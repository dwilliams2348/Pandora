#include "Application.h"

#include "Pandora/Events/ApplicationEvent.h"
#include "Pandora/Log.h"

namespace Pandora {
	Application::Application() {

	}

	Application::~Application() {

	}

	void Application::Run() {
		WindowResizeEvent e(1280, 720);
		LogEngineTrace(e.ToString().c_str());

		while (true);
	}
}