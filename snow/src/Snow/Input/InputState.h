//
// Created by Sweet Acid on 27.04.2021.
//

#pragma once
#include <GLFW/glfw3.h>

namespace Snow {
    enum class InputState: int {
        Pressed = GLFW_PRESS,
        Released = GLFW_RELEASE,
        Held = GLFW_REPEAT,
    };
}