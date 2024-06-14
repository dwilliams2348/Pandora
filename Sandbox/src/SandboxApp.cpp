#include <Pandora.h>

class Sandbox : public Pandora::Application {
public:
	Sandbox() {}
	~Sandbox() {}
};

Pandora::Application* Pandora::CreateApplication() {
	return new Sandbox();
}