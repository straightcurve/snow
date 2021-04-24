#include <iostream>
#include <Snow.h>

class Sandbox : public Snow::Application {
public:
    Sandbox() {

    }

    ~Sandbox() {

    }
};

Snow::Application *Snow::CreateApplication() {
    return new Sandbox();
}
