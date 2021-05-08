//
// Created by Sweet Acid on 25.04.2021.
//

#include <Snow/Window.h>
#include <Snow/Core/Screen.h>
#include <glad/glad.h>

namespace Snow::Impl {
    static bool s_glfw_initialized;
    static bool s_glad_initialized;

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

        glfwSetFramebufferSizeCallback(m_window, [](auto window, int width, int height) {
            /**
             * FIXME: are we sure we want to do this here?
             */
            Screen::width = width;
            Screen::height = height;

            Callbacks &callbacks = *(Callbacks *) glfwGetWindowUserPointer(window);
            if (callbacks.resized != nullptr)
                callbacks.resized(width, height);
        });

        s_glad_initialized = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        SNOW_CORE_ASSERT(s_glad_initialized, "Failed to initialize graphics API..");

        update_viewport_size();
    }

    Window::~Window() {
        if (!s_glfw_initialized)
            return;

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

        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w,
                     clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Window::on_window_closed(std::function<void()> callback) {
        m_callbacks.closed = std::move(callback);
    }

    /**
     * should only run when the window is
     * initialized and/or the window is resized
     */
    void Window::update_viewport_size() {
        SNOW_CORE_ASSERT(s_glfw_initialized, "Tried to update viewport size before GLFW has been initialized!");
        SNOW_CORE_ASSERT(s_glad_initialized, "Tried to update viewport size before graphics API has been initialized!");

        int display_w, display_h;
        glfwGetFramebufferSize(m_window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
    }
}
