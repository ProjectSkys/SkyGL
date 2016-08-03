#pragma once

#include <skygl/common.h>

#include <string>
#include <GL/glew.h>

NS_SKY_GL_BEG

using Byte = GLbyte;
using UByte = GLubyte;
using Short = GLshort;
using UShort = GLushort;
using Int = GLint;
using UInt = GLuint;
using Fixed = GLfixed;
using Int64 = GLint64;
using UInt64 = GLuint64;

using Half = GLhalf;
using Float = GLfloat;
using Double = GLdouble;

using Bool = GLboolean;
using Char = GLchar;
using UChar = GLubyte;
using Size = GLsizei;
using Enum = GLenum;

using Void = GLvoid;

using VoidPtr = Void*;
using CharPtr = Char*;
using BytePtr = Byte*;
using UBytePtr = UByte*;

using SizeT = std::size_t;
using String = std::string;

using KVoidPtr = const Void*;
using KCharPtr = const Char*;

using KStringRef = const String&;

const Bool True = GL_TRUE;
const Bool False = GL_FALSE;

namespace internal {
    template <Enum E> struct E2T;
    template <class T> struct T2E;
#define ExT(e, t) \
    template <> struct E2T<e> { using Type = t; }; \
    template <> struct T2E<t> { static const Enum value = e; };
    ExT(GL_BYTE, Byte)
    ExT(GL_UNSIGNED_BYTE, UByte)
    ExT(GL_SHORT, Short)
    ExT(GL_UNSIGNED_SHORT, UShort)
    ExT(GL_INT, Int)
    ExT(GL_UNSIGNED_INT, UInt)
    // ExT(GL_FIXED, Fixed)
    // ExT(GL_HALF_FLOAT, Half)
    ExT(GL_FLOAT, Float)
    ExT(GL_DOUBLE, Double)
#undef ExT
}

template <Enum E>
using EnumToType = typename internal::E2T<E>::Type;

template <class T>
Enum TypeToEnum = internal::T2E<T>::value;

template <Int N, class T>
SizeT SizeOf = N * sizeof(T);

NS_SKY_GL_END
