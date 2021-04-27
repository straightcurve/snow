//
// Created by Sweet Acid on 25.04.2021.
//

#include <Snow/Window.h>

namespace Snow {
    static bool s_glfw_initialized;

    Window::Window() {
        if (!s_glfw_initialized) {
            s_glfw_initialized = glfwInit();
            SNOW_CORE_ASSERT(s_glfw_initialized, "Failed to initialize GLFW..");
        }

        m_window = glfwCreateWindow(1280, 720, "Snow", nullptr, nullptr);
        glfwMakeContextCurrent(m_window);
        glfwSetWindowUserPointer(m_window, &m_callbacks);
        set_vsync(vsync);

        glfwSetWindowCloseCallback(m_window, [](auto window) {
            Callbacks &callbacks = *(Callbacks *) glfwGetWindowUserPointer(window);
            if (callbacks.closed != nullptr)
                callbacks.closed();
        });
    }

    Window::~Window() {
        if (!s_glfw_initialized)
            return;

        glfwDestroyWindow(m_window);
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
        glfwSwapBuffers(m_window);
    }

    void Window::on_window_closed(std::function<void()> callback) {
        m_callbacks.closed = std::move(callback);
    }
}
