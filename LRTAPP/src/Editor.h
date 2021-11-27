#pragma once


namespace Editor
{
	class App
	{
	public:
		App();
		~App();
		App(const App&) = delete;
		App& operator=(const App&) = delete;
	public:
		void Tick();
	private:
		
	};
}


