#pragma once

#include <memory>

#include "dllexport.h"

#include "GeometryData.h"
#include "IInputController.h"
#include "ISceneManager.h"



//extern "C"
//{
	//GVAPI void gvTest1();
	namespace gv
	{
		namespace Engine
		{
			GVAPI void createWindow(int sizeX, int sizeY, IInputController* inputController);
			GVAPI ISceneManager* getSceneManager();

			GVAPI void gvTest();
			GVAPI int tutorial2();
		}
	}
//}