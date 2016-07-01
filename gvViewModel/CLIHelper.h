#pragma once 

#include <msclr\marshal_cppstd.h>

#include <EventHandler.h>

using namespace System;
using namespace System::Runtime::InteropServices;


class CLIHelper
{
public:
	//Warning! You must follow that delagate reference will not be removed(for example, make it class member)
	template<typename TDelegateType, typename TArgType>
	static int SubscribeDelegateToUnmanagedEvent(TDelegateType^ del, skb::EventHandler<TArgType>& eventHandler)
	{
		IntPtr funcPointer = Marshal::GetFunctionPointerForDelegate(del);
		return (eventHandler += static_cast<void (CALLBACK *)(TArgType)>(funcPointer.ToPointer()));
	}
};