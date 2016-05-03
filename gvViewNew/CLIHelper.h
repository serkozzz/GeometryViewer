#pragma once 



class CLIHelper
{
public:
	template<typename TDelegateType, typename TArgType>
	static int SubscribeDelegateToUnmanagedEvent(TDelegateType^ del, skb::EventHandler<TArgType>& eventHandler)
	{
		IntPtr funcPointer = Marshal::GetFunctionPointerForDelegate(del);
		return (eventHandler += static_cast<void (CALLBACK *)(TArgType)>(funcPointer.ToPointer()));
	}
};