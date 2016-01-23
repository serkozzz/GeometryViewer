#include <thread>
#include <mutex>

#include <GL/glew.h>
#include <glfw3.h>

#include "Renderer.h"
#include "shader.hpp"
#include "ErrorsCollector.h"
#include "WindowManager.h"

using namespace gv::Engine;
GLuint VertexArrayID;
GLuint vertexbuffer;
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

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );

	static const GLfloat g_vertex_buffer_data[] = { 
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

void Renderer::renderFrame(float TimeFromLastFrameMs)
{
	OGLmutex.lock();
	// Clear the screen
	glClear( GL_COLOR_BUFFER_BIT );

	// Use our shader
	glUseProgram(programID);

	// 1rst attribute buffer : vertices
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

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

	glDisableVertexAttribArray(0);

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