#pragma once 

#include <GL/glew.h>


namespace gv
{
	namespace Engine
	{
		struct GeometryData;

		class VideoMemoryManager
		{
			static VideoMemoryManager* _videoMemoryManagerInstance;
			VideoMemoryManager();

			GLuint _VAOId;
			GLuint _IBOId;
			GLuint _vertexBufferId;
			GLuint _texCoordsBufferId;
			GLuint _normalsBufferId;

			void initialize();

		public:
			struct VideoMemoryDataDescriptor
			{
				int startPos;
				int vertexesNumber;
			};

			static VideoMemoryManager* sharedVideoMemoryManager();
			
			void bindVAO();
			void unbindVAO();
			void bindIBO();
			void unbindIBO();

			GLuint getVAOId();
			GLuint getIBOId();
			VideoMemoryDataDescriptor addData(const GeometryData* geometryData);


		};
	}
}