#pragma once 

#include "Figure.h"
#include "Camera.h"


namespace gv
{
	namespace Model
	{
		typedef skb::PtrsObserverableCollection<std::list, Figure> FiguresCollection;
		class Plan
		{
			FiguresCollection _figures;
			Camera _camera;
		public:
			const FiguresCollection* getFigures() const;
			FiguresCollection* getFigures();

			const Camera* getCamera() const;
			Camera* getCamera();

			const Figure* addNewFigure(const Figure* figureAfterInsertion);
			bool removeFigure(const Figure* figure);
		};
	}
}