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
            std::function<void(int width, int height)> resized;
        };
        Callbacks m_callbacks;
        GLFWwindow *m_window = nullptr;
        bool m_vsync = true;

        void update_viewport_size();
        static void s_update_viewport_size(int width, int height);
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
