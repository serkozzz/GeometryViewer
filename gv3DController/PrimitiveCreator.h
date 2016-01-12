#pragma once 

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
			static const gv::Engine::GeometryData* getCube();
			static const gv::Engine::GeometryData* getSphere();
		};
	}
}