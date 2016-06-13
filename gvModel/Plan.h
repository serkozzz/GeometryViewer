#pragma once 

#include "Figure.h"
#include "ICamera.h"

namespace gv
{
	namespace Model
	{
		class Plan
		{
			std::list<Figure> _figures;
			//mCamera _camera;
		public:
			virtual ICamera* getCamera() = 0;
			const std::list<Point>* getFigures() const;

			skb::EventHandler<const Figure&> figureAdded;
			skb::EventHandler<const Figure&> figureRemoved;




			

		public:
			virtual ICamera* getCamera();
			mCamera* getmCamera();

			void AddPoint(const std::shared_ptr<mPoint>& p);
			void RemovePoint(const std::shared_ptr<mPoint>& p);
			const std::list<std::shared_ptr<mPoint> >& getPoints() const;
			const std::list<std::shared_ptr<IPoint> > getPointsOnlyRead() const;
			bool isPointExist(const std::shared_ptr<const IPoint>& p) const; 
			std::shared_ptr<mPoint> getPointByPointer(const IPoint* p) const; 
		};
	}
}