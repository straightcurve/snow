#include <iostream>
#include <Snow.h>

class Sandbox : public Snow::Application {
public:
    Sandbox() = default;

    void update() override {

    }
};

Snow::Application *Snow::CreateApplication() {
    return new Sandbox();
}
