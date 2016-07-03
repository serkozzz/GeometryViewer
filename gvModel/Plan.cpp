#include "Plan.h"

using namespace gv::Model;


const FiguresCollection* Plan::getFigures() const
{
	return &_figures;
}


FiguresCollection* Plan::getFigures()
{
	return &_figures;
}


const Camera* Plan::getCamera() const
{
	return &_camera;
}

Camera* Plan::getCamera()
{
	return &_camera;
}



const Figure* Plan::addNewFigure(const Figure* figureAfterInsertion)
{
	size_t pointsNumber = _figures.size();
	
	return _figures.insert(Figure("figure " + std::to_string(pointsNumber)), figureAfterInsertion);
}


bool Plan::removeFigure(const Figure* figure)
{
	return _figures.remove(figure);
}