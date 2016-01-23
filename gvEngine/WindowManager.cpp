#include <glfw3.h>


#include "WindowManager.h"
#include "ErrorsCollector.h"

using namespace gv::Engine;

WindowManager::WindowManager() :
	_window(nullptr)
{

}

bool WindowManager::createWindow(int width, int height)
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		ErrorsCollector::sharedErrorsCollector()->addError("Failed to initialize GLFW");
		return false;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	_window = glfwCreateWindow( width, height, "gvEngine", NULL, NULL);
	if( _window == NULL ){
		glfwTerminate();
		ErrorsCollector::sharedErrorsCollector()->addError("Failed to open GLFW window."
			"If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.");
		return false;
	}
	glfwMakeContextCurrent(_window);

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
}

void WindowManager::destroyWindow()
{
	glfwTerminate();
}

GLFWwindow* WindowManager::getWindow()
{
	return _window;
}