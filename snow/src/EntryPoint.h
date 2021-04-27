//
// Created by tony on 24.04.2021.
//

#pragma once

#include <Snow/Application.h>

int main(int argc, char **argv) {
    Snow::Log::init();
    SNOW_CORE_INFO("Look! It started snowing!");

    auto app = Snow::CreateApplication();
    app->run();
    delete app;

    return 0;
}
