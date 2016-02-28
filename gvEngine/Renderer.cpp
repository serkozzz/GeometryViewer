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

	const GLfloat g_vertex_buffer_data[] = { 
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);



	const int  g_indecies_data[] = { 
		0, 1, 2
	};

	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_indecies_data), g_indecies_data, GL_STATIC_DRAW);


	////VAO
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// 1-st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);


	//glDisableVertexAttribArray(0);

	glBindVertexArray(0);


}

void Renderer::renderFrame(float TimeFromLastFrameMs)
{
	OGLmutex.lock();
	// Clear the screen
	glClear( GL_COLOR_BUFFER_BIT );

	//transform
	const Camera* camera3d = SceneManager::sharedSceneManager()->get3DCamera();
	glm::mat4 VPmatrix = camera3d->getViewProjectMatrix();
	//glm::mat4 VPmatrix = glm::mat4(1.0f);

	glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -10.0f));
	auto MVP = VPmatrix * modelMatrix;

	GLuint matrixID = glGetUniformLocation(programID, "MVP");
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);

	// Use our shader
	glUseProgram(programID);


	glBindVertexArray(VertexArrayID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

	// Draw the triangles !
	glDrawElements(
		GL_TRIANGLES,      // mode
		3,    // count
		GL_UNSIGNED_INT,   // type
		(void*)0           // element array buffer offset
		);

	glBindVertexArray(0);



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