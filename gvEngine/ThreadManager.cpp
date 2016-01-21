#include <chrono>
#include <thread>



#include "ThreadManager.h"

using namespace gv::Engine;

ThreadManager::ThreadManager(std::shared_ptr<IRenderer> renderer, 
							 std::shared_ptr<IInputController> inputController, 
							 float inputCheckInterval,
							 float renderLoopInterval) 
							 : _renderer(renderer), _inputController(inputController), _inputCheckInterval(inputCheckInterval), _renderLoopInterval(renderLoopInterval)
{

}

void ThreadManager::start()
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point nextRender = now + _renderLoopInterval;
	std::chrono::system_clock::time_point nextInputCheck = now + _inputCheckInterval;

	do
	{

	}
	while(true);
}