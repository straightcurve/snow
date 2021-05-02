//
// Created by Sweet Acid on 29.04.2021.
//

#include "Shader.h"
#include <glad/glad.h>

namespace Snow {
    void Shader::use() const {
        glUseProgram(this->id);
    }

    void Shader::compile(
            const char *vertex_code,
            const char *fragment_code,
            const char *geometry_code
    ) {
        unsigned int vertex_shader, fragment_shader, geometry_shader;
        vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &vertex_code, nullptr);
        glCompileShader(vertex_shader);
        check_compile_errors(vertex_shader, "VERTEX");

        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, &fragment_code, nullptr);
        glCompileShader(fragment_shader);
        check_compile_errors(fragment_shader, "FRAGMENT");

        if (geometry_code != nullptr) {
            geometry_shader = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(geometry_shader, 1, &geometry_code, nullptr);
            glCompileShader(geometry_shader);
            check_compile_errors(geometry_shader, "GEOMETRY");
        }

        this->id = glCreateProgram();
        glAttachShader(this->id, vertex_shader);
        glAttachShader(this->id, fragment_shader);
        if (geometry_code != nullptr)
            glAttachShader(this->id, geometry_shader);

        glLinkProgram(this->id);
        check_compile_errors(this->id, "PROGRAM");

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        if (geometry_code != nullptr)
            glDeleteShader(geometry_shader);
    }

    void Shader::set_float(const char *name, float value, bool use_shader) {
        if (use_shader)
            this->use();
        glUniform1f(glGetUniformLocation(this->id, name), value);
    }

    void Shader::set_int(const char *name, int value, bool use_shader) {
        if (use_shader)
            this->use();
        glUniform1i(glGetUniformLocation(this->id, name), value);
    }

    void Shader::set_vec2f(const char *name, float x, float y, bool use_shader) {
        if (use_shader)
            this->use();
        glUniform2f(glGetUniformLocation(this->id, name), x, y);
    }

    void Shader::set_vec2f(const char *name, const glm::vec2 &value, bool use_shader) {
        if (use_shader)
            this->use();
        glUniform2f(glGetUniformLocation(this->id, name), value.x, value.y);
    }

    void Shader::set_vec3f(const char *name, float x, float y, float z, bool use_shader) {
        if (use_shader)
            this->use();
        glUniform3f(glGetUniformLocation(this->id, name), x, y, z);
    }

    void Shader::set_vec3f(const char *name, const glm::vec3 &value, bool use_shader) {
        if (use_shader)
            this->use();
        glUniform3f(glGetUniformLocation(this->id, name), value.x, value.y, value.z);
    }

    void Shader::set_vec4f(const char *name, float x, float y, float z, float w, bool use_shader) {
        if (use_shader)
            this->use();
        glUniform4f(glGetUniformLocation(this->id, name), x, y, z, w);
    }

    void Shader::set_vec4f(const char *name, const glm::vec4 &value, bool use_shader) {
        if (use_shader)
            this->use();
        glUniform4f(glGetUniformLocation(this->id, name), value.x, value.y, value.z, value.w);
    }

    void Shader::set_mat4(const char *name, const glm::mat4 &matrix, bool use_shader) {
        if (use_shader)
            this->use();
        glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, false, glm::value_ptr(matrix));
    }

    void Shader::check_compile_errors(unsigned int object, const std::string &type) {
        int success;
        const int log_size = 1024;

        if (type != "PROGRAM") {
            glGetShaderiv(object, GL_COMPILE_STATUS, &success);
            if (success) return;

            char _log[log_size];
            glGetShaderInfoLog(object, log_size, nullptr, _log);

            std::stringstream ss;
            ss << type << " shader compilation failed\n" << _log << "\n";
            SNOW_CORE_ERROR(ss.str());
            return;
        }

        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (success) return;

        char _log[log_size];
        glGetProgramInfoLog(object, log_size, nullptr, _log);

        std::stringstream ss;
        ss << "Shader linking failed\n" << _log << "\n";
        SNOW_CORE_ERROR(ss.str());
    }
}
