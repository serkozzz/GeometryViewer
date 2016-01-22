#pragma once

struct GLFWwindow;

namespace gv
{
	namespace Engine
	{
		class WindowManager
		{
			int _width;
			int _height;
			GLFWwindow* _window;
		public:
			void createWindow(int width, int height);
			void destroyWindow();
			GLFWwindow* getWindow();

			int getWidth()
			{
				return _width;
			}

			int getHeight()
			{
				return _height;
			}
		};
	}
}