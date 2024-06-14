#include "Log.h"

namespace Pandora {
	std::shared_ptr<Logger> Log::mEngineLogger = std::make_shared<Logger>();
	std::shared_ptr<Logger> Log::mClientLogger = std::make_shared<Logger>();

	void Log::Init() {
		mEngineLogger->SetInitialString("Engine: ");
		mEngineLogger->SetPriority(Logger::TracePriority);

		mClientLogger->SetInitialString("Client: ");
		mClientLogger->SetPriority(Logger::TracePriority);
	}
}