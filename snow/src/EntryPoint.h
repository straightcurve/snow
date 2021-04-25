//
// Created by tony on 24.04.2021.
//

#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "Application.h"

int main(int argc, char **argv) {
    Snow::Log::init();
    SNOW_CORE_INFO("Hello!");

    auto app = Snow::CreateApplication();
    app->run();
    delete app;

    return 0;
}

#endif //ENTRYPOINT_H
