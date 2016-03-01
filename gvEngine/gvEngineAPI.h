#pragma once

#include <memory>

#include "dllexport.h"

#include "GeometryData.h"
#include "IInputListener.h"
#include "ISceneManager.h"
#include "IErrorsCollector.h"


//extern "C"
//{
	namespace gv
	{
		namespace Engine
		{

			//TODO move logic of engine initialization and start render cycle from createView
			//users can create scene, add meshes without View
			GVAPI void createView(int sizeX, int sizeY, IInputListener* InputListener);
			GVAPI ISceneManager* getSceneManager();
			
			GVAPI IErrorsCollector* getErrorsCollector();
			GVAPI void gvTest();
			//GVAPI int tutorial2();
		}
	}
//}