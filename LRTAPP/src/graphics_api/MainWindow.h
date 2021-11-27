#pragma once
#include "LRTMath.h"
#include <GLFW/glfw3.h>

namespace Editor
{
	class Window
	{
	public:
		Window(u32 width, u32 height, const char* win_name, bool resizable);

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		~Window();
	public:
		bool ShouldClose();

		// causes the ShouldClose() to retrun true;
		void CloseWindow(); 

		inline u32 Width()
		{
			int width, height;
			glfwGetWindowSize(m_glfwwindow, &width, &height);

			return width;
		}
		inline u32 Height()
		{
			int width, height;
			glfwGetWindowSize(m_glfwwindow, &width, &height);

			return height;
		}

		void SetMouseVisibility(bool visible);

		bool KeyIsPress(u32 key);

		/*
		inline glm::vec2 MousePos()
		{
			double xpos, ypos;
			glfwGetCursorPos(m_glfwwindow, &xpos, &ypos);

			return { (float)xpos, (float)ypos };
		}
		*/

		void Resize(u32 width, u32 height);

		void SwapBuffers();
		void PollEvents();

	private:
		GLFWwindow* m_glfwwindow;
	};
}
