#pragma once 

#include <memory>
#include <queue>
#include <mutex>

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
				int startPos;
				int vertexesNumber;
			};

		private:

			static VideoMemoryManager* _videoMemoryManagerInstance;
			VideoMemoryManager();
			~VideoMemoryManager();

			GLuint _VAOId;
			GLuint _IBOId;
			GLuint _vertexBufferId;
			GLuint _texCoordsBufferId;
			GLuint _normalsBufferId;

			mutable std::mutex _mutex;


			VideoMemoryDescriptor pushDataToVideoMemory(const GeometryData* data);

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