#include "graphics_api/OpenGL.h"
#include "graphics_api/MainWindow.h"
#include "Editor.h"


namespace Editor
{
	App::App()
	{

	}

	App::~App()
	{

	}

	void App::Tick()
	{
		glCall(glClearColor(0.5f, 0.7f, 0.4f, 1.0f));
		glCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}

}
