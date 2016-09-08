#pragma once

#include "skygl/basic/common.h"
#include "skygl/basic/types.h"
#include "skygl/basic/error.h"
#include "skygl/gl/gl.h"
#include "skygl/load/image.h"

#include <memory>

#include <boost/noncopyable.hpp>

NS_SKY_GL_BEG

template <Enum TextureType = GL_TEXTURE_2D>
class Texture: private boost::noncopyable {
public:
    using Ptr = std::shared_ptr<Texture<TextureType>>;
private:
    UInt _id;
    UInt _active;
public:
    Texture(UInt active = 0): _id(0), _active(active) {
        glGenTextures(1, &_id);
    }
    ~Texture() {
        if (_id) glDeleteTextures(1, &_id);
    }
    Texture(Texture&& tex) {
        _id = tex._id;
        _active = tex._active;
        tex._id = 0;
    }
    Texture& operator = (Texture&& tex) {
        if (this == &tex) return *this;
        _id = tex._id;
        _active = tex._active;
        tex._id = 0;
        return *this;
    }
    UInt getId() const {
        return _id;
    }
    UInt getActive(UInt active) const {
        return _active;
    }
    void setActive(UInt active) {
        _active = active;
    }
    const Texture& bind() const {
        glActiveTexture(GL_TEXTURE0 + _active);
        glBindTexture(TextureType, _id);
        return *this;
    }
    const Texture& unbind() const {
        glActiveTexture(GL_TEXTURE0 + _active);
        glBindTexture(TextureType, 0);
        return *this;
    }
    Texture& active(UInt active) {
        setActive(active);
        bind();
        return *this;
    }
    const Texture& param(Enum pname, Int value) const {
        glTexParameteri(TextureType, pname, value);
        return *this;
    }
    const Texture& param(Enum pname, Int* value) const {
        glTexParameteriv(TextureType, pname, value);
        return *this;
    }
    const Texture& param(Enum pname, UInt value) const {
        param(pname, static_cast<Int>(value));
        return *this;
    }
    const Texture& param(Enum pname, Float value) const {
        glTexParameterf(TextureType, pname, value);
        return *this;
    }
    const Texture& param(Enum pname, Float* value) const {
        glTexParameterfv(TextureType, pname, value);
        return *this;
    }
    template <typename T>
    const Texture& param(Enum pname, const std::vector<T>& value) const {
        param(TextureType, pname, &value[0]);
        return *this;
    }
    const Texture& load(const Image& img, Enum target = TextureType) const {
        glTexImage2D(target, 0, img.internalFormat, img.width, img.height, 0, img.pixelFormat, GL_UNSIGNED_BYTE, img.data);
        return *this;
    }
    const Texture& multisample(Size width, Size height, Enum format, UInt samples = 1, Enum target = TextureType) const {
        glTexImage2DMultisample(target, samples, format, width, height, True);
        return *this;
    }
    const Texture& empty(Size width, Size height, Enum format, Enum type = GL_UNSIGNED_BYTE, Enum target = TextureType) const {
        glTexImage2D(target, 0, format, width, height, 0, format, type, nullptr);
        return *this;
    }
    const Texture& genMipmap() const {
        glGenerateMipmap(TextureType);
        return *this;
    }
};

#define USING_TEXTURE(postfix, type) \
    using Texture##postfix = Texture<GL_TEXTURE_##type>; \
    using Texture##postfix##Ptr = Texture##postfix::Ptr;
USING_TEXTURE(2D, 2D)
USING_TEXTURE(3D, 3D)
USING_TEXTURE(CubeMap, CUBE_MAP)
USING_TEXTURE(2DMultisample, 2D_MULTISAMPLE)
#undef USING_TEXTURE

NS_SKY_GL_END
