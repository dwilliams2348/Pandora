#pragma once

#ifdef PE_PLATFORM_WINDOWS

	extern Pandora::Application* Pandora::CreateApplication();

	int main(int argc, char* argv) {
		Pandora::Log::Init();
		LogEngineTrace("Trace test");
		LogEngineDebug("Debug test");
		LogEngineInfo("Info test");
		LogEngineWarn("Warn test");
		LogEngineError("Error test");
		LogEngineFatal("Fatal test");

		LogTrace("Trace test");
		LogDebug("Debug test");
		LogInfo("Info test");
		LogWarn("Warn test");
		LogError("Error test");
		LogFatal("Fatal test");

		auto app = Pandora::CreateApplication();
		app->Run();
		delete app;
	}

#else
#error Only Windows platform is supported.
#endif 