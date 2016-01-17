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

	class GVAPI IInputController
	{
	public:
		virtual void keyPressed(gvKey key) = 0;
		//TO DO methods that will be invoked from Engive
	};

}