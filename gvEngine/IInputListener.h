#pragma once
#include "dllexport.h"

namespace gv
{

	enum gvKey
	{
		GV_KEY_UP,
		GV_KEY_DOWN,
		GV_KEY_RIGHT,
		GV_KEY_LEFT
	};

	class GVAPI IInputListener
	{
	public:
		virtual void keyPressed(gvKey key) const = 0;
		virtual void cursorPositionChanged(double dx, double dy) const = 0;
		//TO DO methods that will be invoked from Engive
	};

}