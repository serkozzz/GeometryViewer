#pragma once 

#include <memory>
#include "../gvEngine/GeometryData.h"

namespace gv
{
	namespace Controller3D
	{
		class PrimitiveCreator
		{
		private:
			static gv::Engine::GeometryData* _cube;
			static gv::Engine::GeometryData* _sphere;

		public:
			static std::shared_ptr<const gv::Engine::GeometryData> getCube();
			static std::shared_ptr<const gv::Engine::GeometryData> getSphere();
			static std::shared_ptr<const gv::Engine::GeometryData> getTriangle();
			static std::shared_ptr<const gv::Engine::GeometryData> getXYRectangle(glm::vec2 leftBottom, glm::vec2 rightUp);
		};
	}
}