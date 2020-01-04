#pragma once
#include <vector>
#include <functional>

/*
 * C#-esque Action delegate
 * + Supports lambdas
 * + Operator overloading for +=, =, and ()
 * + No support for unsubscribing (-= operator)
 * + Utilizes std::function (could be faster using other methods, but it's really clean!)
 */
template <typename... TArgs> class Action
{
public:
	Action() = default;

	/*
	 * Calls all subscribed functions with the given arguments in order of subscription with
	 */
	void invoke(TArgs&...mArg)
	{
		for (const auto& action : actions)
		{
			action(std::forward<TArgs&>(mArg)...);
		}
	}

	/*
	 * Adds a function to the subscriber list
	 */
	void subscribe(std::function<void(TArgs&...mArg)> action)
	{
		actions.push_back(action);
	}

	/*
	 * Removes all subscribed functions
	 */
	void clear()
	{
		actions.clear();
	}

	/*
	 * Subscribes the given function
	 */
	void operator += (std::function<void(TArgs&...mArg)> action)
	{
		subscribe(action);
	}

	/*
	 * Clears the Action delegate and subscribes the given function
	 */
	Action& operator = (std::function<void(TArgs &...mArg)> action)
	{
		clear();
		subscribe(action);

		return *this;
	}

	/*
	 * Calls all subscribed functions with the given arguments in order of subscription with
	 */
	void operator () (TArgs&...mArg)
	{
		invoke(std::forward<TArgs&>(mArg)...);
	}
	
private:
	std::vector<std::function<void(TArgs&...mArgs)>> actions;
};