//
// Created by Sweet Acid on 29.04.2021.
//

#pragma once

namespace Snow {

    /**
     * Intended to use with OpenGL.
     */
    class Texture2D {
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

        Texture2D();

        void generate(unsigned int _width, unsigned int _height, unsigned char *data);

        /**
         * @brief binds the texture as the current active GL_TEXTURE_2D texture object
         */
        void bind() const;
    };
}
