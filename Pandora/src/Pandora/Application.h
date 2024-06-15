#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace Pandora {
	class Application {
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		std::unique_ptr<Window> mWindow;
		bool mRunning = true;
	};

	//to be defined in the client
	Application* CreateApplication();
}