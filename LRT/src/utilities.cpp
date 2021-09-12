#include "utilities.h"
#include <cmath>

namespace LRT
{
    bool Equal(float a, float b, float epsilon)
    {
        return std::abs(a - b) < epsilon;
    }
}

