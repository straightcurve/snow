//
// Created by Sweet Acid on 01.05.2021.
//

#pragma once

#include <GLFW/glfw3.h>
#include <Snow/Window.h>

namespace Snow {
    class Renderer {
    public:
        static void swap_buffers(Snow::Impl::Window* window) {
            SNOW_CORE_ASSERT(window != nullptr, "Attempted to swap buffers but there's no window..?");

            auto glfw_window = window->get_window();
            SNOW_CORE_ASSERT(glfw_window != nullptr, "Attempted to swap buffers but there's no window..?");

            glfwSwapBuffers(glfw_window);
        }
    };
}
