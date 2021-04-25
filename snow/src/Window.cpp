//
// Created by Sweet Acid on 25.04.2021.
//

#include "Window.h"

namespace Snow {
    static bool s_glfw_initialized;

    Window::Window() {
        if (!s_glfw_initialized) {
            int success = glfwInit();
            SNOW_CORE_ASSERT(success, "Failed to initialize GLFW..");
            s_glfw_initialized = true;
        }

        window = glfwCreateWindow(1280, 720, "Snow", nullptr, nullptr);
        glfwMakeContextCurrent(window);
        glfwSwapInterval(vsync);
    }

    Window::~Window() {
        if (!s_glfw_initialized)
            return;

        glfwDestroyWindow(window);
    }

    bool Window::get_vsync() {
        return vsync;
    }

    void Window::set_vsync(bool enabled) {
        vsync = enabled;

        if (!s_glfw_initialized)
            return;

        glfwSwapInterval(enabled);
    }

    void Window::update() {
        SNOW_CORE_ASSERT(s_glfw_initialized, "Tried to update window before GLFW has been initialized!");

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}
