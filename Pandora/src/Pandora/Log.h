#pragma once

#include <memory>

#include "Core.h"
#include "Logger/Logger.h"

namespace Pandora {
	class Log {
	public:
		static void Init();

		inline static std::shared_ptr<Logger>& GetEngineLogger() { return mEngineLogger; }
		inline static std::shared_ptr<Logger>& GetClientLogger() { return mClientLogger; }

	private:
		static std::shared_ptr<Logger> mEngineLogger;
		static std::shared_ptr<Logger> mClientLogger;
	};
}

//Core logging macros
#define LogEngineTrace(...) ::Pandora::Log::GetEngineLogger()->Trace(__VA_ARGS__)
#define LogEngineDebug(...) ::Pandora::Log::GetEngineLogger()->Debug(__VA_ARGS__)
#define LogEngineInfo(...) ::Pandora::Log::GetEngineLogger()->Info(__VA_ARGS__)
#define LogEngineWarn(...) ::Pandora::Log::GetEngineLogger()->Warn(__VA_ARGS__)
#define LogEngineError(...) ::Pandora::Log::GetEngineLogger()->Error(__VA_ARGS__)
#define LogEngineFatal(...) ::Pandora::Log::GetEngineLogger()->Fatal(__VA_ARGS__)

#define LogTrace(...) ::Pandora::Log::GetClientLogger()->Trace(__VA_ARGS__)
#define LogDebug(...) ::Pandora::Log::GetClientLogger()->Debug(__VA_ARGS__)
#define LogInfo(...) ::Pandora::Log::GetClientLogger()->Info(__VA_ARGS__)
#define LogWarn(...) ::Pandora::Log::GetClientLogger()->Warn(__VA_ARGS__)
#define LogError(...) ::Pandora::Log::GetClientLogger()->Error(__VA_ARGS__)
#define LogFatal(...) ::Pandora::Log::GetClientLogger()->Fatal(__VA_ARGS__)