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

        static bool get_key(Key key);
    };
}
