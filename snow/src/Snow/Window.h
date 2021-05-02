//
// Created by Sweet Acid on 25.04.2021.
//

#pragma once

#include <Snow/Core.h>
#include <GLFW/glfw3.h>

namespace Snow::Impl {
    class Window {
    private:
        struct Callbacks {
            std::function<void()> closed;
        };
        Callbacks m_callbacks;
        GLFWwindow *m_window = nullptr;
        bool m_vsync = true;

        void update_viewport_size();
    public:
        Window();

        ~Window();

        inline bool get_vsync() {
            return m_vsync;
        }

        inline GLFWwindow *get_window() {
            return m_window;
        }

        void set_vsync(bool enabled);

        void on_window_closed(std::function<void()>);

        void update();
    };
}
