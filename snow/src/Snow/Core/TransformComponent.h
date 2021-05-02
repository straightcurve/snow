//
// Created by Sweet Acid on 01.05.2021.
//

#pragma once

#include <pch.h>

namespace Snow {
    struct TransformComponent {
        glm::vec2 position = glm::vec2(0.f);
        glm::vec2 scale = glm::vec2(200.f);
        float rotation = 0.f;
    };
}
