#pragma once

namespace gv
{
	namespace Engine
	{
		class IInputController
		{
		public:
			virtual void checkInput() = 0;
			virtual ~IInputController() = 0;
		};
	}
}