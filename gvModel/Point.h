#pragma once

#include "PlanElement.h"
#include <common.h>

namespace gv
{
	namespace Model
	{
		class Point;
		typedef skb::PropertyChangedArgs<Point> PointPropChangedArgs;
		typedef skb::TryPropertyChangedArgs<Point> PointTryPropChangedArgs;

		class Point : public PlanElement
		{
			PrimitiveType _primitive;

		public:

			static const std::string primitivePropertyName;

			PrimitiveType getPrimitive() const;
			void setPrimitive(const PrimitiveType& newPrimitive);
			void trySetPrimitive(const PrimitiveType& newPrimitive) const;

			mutable skb::EventHandler<PointPropChangedArgs> propertyChanged;
			mutable	skb::EventHandler<PointTryPropChangedArgs> tryPropertyChanged;

		protected:
			virtual void sendPropertyChanged(const std::string& propName) const;
			virtual void sendTryPropertyChanged(const void* newValue, const std::string& propName) const;
		};
	}
}