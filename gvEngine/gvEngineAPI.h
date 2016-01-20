#pragma once

#include <memory>

#include "dllexport.h"

#include "GeometryData.h"
#include "IInputListener.h"
#include "ISceneManager.h"



//extern "C"
//{
	namespace gv
	{
		namespace Engine
		{
			GVAPI void createWindow(int sizeX, int sizeY, IInputListener* InputListener);
			GVAPI ISceneManager* getSceneManager();

			GVAPI void gvTest();
			//GVAPI int tutorial2();
		}
	}
//}