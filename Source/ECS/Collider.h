#pragma once
#include "ECS.h"

template <class T> class Collider :
	public Component
{
public:
    Collider()
    {
        //registerPolymorphicRelation<T, Collider>();
    }
};