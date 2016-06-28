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