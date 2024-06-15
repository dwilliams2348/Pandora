#include "PEpch.h"
#include "WindowsWindow.h"

namespace Pandora {
	static bool sGLFWInitialized = false;

	Window* Window::Create(const WindowProps& props) {
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props){
		LogEngineInfo("Initializing windowing...");
		Init(props);
	}

	WindowsWindow::~WindowsWindow() {
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props) {
		mData.title = props.title;
		mData.width = props.width;
		mData.height = props.height;

		LogEngineTrace("Creating window %s (%d, %d)", mData.title.c_str(), mData.width, mData.height);

		if (!sGLFWInitialized) {
			int success = glfwInit();
			ENGINE_ASSERT(success, "Could not initialize GLFW.");

			sGLFWInitialized = true;
		}

		//window hints
		//no default rendering client, we hook up vulkan to it later on
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		//resizing will break swapchain until swapchain resize is implemented
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); //TODO: change this to true when swapchain resize works

		mWindow = glfwCreateWindow((int)mData.width, (int)mData.height, mData.title.c_str(), nullptr, nullptr);
		SetVSync(true);
	}

	void WindowsWindow::Shutdown() {
		LogEngineInfo("Shutting down windowing...");

		glfwDestroyWindow(mWindow);
		glfwTerminate();
	}

	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
	}

	void WindowsWindow::SetVSync(bool enabled) {
		if(enabled){
			//TODO: hook this up to vulkan when creating the pipeline
		}
		else{
			//TODO: hook this up to vulkan when creating the pipeline
		}

		mData.vSync = enabled;
	}

	bool WindowsWindow::IsVSync() const{
		return mData.vSync;
	}
}