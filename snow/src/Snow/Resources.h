//
// Created by Sweet Acid on 29.04.2021.
//

#pragma once

#include <pch.h>
#include <Snow/Graphics/Texture.h>
#include <Snow/Graphics/Shader.h>

namespace Snow {
    class Resources {
    public:
        static std::map<std::string, Shader> shaders;
        static std::map<std::string, Texture2D> textures;

        static Shader load_shader(
                const char *vertex_shader_path,
                const char *fragment_shader_path,
                const char *geometry_shader_path,
                std::string name
        );

        static Shader get_shader(std::string name);

        static Texture2D load_texture(const char *file, bool alpha, std::string name);

        static Texture2D get_texture(std::string name);

        static void cleanup();

    private:
        Resources() {}

        static Shader load_shader_from_file(
                const char *vertex_shader_path,
                const char *fragment_shader_path,
                const char *geometry_shader_path = nullptr
        );

        static Texture2D load_texture_from_file(const char *path, bool alpha);
    };
}
