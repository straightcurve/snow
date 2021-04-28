//
// Created by Sweet Acid on 27.04.2021.
//

#pragma once

#include "Key.h"
#include <Snow/Application.h>
#include <Snow/Window.h>

namespace Snow {
    class Input {
        friend class Application;

    private:
        Snow::Impl::Window *m_window;

        inline static void set_window(Snow::Impl::Window *window) {
            auto instance = get_instance();
            instance->m_window = window;
        }

        inline static Input *s_instance;

        inline static Input *get_instance() {
            if (s_instance == nullptr)
                s_instance = new Input();
            return s_instance;
        }

    public:
        ~Input() {
            delete s_instance;
        }

        static std::pair<double, double> get_mouse_position();

        static bool is_key_held_down(Key);

        static bool is_key_pressed(Key);

        static bool is_key_released(Key);

        /**
         * @li 0 - left click
         * @li 1 - right click
         * @li 2 - middle click
         * @param button
         * @return
         */
        static bool is_mouse_button_pressed(int);
    };
}
