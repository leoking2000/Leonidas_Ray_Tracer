#include "LRT.h"
#include "graphics_api/MainWindow.h"
#include "Editor.h"

int main()
{
	using namespace Editor;

	Window win(800, 600, "LRT Editor", false);
	App app;

	while (!win.ShouldClose())
	{
		win.PollEvents();
		app.Tick();
		win.SwapBuffers();
	}
	

	return 0;
}