#pragma once

#include "mCamera.h"

namespace gv
{
	namespace Model
	{


		class CameraMover
		{
			mCamera* _camera;
			int _subscriptiomId;
			void cameraTryPropertyChanged(const CameraPropChangedArgs&);

		public:
			CameraMover(mCamera* camera);
			~CameraMover();			
		};
	}
}