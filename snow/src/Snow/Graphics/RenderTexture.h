//
// Created by Sweet Acid on 08.05.2021.
//

#pragma once

namespace Snow {

    /**
     * Intended to use with OpenGL.
     */
    class RenderTexture {
    public:
        unsigned int id;

        /**
         * in px
         */
        unsigned int width, height;

        /**
         * format of texture object
         */
        unsigned int internal_format;

        /**
         * format of loaded image
         */
        unsigned int image_format;

        unsigned int wrap_s;
        unsigned int wrap_t;

        /**
         * filtering mode if texture pixels < screen pixels
         */
        unsigned int filter_min;

        /**
         * filtering mode if texture pixels > screen pixels
         */
        unsigned int filter_max;

        RenderTexture();

        void generate(unsigned int _width = 512, unsigned int _height = 512, char *data = nullptr);

        /**
         * @brief binds the texture as the current active GL_TEXTURE_2D texture object
         */
        void bind() const;

        void update(char *data) const;
    };
}
