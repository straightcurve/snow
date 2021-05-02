//
// Created by Sweet Acid on 29.04.2021.
//

#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "Texture.h"
#include "Shader.h"

namespace Snow {
    class SpriteRenderer {
    public:
        SpriteRenderer(Shader &shader);

        ~SpriteRenderer();

        void draw(
                Texture2D &texture, glm::vec2 position,
                glm::vec2 size = glm::vec2(10.0f, 10.0f),
                float angle = 0.0f, glm::vec3 color = glm::vec3(1.0f)
        );

    private:
        Shader shader;
        uint32_t vao = 0, vbo = 0, ebo = 0;

        constexpr static float vertices[] = {
                // pos      // tex
                0.0f, 1.0f, 0.0f, 1.0f,
                1.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 0.0f,
                1.0f, 1.0f, 1.0f, 1.0f,
        };

        constexpr static uint32_t triangles[] = {
                0, 1, 2,
                0, 3, 1,
        };

        void init();
    };
}
