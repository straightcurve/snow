#pragma once

#include <Snow/Window.h>
#include <Snow/Events/Event.h>

namespace Snow {
    class Application {
    public:
        Application();

        /**
         * marked virtual because we need to
         * clean up other systems e.g. Resources
         */
        virtual ~Application();

        void run();

        virtual void update() = 0;

        Event exit;

    private:
        bool is_running = true;
        std::unique_ptr<Snow::Impl::Window> window;
    };

    extern Application *CreateApplication();
}
