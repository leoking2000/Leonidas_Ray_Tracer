#pragma once
#include <cinttypes>

#define LRTAPI __declspec(dllexport)

namespace LRT
{
    bool LRTAPI Equal(float a, float b, float epsilon = 0.00001f);
}

#include "Vector4.h"
#include "Canvas.h"