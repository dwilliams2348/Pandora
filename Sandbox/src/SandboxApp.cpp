#include <Pandora.h>

class ExampleLayer : public Pandora::Layer {
public:
	ExampleLayer()
		: Layer("Example") {

	}

	void OnUpdate() override {
		LogInfo("ExampleLayer::OnUpdate");
	}

	void OnEvent(Pandora::Event& event) override {
		LogTrace("%s", event.ToString().c_str());
	}
};

class Sandbox : public Pandora::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}
};

Pandora::Application* Pandora::CreateApplication() {
	return new Sandbox();
}