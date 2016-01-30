#pragma once


#include <map>
#include <functional>
#include <algorithm>

namespace skb    //means SerKoz Bicycles
{
	template <typename ArgsType>
	class EventHandler 
	{
		typedef std::function<void(ArgsType)> callbackType;

	private:
		std::map<int, callbackType> _handlers;
		int _subscriptionsCount;

	public:
		EventHandler();

		int operator+= (callbackType callback);
		void operator-= (int subscriptionId);
		bool operator== (std::nullptr_t);
		bool operator!= (std::nullptr_t);

		void operator () (ArgsType arg) const;
	};

	template <typename ArgsType>
	EventHandler<ArgsType>::EventHandler() : _subscriptionsCount(0)
	{

	}

	template <typename ArgsType>
	int EventHandler<ArgsType>::operator+= (callbackType callback)
	{
		if(callback)
		{
			_handlers[_subscriptionsCount] = callback;	
		}
		return _subscriptionsCount++;
	}

	template <typename ArgsType>
	void EventHandler<ArgsType>::operator-= (int subscriptionId)
	{
		auto it = _handlers.find(subscriptionId);
		if(it != _handlers.end())
			_handlers.erase(it);
	}

	template <class ArgsType>
	bool  EventHandler<ArgsType>::operator==(std::nullptr_t)
	{
		if(_handlers.empty())
			return true;
		return false;
	}


	template <class ArgsType>
	bool  EventHandler<ArgsType>::operator!=(std::nullptr_t arg)
	{
		return !(this->operator==(arg));
	}

	template <typename ArgsType>
	void EventHandler<ArgsType>::operator () (ArgsType arg) const
	{
		std::for_each(_handlers.begin(), _handlers.end(), [&] (const std::pair<int, callbackType>& pair) 
		{ 
			pair.second(arg); 
		});

	}

	//template <typename T>
	//struct PropertyChangedArgs
	//{
	//	PropertyChangedArgs(T* sender, T* newValue, const std::string& propName) 
	//		: sender(sender), newValue(newValue), propName(propName)
	//	{
	//	}

	//	T* sender; ///object whose properties is chanded
	//	T* newValue; 
	//	std::string propName;
	//};

	template <typename T>
	struct PropertyChangedArgs
	{
		PropertyChangedArgs(const T* sender, const void* newValue, const std::string& propName) 
			: sender(sender), newValue(newValue), propName(propName)
		{
		}

		const T* sender; ///object whose properties is chanded
		const void* newValue; 
		std::string propName;
	};

	//template <typename T>
	//struct TryPropertyChangeArgs
	//{
	//	TryPropertyChangeArgs(const T* sender, const std::string& propName, const void* newValue) 
	//		: propName(propName), newValue(newValue)
	//	{
	//	}
	//	const std::string& propName;
	//	const void* newValue;
	//};
}