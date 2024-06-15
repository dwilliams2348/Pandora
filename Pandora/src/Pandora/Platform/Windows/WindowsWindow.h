#pragma once

#include "Pandora/Window.h"

#include <GLFW/glfw3.h>

namespace Pandora {
	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned GetWidth() const override { return mData.width; }
		inline unsigned GetHeight() const override { return mData.height; }

		inline void SetEventCallback(const EventCallbackFn& callback) override { mData.eventCallback = callback; }
		void SetVSync(bool enable) override;
		bool IsVSync() const override;

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:
		GLFWwindow* mWindow;

		struct WindowData {
			std::string title;
			unsigned width, height;
			bool vSync;

			EventCallbackFn eventCallback;
		};

		WindowData mData;
	};
}