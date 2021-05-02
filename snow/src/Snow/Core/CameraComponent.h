//
// Created by Sweet Acid on 02.05.2021.
//

#pragma once

#include <vec3.hpp>
#include <ext/matrix_float4x4.hpp>
#include <ext/matrix_clip_space.hpp>

namespace Snow {
    struct CameraComponent {
        glm::mat4 projection { };
        glm::mat4 view = glm::mat4(1.f);

        explicit CameraComponent(float size = 1) {
            projection = glm::ortho(
                    0.0f,
                    static_cast<float>(1280 * size),
                    static_cast<float>(720 * size), 0.0f,
                    -1.0f,
                    1.0f
            );
        };
    };
}
