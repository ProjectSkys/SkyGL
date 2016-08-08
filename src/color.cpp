#include "skygl/calc/color.h"

NS_SKY_GL_BEG

namespace Color {
#define DEFINE_COLOR(name, value...) \
    const ColorRGB name(value); \
    const ColorRGBA name##A(value, 1);
    DEFINE_COLOR(Black, 0, 0, 0)
    DEFINE_COLOR(Blue,  0, 0, 1)
    DEFINE_COLOR(Green, 0, 1, 0)
    DEFINE_COLOR(Red,   1, 0, 0)
    DEFINE_COLOR(White, 1, 1, 1)
#undef DEFINE_COLOR
}

NS_SKY_GL_END
