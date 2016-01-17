

#include "gvEngineAPI.h"
#include "SceneManager.h"
#include "IInputController.h"
#include "RenderCycle.h"

using namespace gv;
using namespace gv::Engine;


ISceneManager* gv::Engine::getSceneManager()
{
	return SceneManager::sharedSceneManager();
}

void gv::Engine::createWindow(int sizeX, int sizeY, IInputController* inputController)
{
	launchRenderCycle(inputController);
}