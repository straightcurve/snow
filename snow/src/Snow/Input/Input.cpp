//
// Created by Sweet Acid on 27.04.2021.
//

#include <Snow/Window.h>
#include "Input.h"

namespace Snow {
    bool Input::get_key(Key key) {
        auto instance = get_instance();
        auto window = instance->m_window;
        if (window == nullptr) return false;

        return glfwGetKey(window->get_window(), static_cast<int>(key));
    }
}