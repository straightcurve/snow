#pragma once

#include <Snow/Window.h>
#include <Snow/Events/Event.h>

namespace Snow {
    class Application {
    public:
        Application();

        ~Application();

        void run();

        Event exit;

    private:
        bool is_running = true;
        std::unique_ptr<Snow::Impl::Window> window;
    };

    extern Application *CreateApplication();
}
