#pragma once

#include <list>

#include "Point.h"



namespace gv
{ 
	namespace Model
	{
		class Figure;
		typedef skb::PropertyChangedArgs<Figure> FigurePropChangedArgs;
		typedef skb::TryPropertyChangedArgs<Figure> FigureTryPropChangedArgs;

		class Figure : public PlanElement
		{
			std::list<Point> _points;
		public:
			const std::list<Point>* getPoints() const;




			skb::EventHandler<FigurePropChangedArgs> propertyChanged;
			mutable	skb::EventHandler<FigureTryPropChangedArgs> tryPropertyChanged;

		protected:
			virtual void sendPropertyChanged(const std::string& propName) const;
			virtual void sendTryPropertyChanged(const void* newValue, const std::string& propName) const;
		};
	}
}