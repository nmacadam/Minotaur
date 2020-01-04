#pragma once

/** @todo document
*/
//ECS Implementation from Let's Make Games YouTube video series
//https://www.youtube.com/watch?v=XsvI8Sng6dk&index=9&list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

//#include <cereal/cereal.hpp>
//#include <cereal/types/vector.hpp>
//#include <cereal/types/memory.hpp>
//#include <cereal/types/base_class.hpp>
//#include <cereal/types/polymorphic.hpp>

#include <cereal/types/vector.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

class Component;
class Entity;
class EntitySet;  //some forward declaration(s)


//class Collider;


using ComponentID = std::size_t;	//BASICALLY the same thing as typedef, but theres some added bonuses for OOP stuff and whatnot...
									//here we are saying ComponentID is a variable type using size_t for the data type
									//some deeper explanation: https://stackoverflow.com/questions/20790932/what-is-the-logic-behind-the-using-keyword-in-c

using Group = std::size_t;

inline ComponentID getNewComponentTypeID()		//inline means when the function is called the code is inserted in-line instead of being referenced as a memory location
{											//this reduces overhead for extremely simple functions.  Note inline is a request, the compiler can deny it if it doesn't make sense i.e. a complex function shouldn't be inline
	static ComponentID lastID = 0u;
	//every time we call this last id remembers the last component
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept	//template allows for generic data types, i.e. we can run this function with lots of data types and we only need one function
{																		//noexcept in this instance just means the function won't throw errors; be careful with noexcept
	static_assert (std::is_base_of<Component, T>::value, "");
	static ComponentID typeID = getNewComponentTypeID();					//static variables have scope for full program, i.e. the typeID variable wont "start over" on a second call (you should know this by now!)
	return typeID;
}

constexpr std::size_t maxComponents = 32;	//constexpr means the value of the var is evaluated at compile time
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>; //bitsets are just boolean arrays, normal arrays aren't as optimized as possible for bit values; allows us to find out if entity has a selection of components; we compare whether it has it or not
using GroupBitSet = std::bitset<maxGroups>;

using ComponentArray = std::array<Component*, maxComponents>; //just an array of component pointers of the length of our max component

// Derived class maps to base class
static std::unordered_map<std::type_index, std::type_index> polymorphic_relations;

template<class Derived, class Base> void registerPolymorphicRelation()
{
	auto mapItr = polymorphic_relations.find(std::type_index(typeid(Derived)));

	// if it doesn't exist already, add relation
	if (mapItr == polymorphic_relations.end())
	{
		std::cout << "REGISTERING POLYMORPHIC RELATION BETWEEN " << typeid(Derived).name() << " AND " << typeid(Base).name() << "\n\n";
		
		polymorphic_relations.insert(
			std::pair<std::type_index, std::type_index>(
				std::type_index(typeid(Derived)),
				std::type_index(typeid(Base))
				)
		);
	}
}

class Component {
public:
	Entity* entity;
	
	virtual void initialize() {}
	virtual void update() {}
	virtual void onBeforeDraw() {}
	virtual void draw() {}

	virtual void drawEditor() {}

	virtual ~Component() {}

	template <class Archive>
	void serialize(Archive& ar)
	{}

protected:
	
private:

};

class UnmanagedEntity
{
public:
	UnmanagedEntity() = default;

	std::string name;

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(name, components);
	}
	
protected:
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;
};

class Entity : public UnmanagedEntity
{
public:
	Entity(EntitySet& mManager) : manager(mManager) {}

	virtual void update()
	{											//auto lets us use the template variables we defined before
		for (auto& c : components) c->update();	//for every component (c) in components, run c->update; using reference since components are in array as pointers!
	}
	virtual void draw()
	{
		for (auto& c : components) c->onBeforeDraw();
		for (auto& c : components) c->draw();
	}
	//virtual void onCollision(Collider* other) {}
	
	bool isActive() const { return active; }
	void destroy() { active = false; }

	bool hasGroup(Group mGroup)
	{
		return groupBitSet[mGroup];
	}

	void addGroup(Group mGroup);
	void delGroup(Group mGroup)
	{
		groupBitSet[mGroup] = false;
	}

	template <typename T> bool hasComponent() const	//has it got the component? lets check the bit set at that component id! const keyword means member variables cannot be changed
	{
		return componentBitSet[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs> T& addComponent(TArgs&&...mArgs)	//variadic template time! function accepts n of T arguments, returns a reference to T
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));		//creating a pointer c that points to type T; forward forwards arguments of one function to another as though the wrapped functionw as called directly; i.e. we are using it as an optimization thing because of our variadic template
		c->entity = this;								
		std::unique_ptr<Component> uPtr{ c };			//unique_ptr allows a pointer to object of type T (so it accepts T*); 
		components.emplace_back(std::move(uPtr));		//inserts uPtr at the end of the components vector

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->initialize();
		return *c;
	}

	template<typename T> T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);	//auto tells the variable to get its type from the initial value
		return *static_cast<T*>(ptr);						//converts between types using T and ptr
	}

	/*template <typename T, typename... TArgs> T& getOrAddComponent(TArgs&&...mArgs)
	{
		if (componentBitSet[getComponentTypeID<T>()])
		{
			return getComponent<T>();
		}
		else
		{
			addComponent<T>(mArgs);
		}
	}*/
	
	//template<typename T> void RequireComponent()
	//{
	//	//A little bit of error checking to add necessary components
	//	if (!this->hasComponent<T>())
	//	{
	//		std::cerr << "Adding required component type to entity" << std::endl;
	//		this->addComponent<T>();
	//	}
	//}

	//so, example use time: gameobject.getComponent<PositionComponent>().setXpos(25);
	std::vector<std::unique_ptr<Component>>* getAllComponents()
	{
		return &components;
	}

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(cereal::base_class<UnmanagedEntity>(this));//cereal::defer(components)); // serialize things by passing them to the archive

		//archive.serializeDeferments();
	}

	// We could define load_and_construct internally:
	/*template <class Archive>
	static void load_and_construct( Archive & ar, cereal::construct<Entity> & construct )
	{
		auto& e = Engine::loadedEntities->addEntity();
		
		ar(e);
		construct(e);
	}*/

	//std::string name;

