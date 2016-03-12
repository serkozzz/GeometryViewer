
#include <algorithm>

#include "VideoMemoryManager.h"
#include "GeometryData.h"
#include "ErrorsCollector.h"

using namespace gv::Engine;

static const int vertexesBufferSize = 1 * 1024 * 1024; //1 mb
static const int indexesBufferSize = 1 * 1024 * 1024; //1 mb

static const int SIZE_OF_POSITION_ATTR = 3 * sizeof(float);
static const int SIZE_OF_NORMAL_ATTR = 3 * sizeof(float);
static const int SIZE_OF_TEXTCOORDS_ATTR = 2 * sizeof(float);
static const int SIZE_OF_INDEX = 1 * sizeof(unsigned int);

VideoMemoryManager* VideoMemoryManager::_videoMemoryManagerInstance = nullptr;

VideoMemoryManager::VideoMemoryManager() 
{
	_vertexesCount = 0;
	_indexesCount = 0;
}


VideoMemoryManager* VideoMemoryManager::sharedVideoMemoryManager()
{
	if (_videoMemoryManagerInstance == nullptr)
		_videoMemoryManagerInstance = new VideoMemoryManager();
	return _videoMemoryManagerInstance;
}


void VideoMemoryManager::initialize()
{
	glGenBuffers(1, &_positionsBufferId);
	glGenBuffers(1, &_normalsBufferId);
	glGenBuffers(1, &_texCoordsBufferId);

	glGenBuffers(1, &_iboId);



	glBindBuffer(GL_ARRAY_BUFFER, _positionsBufferId);
	glBufferData(GL_ARRAY_BUFFER, vertexesBufferSize, nullptr, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, _normalsBufferId);
	glBufferData(GL_ARRAY_BUFFER, vertexesBufferSize, nullptr, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, _texCoordsBufferId);
	glBufferData(GL_ARRAY_BUFFER, vertexesBufferSize, nullptr, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexesBufferSize, nullptr, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	_vaoId = createVAO(0, 0, 0);
}


GLuint VideoMemoryManager::createVAO(int positionsBufferOffset,
									 int normalsBufferOffset,
									 int textCoordsBufferOffset)
{
	GLuint vaoId;
	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	// 1-st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _positionsBufferId);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)positionsBufferOffset            // array buffer offset
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
		(void*)normalsBufferOffset            // array buffer offset
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
		(void*)textCoordsBufferOffset            // array buffer offset
		);

	//glDisableVertexAttribArray(0);
	glBindVertexArray(0);

	return vaoId;
}



void VideoMemoryManager::bindVAO()
{
	glBindVertexArray(_vaoId);
}


void VideoMemoryManager::unbindVAO()
{
	glBindVertexArray(0);
}


void VideoMemoryManager::bindIBO()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboId);
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
	glDeleteBuffers(1, &_positionsBufferId);
	glDeleteBuffers(1, &_normalsBufferId);
	glDeleteBuffers(1, &_texCoordsBufferId);
	glDeleteBuffers(1, &_iboId);

	////VAO
	//for(GLuint vaoId : _vaoIdSet)
	glDeleteVertexArrays(1, &_vaoId);
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
	size_t vertexesNumber = geometryData->verticies.size();

	//weak place(maybe) - unnecessary copying
	float* positionsBufferData = new float[vertexesNumber * 3];
	float* normalsBufferData = new float[vertexesNumber * 3];
	float* uvBufferData = new float[vertexesNumber * 2];

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

	int positionsDataSize = vertexesNumber * SIZE_OF_POSITION_ATTR;
	int normalsDataSize = vertexesNumber * SIZE_OF_NORMAL_ATTR;
	int texCoordsDataSize = vertexesNumber * SIZE_OF_TEXTCOORDS_ATTR;

	int positionBufferOffset = _vertexesCount * SIZE_OF_POSITION_ATTR;
	int normalsBufferOffset = _vertexesCount * SIZE_OF_NORMAL_ATTR;
	int textCoordsBufferOffset = _vertexesCount * SIZE_OF_TEXTCOORDS_ATTR;

	glBindBuffer(GL_ARRAY_BUFFER, _positionsBufferId);
	glBufferSubData(GL_ARRAY_BUFFER, positionBufferOffset, positionsDataSize, positionsBufferData);
	glBindBuffer(GL_ARRAY_BUFFER, _normalsBufferId);
	glBufferSubData(GL_ARRAY_BUFFER, normalsBufferOffset, normalsDataSize, normalsBufferData);
	glBindBuffer(GL_ARRAY_BUFFER, _texCoordsBufferId);
	glBufferSubData(GL_ARRAY_BUFFER, normalsBufferOffset, texCoordsDataSize, uvBufferData);



	//weak place - unnecessary copying
	int indexesNumber = geometryData->indecies.size(); 
	unsigned int* indexies = new unsigned int[indexesNumber];
	int count = 0;
	for (unsigned int index : geometryData->indecies)
	{
		indexies[count] = index + _vertexesCount;
		count++;
	}
	//std::copy(geometryData->indecies.begin(), geometryData->indecies.end(), indexies);
	int indexesDataSize = indexesNumber * SIZE_OF_INDEX;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboId);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, _indexesCount * SIZE_OF_INDEX, indexesDataSize, indexies);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	delete[] positionsBufferData;
	delete[] normalsBufferData;
	delete[] uvBufferData;
	delete[] indexies;

	VideoMemoryDescriptor dataDescriptor;
	dataDescriptor.bufferOffsetInBytes = _indexesCount * SIZE_OF_INDEX;
	dataDescriptor.vertexesNumber = indexesNumber;

	_vertexesCount += vertexesNumber;
	_indexesCount += indexesNumber;

	return dataDescriptor;
}