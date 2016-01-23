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
			GVAPI void createView(int sizeX, int sizeY, IInputListener* InputListener);
			GVAPI ISceneManager* getSceneManager();
			
			GVAPI IErrorsCollector* getErrorsCollector();
			GVAPI void gvTest();
			//GVAPI int tutorial2();
		}
	}
//}