//
// Created by Sweet Acid on 02.05.2021.
//

#pragma once

#include <glm.hpp>
#include <ext/matrix_clip_space.hpp>
#include <ext/matrix_transform.hpp>
#include <Snow/Core/CameraComponent.h>

namespace Snow {
    class CameraSystem {
    private:
        static void recalculate_view_matrix(
                CameraComponent &camera,
                TransformComponent &transform
        ) {
            camera.view = glm::inverse(glm::translate(
                    glm::mat4(1.f),
                    glm::vec3(transform.position, 1.f)
            ));
        }

    public:
        static void update(entt::registry &registry) {
            auto view = registry.view<CameraComponent, TransformComponent>();

            for (auto e : view) {
                auto &camera = registry.get<CameraComponent>(e);
                auto &transform = registry.get<TransformComponent>(e);
                recalculate_view_matrix(camera, transform);
            }
        }
    };
}
