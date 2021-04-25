//
// Created by Sweet Acid on 25.04.2021.
//

#pragma once

#include <Snow/Core.h>
#include <GLFW/glfw3.h>

namespace Snow {
    class Window {
    private:
        GLFWwindow *window = nullptr;
        bool vsync = true;
    public:
        Window();

        ~Window();

        bool get_vsync();

        void set_vsync(bool enabled);

        void update();
    };
}
