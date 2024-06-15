#include "PEpch.h"
#include "Application.h"

#include "Pandora/Events/ApplicationEvent.h"
#include "Pandora/Log.h"

namespace Pandora {
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application::Application() {
		mWindow = std::unique_ptr<Window>(Window::Create());
		mWindow->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application() {

	}

	void Application::Run() {
		WindowResizeEvent e(1280, 720);
		LogEngineTrace(e.ToString().c_str());

		while (mRunning) {
			for (Layer* layer : mLayerStack)
				layer->OnUpdate();

			mWindow->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClosed));

		LogEngineTrace("%s", e.ToString().c_str());

		for (auto it = mLayerStack.end(); it != mLayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer){
		mLayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay){
		mLayerStack.PushOverlay(overlay);
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e) {
		mRunning = false;

		return true;
	}
}