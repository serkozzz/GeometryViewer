#pragma once

#include "Camera.h"

namespace gv
{
	namespace Model
	{
		class CameraMover
		{
			Camera* _camera;
			int _subscriptiomId;
			void cameraTryPropertyChanged(const CameraTryPropChangedArgs&);

		public:
			CameraMover(Camera* camera);
			~CameraMover();			
		};
	}
}