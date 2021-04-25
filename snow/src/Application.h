#pragma once

namespace Snow {
    class Application {
    public:
        Application();

        ~Application();

        void run();
    };

    extern Application *CreateApplication();
}
