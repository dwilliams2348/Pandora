#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Pandora {
	class Application {
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//to be defined in the client
	Application* CreateApplication();
}