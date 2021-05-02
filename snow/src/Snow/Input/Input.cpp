//
// Created by Sweet Acid on 27.04.2021.
//

#include <Snow/Window.h>
#include "Input.h"
#include "InputState.h"

namespace Snow {
    bool Input::is_key_held_down(Key key) {
        auto instance = get_instance();
        auto window = instance->m_window;
        if (window == nullptr) return false;

        return glfwGetKey(window->get_window(), static_cast<int>(key)) == static_cast<int>(InputState::Held);
    }

    bool Input::is_key_pressed(Key key) {
        auto instance = get_instance();
        auto window = instance->m_window;
        if (window == nullptr) return false;

        return glfwGetKey(window->get_window(), static_cast<int>(key)) == static_cast<int>(InputState::Pressed);
    }

    bool Input::is_key_released(Key key) {
        auto instance = get_instance();
        auto window = instance->m_window;
        if (window == nullptr) return false;

        return glfwGetKey(window->get_window(), static_cast<int>(key)) == static_cast<int>(InputState::Released);
    }

    bool Input::is_mouse_button_pressed(int button) {
        auto instance = get_instance();
        auto window = instance->m_window;
        if (window == nullptr) return false;

        return glfwGetMouseButton(window->get_window(), button) == static_cast<int>(InputState::Pressed);
    }

    /**
     * @details
     * ALLOCATIONS.
     *
     * @param position
     */
    std::pair<double, double> Input::get_mouse_position() {
        auto instance = get_instance();

        SNOW_CORE_ASSERT(instance->m_window != nullptr, "Input system has not been initialized!");

        std::pair<double, double> pos;
        glfwGetCursorPos(instance->m_window->get_window(), &pos.first, &pos.second);

        return pos;
    }
}