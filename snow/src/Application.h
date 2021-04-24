#ifndef SNOW_APPLICATION_H
#define SNOW_APPLICATION_H

namespace Snow {
    class Application {
    public:
        Application();

        ~Application();

        void run();
    };

    extern Application *CreateApplication();
}

#endif //SNOW_APPLICATION_H