//private:
protected:
	
	EntitySet& manager;
	//bool active = true;
	//std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
	GroupBitSet groupBitSet;
};

//namespace cereal
//{
//	template <> struct LoadAndConstruct<Entity>
//	{
//		// load_and_construct will be passed the archive that you will be loading
//		// from as well as a special construct object that can be used to invoke
//		// the constructor for your class.
//		//
//		// More advanced functionality is available using construct, such as accessing
//		// class members, which is detailed in the doxygen docs.
//		//
//		// As with the internal load_and_construct, versioning can be supported by adding an
//		// additional final parameter: const std::uint32_t version
//		template <class Archive>
//		static void load_and_construct(Archive& ar, cereal::construct<Entity>& construct)
//		{
//			EntitySet manager;
//			ar(manager);
//			construct(manager); // calls MyType( x )
//		}
//	};
//}

class EntitySet {
public:
	void checkCollisions()
	{
		for (auto& e : entities)
		{
			/*if (e->hasComponent<Collider>())
			{
				auto collider = &e->getComponent<Collider>();
				for (auto& other : entities)
				{
					if (other->hasComponent<Collider>())
					{
						if (collider->detectCollision(&other->getComponent<Collider>()))
						{
							std::cout << "collision detected\n";
						}
					}
				}
			}*/

			/*if (e->hasComponent<Collider>()) std::cout << "collision detected\n";*/
		}
	}
	void update()
	{
		for (auto& e : entities) e->update();
	}
	void draw()
	{
		for (auto& e : entities) e->draw();
	}

	void refresh()
	{
		for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(groupedEntities[i]);
			v.erase(std::remove_if(std::begin(v), std::end(v), [i](Entity* mEntity)
				{
					return !mEntity->isActive() || !mEntity->hasGroup(i);
				}), std::end(v));
		}

		entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](const std::unique_ptr<Entity>& mEntity)	//removes inactive entities
			{
				return !mEntity->isActive();
			}),
			std::end(entities));
	}

	void AddToGroup(Entity* mEntity, Group mGroup)
	{
		groupedEntities[mGroup].emplace_back(mEntity);
	}

	std::vector<Entity*>& getGroup(Group mGroup)
	{
		return groupedEntities[mGroup];
	}

	Entity& addEntity()
	{
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e }; //initialize uPtr to e
		entities.emplace_back(std::move(uPtr));

		return *e;
	}

	Entity* getEntity(unsigned int iterator)
	{
		return entities[iterator].get();
	}

	Entity* getReleasedEntity(unsigned int iterator)
	{
		return entities[iterator].release();
	}

	/*std::vector<Entity> releaseEntities()
	{
		std::vector<Entity> outVector;

		for (auto& entity : entities)
		{
			Entity e = *(entity.release());
			outVector.push_back(e);
		}
		
		return outVector;
	}*/

	int count()
	{
		return entities.size();
	}

	//template<class Archive>
	//void serialize(Archive& archive)
	//{
	//	archive(entities);//cereal::defer(components)); // serialize things by passing them to the archive

	//	//archive.serializeDeferments();
	//}

	template<class Archive>
	void save(Archive& archive) const
	{
		archive(entities);
	}

	template<class Archive>
	void load(Archive& archive)
	{
		//std::vector<UnmanagedEntity> unmanaged;
		std::cout << "Loaded\n";
	}

private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;

	
};


//
//#define MINOTAUR_REGISTER_POLYMORPHIC_RELATION(Base, Derived)	\
//  minotaur_ecs::registerRelation<Base, Derived>();				\
//
//#define LUAVOID(FN, ...) \
//    void FN(); \
//    static auto addFN ## __LINE__ = myMap.emplace(#FN, FN); \
//    void FN()
//
////namespace minotaur_ecs
////{
//	
//	
//	template <class Base, class Derived> auto registerRelation()
//	{
//		return polymorphic_relations.insert(
//			std::pair<std::type_index, std::type_index>(
//				std::type_index(typeid(Derived)), std::type_index(typeid(Base)))
//		);
//	}
//	
////}
//
//#define MINOTAUR_REGISTER_POLYMORPHIC_RELATION(Base, Derived) \
//	//namespace minotaur_ecs { 
//		void FN(); \
//		static auto addFN ## __LINE__ = registerRelation<Base,Derived>(); \
//	    void FN() \
//	//}