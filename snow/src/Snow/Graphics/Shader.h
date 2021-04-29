//
// Created by Sweet Acid on 29.04.2021.
//
#pragma once

#include <pch.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

namespace Snow {
    class Shader {
    public:
        unsigned int id;

        Shader() = default;

        Shader &use();

        void compile(
                const char *vertex_code,
                const char *fragment_code,
                const char *geometry_code = nullptr
        );

        void set_float(const char *name, float value, bool use_shader = false);

        void set_int(const char *name, int value, bool use_shader = false);

        void set_vec2f(const char *name, float x, float y, bool use_shader = false);

        void set_vec2f(const char *name, const glm::vec2 &value, bool use_shader = false);

        void set_vec3f(const char *name, float x, float y, float z, bool use_shader = false);

        void set_vec3f(const char *name, const glm::vec3 &value, bool use_shader = false);

        void set_vec4f(const char *name, float x, float y, float z, float w, bool use_shader = false);

        void set_vec4f(const char *name, const glm::vec4 &value, bool use_shader = false);

        void set_mat4(const char *name, const glm::mat4 &matrix, bool use_shader = false);

    private:
        static void check_compile_errors(unsigned int object, const std::string &type);
    };
}
