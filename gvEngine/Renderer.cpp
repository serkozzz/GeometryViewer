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

	// �������� ���� �������
	glEnable(GL_DEPTH_TEST);
	// �������� ����� ���������� ������ � ���, ������, ���� �� ��������� ����� � ������, ��� ����������
	glDepthFunc(GL_LESS);
}

void Renderer::renderFrame(float timeFromLastFrameMs)
{
	auto videoMemoryManager = VideoMemoryManager::sharedVideoMemoryManager();
	//TODO may be move it to the Thread manager?
	videoMemoryManager->checkQueue();

	auto sceneManager = SceneManager::sharedSceneManager();
	auto meshManager = MeshManager::sharedMeshManager();

	GLuint mvpMatrixId = glGetUniformLocation(programID, "MVP");
	GLuint mMatrixId = glGetUniformLocation(programID, "M");
	GLuint vMatrixId = glGetUniformLocation(programID, "V");
	GLuint materialColorId = glGetUniformLocation(programID, "materialColor");
	GLuint lightPosId = glGetUniformLocation(programID, "LightPosition_worldspace");
	GLuint lightPowerId = glGetUniformLocation(programID, "LightPower");
	GLuint lightColorId = glGetUniformLocation(programID, "LightColor");
	GLuint ambientIntensityId = glGetUniformLocation(programID, "AmbientIntensity");



	OGLmutex.lock();
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//transform
	const Camera* camera3d = sceneManager->get3DCamera();
	glm::mat4 VMatrix = camera3d->getViewMatrix();
	glm::mat4 VPmatrix = camera3d->getViewProjectMatrix();

	static float timeCount = 0;
	timeCount += timeFromLastFrameMs;

	glm::vec3 lightPosition = glm::vec3(0, 10, 10);
	//lightPosition.y = sin(timeCount / 1000 ) * 10;
	//lightPosition.x = cos(timeCount / 1000 ) * 10;

	glUniform3f(lightPosId, lightPosition.x, lightPosition.y, lightPosition.z);
	glUniform3f(lightColorId, 1.0f, 1.0f, 1.0f);
	glUniform1f(lightPowerId, 10.0f);
	glUniform1f(ambientIntensityId, 0.2f);

	glUniformMatrix4fv(vMatrixId, 1, GL_FALSE, &VMatrix[0][0]);

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
		//auto MVP = camera3d->getProjectMatrix() * glm::translate(glm::mat4(1.0f), glm::vec3(-1, -1, -15))  * modelMatrix;

		glUniformMatrix4fv(mvpMatrixId, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(mMatrixId, 1, GL_FALSE, &modelMatrix[0][0]);
		
		auto material = node.second->getMaterial();	
		glUniform3f(
			materialColorId,
			material->getColor().r,
			material->getColor().g,
			material->getColor().b);

		// Use our shader
		glUseProgram(programID);

		videoMemoryManager->bindVAO();
		videoMemoryManager->bindIBO();

		//// Draw the triangles !
		glDrawElements(
			GL_TRIANGLES,      // mode
			mesh->pointsNumber,    // count
			GL_UNSIGNED_INT,   // type
			(void*)(mesh->iboOffsetInBytes)          // element array buffer offset
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