//
// Created by Sweet Acid on 08.05.2021.
//

#include "RenderTexture.h"
#include <glad/glad.h>

namespace Snow {
    RenderTexture::RenderTexture()
            :width(0), height(0),
             internal_format(GL_RGBA),
             image_format(GL_RGBA),
             wrap_s(GL_REPEAT),
             wrap_t(GL_REPEAT),
             filter_min(GL_LINEAR),
             filter_max(GL_LINEAR) {
        glGenTextures(1, &this->id);
    }

    void RenderTexture::generate(unsigned int _width, unsigned int _height, char *data) {
        this->width = _width;
        this->height = _height;

        //  create texture
        glBindTexture(GL_TEXTURE_2D, this->id);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0,
                     GL_RGBA, GL_UNSIGNED_BYTE, data);

        //  set texture wrap and filter modes
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrap_s);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrap_t);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filter_min);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filter_max);

        // unbind texture
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void RenderTexture::bind() const {
        glBindTexture(GL_TEXTURE_2D, this->id);
    }

    void RenderTexture::update(char *data) const {
        glBindTexture(GL_TEXTURE_2D, this->id);

        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, this->width, this->height,
                        GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
}
