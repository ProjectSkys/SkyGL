#pragma once

#include <skygl/basic/common.h>
#include <skygl/basic/types.h>
#include <skygl/basic/error.h>

#include <boost/noncopyable.hpp>

#include <SOIL/SOIL.h>

NS_SKY_GL_BEG

class Image: private boost::noncopyable {
public:
    UBytePtr data;
    Int width, height;
    Enum pixelFormat;
    Enum internalFormat;
public:
    Image(KStringRef path, bool alpha = false, Bool gamma = false)
        : pixelFormat(alpha ? GL_RGBA : GL_RGB)
        , internalFormat(alpha ?
            (gamma ? GL_SRGB_ALPHA : GL_RGBA) :
            (gamma ? GL_SRGB : GL_RGB)
        )
    {
        data = SOIL_load_image(path.c_str(), &width, &height, 0, alpha ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
        if (data == nullptr) {
            throw GLException("Image::Image(path)", "Can not load " + path);
        }
    }
    ~Image() {
        if (data) SOIL_free_image_data(data);
    }
    Image(Image&& img) {
        data = img.data;
        width = img.width;
        height = img.height;
        img.data = 0;
    }
    Image& operator = (Image&& img) {
        if (this == &img) return *this;
        data = img.data;
        width = img.width;
        height = img.height;
        img.data = 0;
        return *this;
    }
};

NS_SKY_GL_END
