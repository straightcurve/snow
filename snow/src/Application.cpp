#include "Application.h"

namespace Snow {
    Application::Application() {
        window = std::make_unique<Window>();
    }

    void Application::run() {
        while (is_running)
            if (window != nullptr)
                window->update();
    }
}
