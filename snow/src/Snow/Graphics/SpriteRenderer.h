//
// Created by Sweet Acid on 29.04.2021.
//

#pragma once

#include <glm.hpp>
#include <Snow/Core/SpriteComponent.h>
#include <Snow/Core/TransformComponent.h>
#include "Texture.h"
#include "Shader.h"

namespace Snow {
    class SpriteRenderer {
    public:
        SpriteRenderer() = default;

        ~SpriteRenderer();

        void draw(
                const SpriteComponent &sprite,
                const TransformComponent &transform,
                Shader &shader
        ) const;

    private:
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
