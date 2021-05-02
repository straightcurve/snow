//
// Created by Sweet Acid on 02.05.2021.
//

#pragma once

#include <glm.hpp>
#include <ext/matrix_clip_space.hpp>

namespace Snow {
    class Camera {
    public:
        glm::mat4 projection { };

        explicit Camera(float size = 1) {
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
