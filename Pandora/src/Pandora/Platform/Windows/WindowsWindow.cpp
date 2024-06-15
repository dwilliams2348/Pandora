#include "PEpch.h"
#include "WindowsWindow.h"

#include "Pandora/Events/ApplicationEvent.h"
#include "Pandora/Events/KeyEvent.h"
#include "Pandora/Events/MouseEvent.h"

namespace Pandora {
	static bool sGLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description) {
		LogEngineError("GLFW Error (%d): %s", error, description);
	}

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
			glfwSetErrorCallback(GLFWErrorCallback);

			sGLFWInitialized = true;
		}

		//window hints
		//no default rendering client, we hook up vulkan to it later on
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		//resizing will break swapchain until swapchain resize is implemented
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); //TODO: change this to true when swapchain resize works

		mWindow = glfwCreateWindow((int)mData.width, (int)mData.height, mData.title.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(mWindow, &mData);
		SetVSync(true);

		//set GLFW callbacks
		glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* window, int width, int height) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.width = width;
				data.height = height;

				WindowResizeEvent event(width, height);
				data.eventCallback(event);
			});

		glfwSetWindowCloseCallback(mWindow, [](GLFWwindow* window) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.eventCallback(event);
			});

		glfwSetKeyCallback(mWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.eventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.eventCallback(event);
					break;
				}
				}
			});

		glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.eventCallback(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(mWindow, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.eventCallback(event);
			});

		glfwSetCursorPosCallback(mWindow, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.eventCallback(event);
			});
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