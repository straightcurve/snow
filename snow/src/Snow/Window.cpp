//
// Created by Sweet Acid on 25.04.2021.
//

#include <Snow/Window.h>
#include <glad/glad.h>
#include <Snow/GUI/GUI.h>

namespace Snow::Impl {
    static bool s_glfw_initialized;

    Window::Window() {
        if (!s_glfw_initialized) {
            s_glfw_initialized = glfwInit();
            SNOW_CORE_ASSERT(s_glfw_initialized, "Failed to initialize GLFW..");
        }

        m_window = glfwCreateWindow(1280, 720, "Snow", nullptr, nullptr);
        glfwMakeContextCurrent(m_window);
        glfwSetWindowUserPointer(m_window, &m_callbacks);
        set_vsync(m_vsync);

        glfwSetWindowCloseCallback(m_window, [](auto window) {
            Callbacks &callbacks = *(Callbacks *) glfwGetWindowUserPointer(window);
            if (callbacks.closed != nullptr)
                callbacks.closed();
        });

        int glad_status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        SNOW_CORE_ASSERT(glad_status, "Failed to initialize graphics API..");

        GUI::init(m_window);
    }

    Window::~Window() {
        if (!s_glfw_initialized)
            return;

        GUI::shutdown();
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    void Window::set_vsync(bool enabled) {
        m_vsync = enabled;

        if (!s_glfw_initialized)
            return;

        glfwSwapInterval(enabled);
    }

    void Window::update() {
        SNOW_CORE_ASSERT(s_glfw_initialized, "Tried to update window before GLFW has been initialized!");

        glfwPollEvents();

        //  temporary
        int display_w, display_h;
        glfwGetFramebufferSize(m_window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w,
                     clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        GUI::update();
        glfwSwapBuffers(m_window);
    }

    void Window::on_window_closed(std::function<void()> callback) {
        m_callbacks.closed = std::move(callback);
    }
}
