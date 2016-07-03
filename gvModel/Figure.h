#pragma once

#include <list>

#include <ObserverableCollection.h>
#include <common.h>


#include "Point.h"


namespace gv
{ 
	namespace Model
	{
		class Figure;
		typedef skb::PropertyChangedArgs<Figure> FigurePropChangedArgs;
		typedef skb::TryPropertyChangedArgs<Figure> FigureTryPropChangedArgs;

		typedef skb::NonCopiableObserverableCollection<std::list, Point> PointsCollection;

		class Figure : public PlanElement
		{

			PointsCollection _points;
		public:
			Figure(const std::string& name);

			const PointsCollection* getPoints() const;
			PointsCollection* getPoints();

			mutable skb::EventHandler<FigurePropChangedArgs> propertyChanged;
			mutable	skb::EventHandler<FigureTryPropChangedArgs> tryPropertyChanged;

			const Point* addNewPoint(const Point* pointAfterInsertion = nullptr);
			bool removePoint(const Point* point);

		protected:
			virtual void sendPropertyChanged(const std::string& propName) const;
			virtual void sendTryPropertyChanged(const void* newValue, const std::string& propName) const;

		private:
			Figure(const Figure&);
		};
	}
}