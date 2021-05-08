//
// Created by Sweet Acid on 02.05.2021.
//

#pragma once

#include <Snow/Graphics/SpriteRenderer.h>
#include <entt.hpp>
#include <Snow/Resources.h>
#include <Snow/CameraSystem.h>

namespace Snow {
    class SpriteRendererSystem {
        SpriteRenderer renderer;

        //  temporary
        Shader shader { };

    public:
        SpriteRendererSystem(entt::registry &registry) {
            shader = Resources::load_shader(
                    "assets/shaders/base/vertex.shader",
                    "assets/shaders/x11/fragment.glsl",
                    nullptr,
                    "base"
            );

            shader.use();
            shader.set_int("image", 0);

            //  temporary
            auto view = registry.view<CameraComponent>();
            const auto camera = view.get<CameraComponent>(view.front());

            //  FIXME: we shouldn't set the matrices here...
            shader.set_mat4("projection", camera.projection);
            shader.set_mat4("view", camera.view);
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
