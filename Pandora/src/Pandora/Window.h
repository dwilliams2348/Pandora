#pragma once

#include "PEpch.h"

#include "Pandora/Core.h"
#include "Pandora/Events/Event.h"

namespace Pandora {
	struct WindowProps {
		std::string title;
		unsigned width, height;

		WindowProps(const std::string& title = "Pandora Engine",
			unsigned width = 1280,
			unsigned height = 720)
			: title(title), width(width), height(height) {}
	};

	//interface representing a desktop system based Window
	class Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned GetWidth() const = 0;
		virtual unsigned GetHeight() const = 0;

		//attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}