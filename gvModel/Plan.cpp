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
	Figure f ("figure " + std::to_string(pointsNumber));
	return _figures.insert(std::move(f), figureAfterInsertion);
}


bool Plan::removeFigure(const Figure* figure)
{
	return _figures.remove(figure);
}