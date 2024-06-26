#pragma once

#include "Pandora/Core.h"
#include "Pandora/Events/Event.h"

namespace Pandora {
	class Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return mDebugName; }

	private:
		std::string mDebugName;
	};
}