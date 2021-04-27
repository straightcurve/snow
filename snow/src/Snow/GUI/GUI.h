//
// Created by Sweet Acid on 27.04.2021.
//

#pragma once

#include <GLFW/glfw3.h>

namespace Snow {

    class GUI {
    public:
        static void init(GLFWwindow *);

        static void shutdown();

        static void update();
    };
}
