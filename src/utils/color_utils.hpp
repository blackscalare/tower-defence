#pragma once
#include <raylib.h>

static inline Color ChangeAlpha(Color color, int a) {
    color.a = a;
    return color;
}
