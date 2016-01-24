#include <thread>
#include <memory>

#include "RootEngineManager.h"
#include "WindowManager.h"
#include "Renderer.h"
#include "InputController.h"
#include "ThreadManager.h"
#include "Logger.h"


using namespace gv;
using namespace gv::Engine;

RootEngineManager* RootEngineManager::_rootEngineManagerInstance = nullptr;

RootEngineManager::RootEngineManager()
{
}

RootEngineManager* RootEngineManager::sharedRootEngineManager()
{
	if (_rootEngineManagerInstance == nullptr)
		_rootEngineManagerInstance = new RootEngineManager();
	return _rootEngineManagerInstance;
}

void RootEngineManager::startInSeparatedThread(int sizeX, int sizeY, IInputListener* InputListener)
{
	sk::Logger::sharedLogger()->setBehavior(
		std::shared_ptr<sk::IWritingBehavior>(new sk::FileWritingBehavior("gvEngineLog.log")));
	_windowManager = new WindowManager();
	_windowManager->createWindow(sizeX, sizeY);
	_inputController = new InputController(_windowManager->getWindow(), InputListener);
	_renderer = new Renderer(_windowManager);
	_threadManager = new ThreadManager(
		std::shared_ptr<IRenderer>(_renderer),
		std::shared_ptr<IInputController>(_inputController),
		10,
		40);
	sk::Logger::sharedLogger()->writeMessage("Hello", sk::Logger::Special);
	sk::Logger::sharedLogger()->writeMessage("This is gvEngine", sk::Logger::Special);
	_threadManager->start();

}


void RootEngineManager::start(int sizeX, int sizeY, IInputListener* inputListener)
{
	std::thread newThread(
		&RootEngineManager::startInSeparatedThread,
		this,
		sizeX,
		sizeY,
		inputListener);
	newThread.detach();
}