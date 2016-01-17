

#include "gvEngineAPI.h"
#include "SceneManager.h"

using namespace gv::Engine;


ISceneManager* gv::Engine::getSceneManager()
{
	return SceneManager::sharedSceneManager();
}