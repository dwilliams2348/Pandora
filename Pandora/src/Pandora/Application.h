#pragma once

#include "Pandora/Core.h"
#include "Pandora/LayerStack.h"
#include "Pandora/Events/Event.h"
#include "Pandora/Events/ApplicationEvent.h"

#include "Window.h"

namespace Pandora {
	class Application {
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

	private:
		bool OnWindowClosed(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> mWindow;
		bool mRunning = true;
		LayerStack mLayerStack;
	};

	//to be defined in the client
	Application* CreateApplication();
}