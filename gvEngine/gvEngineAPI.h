#pragma once

#if defined(GVLIBRARY_EXPORT) // ������ DLL
#   define GVAPI   __declspec(dllexport)
#else // ��� DLL
#   define GVAPI   __declspec(dllimport)
#endif  // GVLIBRARY_EXPORT

#include <memory>

#include "GeometryData.h"
#include "IInputController.h"
#include "ISceneManager.h"


extern "C"
{
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
}