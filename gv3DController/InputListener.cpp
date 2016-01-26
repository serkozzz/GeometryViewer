#include "InputListener.h"

using namespace gv;
using namespace gv::Controller3D;

void InputListener::keyPressed(gvKey key) const
{
	switch(key)
	{
	case gvKey::GV_KEY_UP:
		{
			int a = 10;
			a++;
			break;
		}
	case gvKey::GV_KEY_DOWN:
		{
			int a = 10;
			a++;
			break;
		}
	case gvKey::GV_KEY_LEFT:
		{
			int a = 10;
			a++;
			break;
		}
	case gvKey::GV_KEY_RIGHT:
		{
			int a = 10;
			a++;
			break;
		}
	}
}


void InputListener::cursorPositionChanged(double dx, double dy) const
{
	int a = 10;
	a++;
}