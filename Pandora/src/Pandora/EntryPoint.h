#pragma once

#ifdef PE_PLATFORM_WINDOWS

	extern Pandora::Application* Pandora::CreateApplication();

	int main(int argc, char* argv) {
		auto app = Pandora::CreateApplication();
		app->Run();
		delete app;
	}

#else
#error Only Windows platform is supported.
#endif 