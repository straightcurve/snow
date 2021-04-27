#include <Snow/Application.h>

namespace Snow {
    Application::Application() {
        window = std::make_unique<Window>();

        window->on_window_closed([=]() {
            this->is_running = false;
        });
    }

    void Application::run() {
        while (is_running)
            window->update();
    }
}
