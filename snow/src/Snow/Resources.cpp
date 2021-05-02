//
// Created by Sweet Acid on 29.04.2021.
//

#include "Resources.h"
#include "stb_image.h"
#include <glad/glad.h>

namespace Snow {
    std::map<std::string, Texture2D>    Resources::textures;
    std::map<std::string, Shader>       Resources::shaders;

    Shader Resources::load_shader(
            const char *vertex_shader_path,
            const char *fragment_shader_path,
            const char *geometry_shader_path,
            std::string name
    ) {
        if (shaders[name].id > 0) return shaders[name];
        shaders[name] = load_shader_from_file(vertex_shader_path, fragment_shader_path, geometry_shader_path);
        return shaders[name];
    }

    Shader Resources::get_shader(std::string name) {
        return shaders[name];
    }

    Texture2D Resources::load_texture(const char *file, bool alpha, std::string name) {
        if (textures[name].id > 0) return textures[name];
        textures[name] = load_texture_from_file(file, alpha);
        return textures[name];
    }

    Texture2D Resources::get_texture(std::string name) {
        return textures[name];
    }

    void Resources::cleanup() {
        for (auto iter : shaders)
            glDeleteProgram(iter.second.id);
        for (auto iter : textures)
            glDeleteTextures(1, &iter.second.id);
    }

    Shader Resources::load_shader_from_file(
            const char *vertex_shader_path,
            const char *fragment_shader_path,
            const char *geometry_shader_path
    ) {
        auto load = [](const char *path, std::string &code, const char *type) {
            try {
                std::stringstream ss;

                std::ifstream file(path);
                ss << file.rdbuf();
                file.close();

                code = ss.str();
            }
            catch (std::exception e) {
                std::stringstream ss;
                ss << type << " shader loading failed\n"
                   << "Path: " << path << "\n";

                SNOW_CORE_ERROR(ss.str());
            }
        };

        auto validate = [](const char *path, std::string &code, const char *type) {
            if (code.length() == 0) {
                std::stringstream ss;
                ss << type << " shader does not exist or is empty\n"
                   << "Path: " << path << "\n";

                SNOW_CORE_ERROR(ss.str());
            }
        };

        std::string vertex_code;
        std::string fragment_code;
        std::string geometry_code;

        load(vertex_shader_path, vertex_code, "vertex");
        validate(vertex_shader_path, vertex_code, "vertex");

        load(fragment_shader_path, fragment_code, "fragment");
        validate(fragment_shader_path, fragment_code, "fragment");

        if (geometry_shader_path != nullptr) {
            load(geometry_shader_path, geometry_code, "geometry");
            validate(geometry_shader_path, geometry_code, "geometry");
        }

        const char *vertex_code_c_str = vertex_code.c_str();
        const char *fragment_code_c_str = fragment_code.c_str();
        const char *geometry_code_c_str = geometry_shader_path == nullptr ? nullptr : geometry_code.c_str();

        Shader shader;
        shader.compile(vertex_code_c_str, fragment_code_c_str, geometry_code_c_str);
        return shader;
    }

    Texture2D Resources::load_texture_from_file(const char *path, bool alpha) {
        Texture2D texture;
        if (alpha) {
            texture.internal_format = GL_RGBA;
            texture.image_format = GL_RGBA;
        }

        int width, height, nr_channels;
        unsigned char *data = stbi_load(path, &width, &height, &nr_channels, 0);
        texture.generate(width, height, data);
        stbi_image_free(data);

        return texture;
    }
}
