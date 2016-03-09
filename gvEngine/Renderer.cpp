#include <thread>
#include <mutex>

#include <GL/glew.h>
#include <glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer.h"
#include "shader.hpp"
#include "ErrorsCollector.h"
#include "WindowManager.h"
#include "SceneManager.h"
#include "MeshManager.h"
#include "VideoMemoryManager.h"
#include "ErrorsCollector.h"

using namespace gv::Engine;
GLuint VertexArrayID;
GLuint vertexbuffer;
GLuint elementbuffer;
GLuint programID;
std::mutex OGLmutex;

Renderer::Renderer(WindowManager* windowManager)
	: _windowManager(windowManager)
{
	// Create and compile our GLSL program from the shaders
	programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );
}

void Renderer::renderFrame(float TimeFromLastFrameMs)
{
	auto videoMemoryManager = VideoMemoryManager::sharedVideoMemoryManager();
	//TODO may be move it to the Thread manager?
	videoMemoryManager->checkQueue();

	auto sceneManager = SceneManager::sharedSceneManager();
	auto meshManager = MeshManager::sharedMeshManager();

	GLuint matrixID = glGetUniformLocation(programID, "MVP");

	OGLmutex.lock();
	// Clear the screen
	glClear( GL_COLOR_BUFFER_BIT );

	//transform
	const Camera* camera3d = sceneManager->get3DCamera();
	glm::mat4 VPmatrix = camera3d->getViewProjectMatrix();
	//glm::mat4 VPmatrix = glm::mat4(1.0f);

		
	const auto& nodes = sceneManager->getNodes();
	for (auto& node : nodes)
	{
		std::string meshName = node.second->getMesh();
		auto mesh = meshManager->getMesh(meshName);
		if (mesh == nullptr)
		{
			ErrorsCollector::sharedErrorsCollector()->
				addError("Scene node references to unexisted mesh. Mesh name = " + meshName);
			throw std::exception("Scene node references to unexisted mesh. Mesh name = "); 
		}


		glm::mat4& modelMatrix = node.second->getTransformMatrix();
		auto MVP = VPmatrix * modelMatrix;


		glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);

		// Use our shader
		glUseProgram(programID);

		videoMemoryManager->bindVAO();
		videoMemoryManager->bindIBO();

		//// Draw the triangles !
		glDrawElements(
			GL_TRIANGLES,      // mode
			mesh->pointsNumber,    // count
			GL_UNSIGNED_INT,   // type
			(void*)(mesh->IBOoffset)          // element array buffer offset
 			);

		videoMemoryManager->unbindVAO();
		videoMemoryManager->unbindIBO();
	}

	// Swap buffers
	glfwSwapBuffers(_windowManager->getWindow());
	glfwPollEvents();
	OGLmutex.unlock();
}


Renderer::~Renderer()
{
	glDeleteProgram(programID);
}