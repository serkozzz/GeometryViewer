// Starter.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../gvEngine/gvEngineAPI.h"
#include "../gv3DController/PrimitiveCreator.h"

using namespace gv::Engine;

int _tmain(int argc, _TCHAR* argv[])
{
	//gvTest();
		tutorial2();
		ISceneManager* manager = getSceneManager();
		manager->createMesh("", gv::Controller3D::PrimitiveCreator::getCube());

	getchar();
	return 0;
}

