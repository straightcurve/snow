//
// Created by Sweet Acid on 02.05.2021.
//

#pragma once

#include <Snow/Graphics/SpriteRenderer.h>
#include <entt.hpp>
#include <Snow/Resources.h>

namespace Snow {
    class SpriteRendererSystem {
        SpriteRenderer renderer;

        //  temporary
        Shader shader { };

    public:
        SpriteRendererSystem() {
            shader = Resources::load_shader(
                    "assets/shaders/base/vertex.shader",
                    "assets/shaders/base/fragment.shader",
                    nullptr,
                    "base"
            );
            glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(1280),
                                              static_cast<float>(720), 0.0f,
                                              -1.0f,
                                              1.0f);
            shader.use();
            shader.set_int("image", 0);
            shader.set_mat4("projection", projection);
        }

        void update(entt::registry &registry) {
            auto view = registry.view<TransformComponent, SpriteComponent>();
            for (auto e : view) {
                auto &transform = view.get<TransformComponent>(e);
                auto &sprite = view.get<SpriteComponent>(e);
                renderer.draw(sprite, transform, shader);
            }
        }
    };
}
