

#include "gvEngineAPI.h"
#include "SceneManager.h"
#include "IInputListener.h"
#include "RenderCycle.h"

using namespace gv;
using namespace gv::Engine;


ISceneManager* gv::Engine::getSceneManager()
{
	return SceneManager::sharedSceneManager();
}

void gv::Engine::createWindow(int sizeX, int sizeY, IInputListener* InputListener)
{
	launchRenderCycle(InputListener);
}