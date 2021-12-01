#include "OpenGL.h"
#include "MainWindow.h"
#include "Log.h"

namespace Editor
{
	void window_size_callback(GLFWwindow* window, int width, int height)
	{
		glCall(glViewport(0, 0, width, height));
	}

	Window::Window(u32 width, u32 height, const char* win_name, bool resizable)
	{
		// Set GLFW error callback
		glfwSetErrorCallback(Logger::LogGLFW_Error);

		// Initialize GLFW
		if (!glfwInit())
		{
			Logger::LogError("GLFW could not Initialize.");
			// TODO: throw exception
		}

		// Hits
		// OpenGL version 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

		// using the core profile
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, resizable ? GL_TRUE : GL_FALSE);

		m_glfwwindow = glfwCreateWindow(width, height, win_name, NULL, NULL);
		if (!m_glfwwindow)
		{
			Logger::LogError("Window creation failed.");
			glfwTerminate();
			// TODO: throw exception
		}

		glfwSetWindowSizeCallback(m_glfwwindow, window_size_callback);
		glfwMakeContextCurrent(m_glfwwindow);

		// Initialize OpenGL
		if (!InitOpenGL())
		{
			Logger::LogError("OpenGL could not Initialize.");
			// TODO: throw exception
		}
		// print OpenGL version
		Logger::LogInfo("Using OpenGL");
		Logger::LogInfo((const char*)glGetString(GL_VERSION));

		glfwSwapInterval(1);

		glCall(glViewport(0, 0, width, height));

	}

	Window::~Window()
	{
		glfwDestroyWindow(m_glfwwindow);
		glfwTerminate();
	}

	bool Window::ShouldClose()
	{
		return glfwWindowShouldClose(m_glfwwindow);
	}

	void Window::CloseWindow()
	{
		glfwSetWindowShouldClose(m_glfwwindow, true);
	}

	void Window::SetMouseVisibility(bool visible)
	{
		glfwSetInputMode(m_glfwwindow, GLFW_CURSOR, visible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
	}

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(m_glfwwindow);
	}

	void Window::PollEvents()
	{
		glfwPollEvents();
	}

	bool Window::KeyIsPress(u32 key)
	{
		return glfwGetKey(m_glfwwindow, (int)key) == GLFW_PRESS;
	}

	void Window::Resize(u32 width, u32 height)
	{
		glfwSetWindowSize(m_glfwwindow, (int)width, (int)height);

		glCall(glViewport(0, 0, width, height));
	}
}
