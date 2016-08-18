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
	size_t figuresNumber = _figures.size();
	std::unique_ptr<Figure> newFigure(new Figure("figure " + std::to_string(figuresNumber)));

	if (figureAfterInsertion == nullptr)
	{
		_figures.push_back(std::move(newFigure));
		return _figures.back().get();
	}
	auto it = _figures.find(figureAfterInsertion);
	return (*_figures.insert(it, std::move(newFigure))).get();
}


bool Plan::removeFigure(const Figure* figure)
{
	_figures.erase(_figures.find(figure));
	return true;
}