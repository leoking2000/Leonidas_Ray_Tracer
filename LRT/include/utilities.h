#pragma once
#include <cinttypes>

#define LRTAPI __declspec(dllexport)

namespace LRT
{
    constexpr float PI = 3.14159265f;

    bool LRTAPI Equal(float a, float b, float epsilon = 0.00001f);

    template<typename T>
    inline constexpr const T& clamp(const T& v, const T& lo, const T& hi)
    {
        return v < lo ? lo : hi < v ? hi : v;
    }
}