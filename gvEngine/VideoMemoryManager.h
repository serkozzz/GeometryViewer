#pragma once 

#include <memory>
#include <queue>
#include <mutex>
#include <set>

#include <GL/glew.h>
#include <functional>


namespace gv
{
	namespace Engine
	{
		struct GeometryData;

		class VideoMemoryManager
		{
		public:

			struct VideoMemoryDescriptor
			{
				int bufferOffsetInBytes;
				int vertexesNumber;
			};

		private:

			static VideoMemoryManager* _videoMemoryManagerInstance;
			VideoMemoryManager();
			~VideoMemoryManager();

			GLuint _vaoId;
			GLuint _iboId;
			GLuint _positionsBufferId;
			GLuint _texCoordsBufferId;
			GLuint _normalsBufferId;


			int _vertexesCount;
			int _indexesCount;

			mutable std::mutex _mutex;


			VideoMemoryDescriptor pushDataToVideoMemory(const GeometryData* data);
			
			/*returns id of created VAO
			*/
			GLuint createVAO(int positionsBufferOffset,
				int normalsBufferOffset,
				int textCoordsBufferOffset);

			struct DataAdditionQuery
			{
				DataAdditionQuery(std::shared_ptr<const GeometryData> geometryData,
					std::function<void(VideoMemoryDescriptor& descriptor)> callback)
					: geometryData(geometryData), callback(callback)
				{

				}
				std::shared_ptr<const GeometryData> geometryData;
				std::function<void(VideoMemoryDescriptor& descriptor)> callback;
			};
			std::queue<DataAdditionQuery> dataAdditionQueue;


		public:

			static VideoMemoryManager* sharedVideoMemoryManager();
			static void deleteVideoMemoryManager();

			void initialize();

			void bindVAO();
			void unbindVAO();
			void bindIBO();
			void unbindIBO();

			GLuint getVAOId();
			GLuint getIBOId();

			void addData(std::shared_ptr<const GeometryData> geometryData, 
				std::function<void(VideoMemoryDescriptor& descriptor)> callback);

			//WARNING!!! this function may be called from Engine thread only!!
			//TODO interface for VideoMemory users without this method
			void checkQueue();
		};
	}
}