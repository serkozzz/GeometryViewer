

#include <GL/glew.h>
#include <glfw3.h>

#include "OpenGLInitializer.h"
#include "ErrorsCollector.h"


using namespace gv::Engine;


void OpenGLInitializer::initialize()
{
	//TODO to move glewInit in to other place, because other objects depends from it. For example
	//VideoMemoryManager
	//OpenGL context must be created before glewInit() call!!!!!! 
	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		ErrorsCollector::sharedErrorsCollector()->addError("Failed to initialize GLEW");

		//TODO class Renderer coulld not manage window
		glfwTerminate();
	}
}