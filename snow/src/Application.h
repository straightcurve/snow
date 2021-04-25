#pragma once

#include "Window.h"

namespace Snow {
    class Application {
    public:
        Application();

        ~Application() = default;

        void run();

    private:
        bool is_running = true;
        std::unique_ptr<Window> window;
    };

    extern Application *CreateApplication();
}
