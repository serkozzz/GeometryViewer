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
	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		ErrorsCollector::sharedErrorsCollector()->addError("Failed to initialize GLEW");
		glfwTerminate();
	}

	// Create and compile our GLSL program from the shaders
	programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );

#pragma region old buffers creation

	//const GLfloat g_vertex_buffer_data[] = { 
	//	-1.0f, -1.0f, 0.0f,
	//	1.0f, -1.0f, 0.0f,
	//	0.0f,  1.0f, 0.0f,
	//};

	//glGenBuffers(1, &vertexbuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


	//const int  g_indecies_data[] = { 
	//	0, 1, 2
	//};

	//glGenBuffers(1, &elementbuffer);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_indecies_data), g_indecies_data, GL_STATIC_DRAW);


	//////VAO
	//glGenVertexArrays(1, &VertexArrayID);
	//glBindVertexArray(VertexArrayID);

	//// 1-st attribute buffer : vertices
	//glEnableVertexAttribArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	//glVertexAttribPointer(
	//	0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	//	3,                  // size
	//	GL_FLOAT,           // type
	//	GL_FALSE,           // normalized?
	//	0,                  // stride
	//	(void*)0            // array buffer offset
	//	);


	////glDisableVertexAttribArray(0);

	//glBindVertexArray(0);

#pragma endregion old buffers creation


}

void Renderer::renderFrame(float TimeFromLastFrameMs)
{
	auto videoMemoryManager = VideoMemoryManager::sharedVideoMemoryManager();
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
			(void*)mesh->IBOoffset          // element array buffer offset
			);

		videoMemoryManager->unbindVAO();
		videoMemoryManager->unbindIBO();
	}


	//glBindVertexArray(VertexArrayID);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

	//// Draw the triangles !
	//glDrawElements(
	//	GL_TRIANGLES,      // mode
	//	3,    // count
	//	GL_UNSIGNED_INT,   // type
	//	(void*)0           // element array buffer offset
	//	);

	//glBindVertexArray(0);


	// Swap buffers
	glfwSwapBuffers(_windowManager->getWindow());
	glfwPollEvents();
	OGLmutex.unlock();
}


Renderer::~Renderer()
{
	// Cleanup VBO
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);
}