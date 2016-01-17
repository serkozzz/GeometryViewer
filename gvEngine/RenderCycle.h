#pragma once


namespace gv
{
	class IInputController;

	namespace Engine
	{
		int launchRenderCycle(IInputController* inputController);
	}
}