
#include <algorithm>

#include "VideoMemoryManager.h"
#include "GeometryData.h"
#include "ErrorsCollector.h"

using namespace gv::Engine;

VideoMemoryManager* VideoMemoryManager::_videoMemoryManagerInstance = nullptr;

VideoMemoryManager::VideoMemoryManager() 
{
}


VideoMemoryManager* VideoMemoryManager::sharedVideoMemoryManager()
{
	if (_videoMemoryManagerInstance == nullptr)
		_videoMemoryManagerInstance = new VideoMemoryManager();
	return _videoMemoryManagerInstance;
}


void VideoMemoryManager::initialize()
{
	glGenBuffers(1, &_vertexBufferId);
	glGenBuffers(1, &_normalsBufferId);
	glGenBuffers(1, &_texCoordsBufferId);

	glGenBuffers(1, &_IBOId);

	////VAO
	glGenVertexArrays(1, &_VAOId);
	glBindVertexArray(_VAOId);

	// 1-st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferId);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	// 2-st attribute buffer : normals
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, _normalsBufferId);
	glVertexAttribPointer(
		1,                  // attribute 1. 
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	// 3-st attribute buffer : textCoords
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, _texCoordsBufferId);
	glVertexAttribPointer(
		2,                  // attribute 2.
		2,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	//glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void VideoMemoryManager::bindVAO()
{
	glBindVertexArray(_VAOId);

}


void VideoMemoryManager::unbindVAO()
{
	glBindVertexArray(0);
}


void VideoMemoryManager::bindIBO()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBOId);
}


void VideoMemoryManager::unbindIBO()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void VideoMemoryManager::deleteVideoMemoryManager()
{
	if (_videoMemoryManagerInstance)
		delete _videoMemoryManagerInstance;
}


VideoMemoryManager::~VideoMemoryManager()
{
	// Cleanup VBO
	glDeleteBuffers(1, &_vertexBufferId);
	glDeleteBuffers(1, &_normalsBufferId);
	glDeleteBuffers(1, &_texCoordsBufferId);
	glDeleteBuffers(1, &_IBOId);

	////VAO
	glDeleteVertexArrays(1, &_VAOId);
}


void VideoMemoryManager::addData(std::shared_ptr<const GeometryData> geometryData, 
								 std::function<void(VideoMemoryDescriptor& descriptor)> callback)
{
	std::lock_guard<std::mutex> lock(_mutex);
	dataAdditionQueue.push(DataAdditionQuery(geometryData, callback));
}


void VideoMemoryManager::checkQueue()
{
	std::lock_guard<std::mutex> lock(_mutex);
	while(!dataAdditionQueue.empty())
	{
		auto& query = dataAdditionQueue.front();
		auto videoMemoryDecroptor = pushDataToVideoMemory(query.geometryData.get());
		query.callback(videoMemoryDecroptor);
		dataAdditionQueue.pop();
	}
}


VideoMemoryManager::VideoMemoryDescriptor VideoMemoryManager::pushDataToVideoMemory(const GeometryData* geometryData)
{
	size_t vertexexNumber = geometryData->verticies.size();

	//weak place(maybe) - unnecessary copying
	float* positionsBufferData = new float[vertexexNumber * 3];
	float* normalsBufferData = new float[vertexexNumber * 3];
	float* uvBufferData = new float[vertexexNumber * 2];

	{
		auto it = geometryData->verticies.begin();
		auto end = geometryData->verticies.end();
		int count = 0;

		for (it; it != end; it++)
		{
			positionsBufferData[3 * count] = (float)it->position.x;
			positionsBufferData[3 * count + 1] = (float)it->position.y;
			positionsBufferData[3 * count + 2] = (float)it->position.z;

			normalsBufferData[3 * count] = (float)it->normal.x;
			normalsBufferData[3 * count + 1] = (float)it->normal.y;
			normalsBufferData[3 * count + 2] = (float)it->normal.z;

			uvBufferData[2 * count] = (float)it->uv.x;
			uvBufferData[2 * count + 1] = (float)it->uv.y;

			count++;
		}
	}

	//TODO: remade, use "sub" commands
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, vertexexNumber * 3 * sizeof(float), positionsBufferData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, _normalsBufferId);
	glBufferData(GL_ARRAY_BUFFER, vertexexNumber * 3 * sizeof(float), normalsBufferData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, _texCoordsBufferId);
	glBufferData(GL_ARRAY_BUFFER, vertexexNumber * 2 * sizeof(float), uvBufferData, GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);


	//weak place - unnecessary copying
	int indexesNumber = geometryData->indecies.size(); 
	unsigned int* indexies = new unsigned int[indexesNumber];
	std::copy(geometryData->indecies.begin(), geometryData->indecies.end(), indexies);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBOId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexesNumber * sizeof(unsigned int), indexies, GL_STATIC_DRAW);


	delete[] positionsBufferData;
	delete[] normalsBufferData;
	delete[] uvBufferData;
	delete[] indexies;

	VideoMemoryDescriptor dataDecriptor;
	dataDecriptor.startPos = 0;
	dataDecriptor.vertexesNumber = vertexexNumber;

	return dataDecriptor;
}