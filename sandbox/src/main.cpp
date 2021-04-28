#include <iostream>
#include <Snow.h>

class Sandbox : public Snow::Application {
public:
    Sandbox() = default;
};

Snow::Application *Snow::CreateApplication() {
    return new Sandbox();
}
