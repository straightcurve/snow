//
// Created by Sweet Acid on 29.04.2021.
//

#include "SpriteRenderer.h"
#include <glad/glad.h>

namespace Snow {
    SpriteRenderer::SpriteRenderer() {
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
                     GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangles), triangles,
                     GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(
                0, 4, GL_FLOAT,
                GL_FALSE, 4 * sizeof(float),
                nullptr
        );
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    SpriteRenderer::~SpriteRenderer() {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
    }

    void SpriteRenderer::draw(
            const SpriteComponent &sprite,
            const TransformComponent &transform,
            Shader &shader
    ) const {
        shader.use();
        glm::mat4 model = glm::mat4(1.0f);

        //  scale -> rotation -> translation
        //  we do it reversed because reasons
        model = glm::translate(model, glm::vec3(transform.position, 0.0f));

        // move origin of rotation to center of quad
        model = glm::translate(model, glm::vec3(
                0.5f * transform.scale,
                0.0f)
        );
        model = glm::rotate(
                model,
                glm::radians(transform.rotation),
                glm::vec3(0.0f, 0.0f, 1.0f)
        );

        // move origin back
        model = glm::translate(model, glm::vec3(
                -0.5f * transform.scale,
                0.0f)
        );

        model = glm::scale(model, glm::vec3(transform.scale, 1.0f));

        shader.set_mat4("model", model);
        shader.set_vec3f("spriteColor", sprite.color);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, sprite.texture);

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }
}
