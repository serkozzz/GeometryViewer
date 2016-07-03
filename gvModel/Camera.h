#pragma once

#include <EventHandler.h>

#include "PlanElement.h"


namespace gv
{
	namespace Model
	{
		class Camera;
		typedef skb::PropertyChangedArgs<Camera> CameraPropChangedArgs;
		typedef skb::TryPropertyChangedArgs<Camera> CameraTryPropChangedArgs;

		class Camera : public PlanElement
		{
		public:
			Camera(const std::string& name);

			mutable skb::EventHandler<CameraPropChangedArgs> propertyChanged;
			mutable	skb::EventHandler<CameraTryPropChangedArgs> tryPropertyChanged;

		protected:
			virtual void sendPropertyChanged(const std::string& propName) const;
			virtual void sendTryPropertyChanged(const void* newValue, const std::string& propName) const;
		};
	}
}