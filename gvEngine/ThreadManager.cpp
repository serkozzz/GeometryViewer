#include <chrono>
#include <thread>


#include "Logger.h"
#include "ThreadManager.h"

using namespace gv::Engine;

ThreadManager::ThreadManager(std::shared_ptr<IRenderer> renderer, 
							 std::shared_ptr<IInputController> inputController, 
							 unsigned int inputCheckInterval,
							 unsigned int renderLoopInterval) 
							 : _renderer(renderer), _inputController(inputController), _inputCheckInterval(inputCheckInterval), _renderLoopInterval(renderLoopInterval)
{

}

void ThreadManager::start()
{
	sk::Logger::sharedLogger()->writeMessage("gvEngine::ThreadManager has started");
	_renderer->renderFrame(0);

	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point nextRenderDate = now + _renderLoopInterval;
	std::chrono::system_clock::time_point nextInputCheckDate  = now + _inputCheckInterval;
	std::chrono::system_clock::time_point lastRenderDate = now;

	do
	{
		auto nextEventDate = (nextInputCheckDate < nextRenderDate) ? nextInputCheckDate : nextRenderDate;
		std::this_thread::sleep_until(nextEventDate + std::chrono::duration<int, std::milli>(1));

		if (nextInputCheckDate <= std::chrono::system_clock::now())
		{
			nextInputCheckDate += _inputCheckInterval;
			_inputController->checkInput();
		}
		if (nextRenderDate <= std::chrono::system_clock::now())
		{
			nextRenderDate += _renderLoopInterval;
			auto elapsedTime = std::chrono::system_clock::now() - lastRenderDate;
			lastRenderDate = std::chrono::system_clock::now();
			_renderer->renderFrame(elapsedTime.count());
		}

	}
	while(true);
}