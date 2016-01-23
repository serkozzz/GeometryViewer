

#include "gvEngineAPI.h"
#include "SceneManager.h"
#include "IInputListener.h"
#include "RenderCycle.h"
#include "ErrorsCollector.h"
#include "RootEngineManager.h"



using namespace gv;
using namespace gv::Engine;


ISceneManager* gv::Engine::getSceneManager()
{
	return SceneManager::sharedSceneManager();
}

void gv::Engine::createView(int sizeX, int sizeY, IInputListener* inputListener)
{
	//WindowManager

	RootEngineManager::sharedRootEngineManager()->start(sizeX, sizeY, inputListener);
	//launchRenderCycle(InputListener);
}

IErrorsCollector* gv::Engine::getErrorsCollector()
{
	return ErrorsCollector::sharedErrorsCollector();
}