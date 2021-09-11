#include "utilities.h"
#include <cmath>
#include <limits>
#include <algorithm>

namespace LRT
{
    bool Equal(float a, float b, float epsilon)
    {
        constexpr float MIN_NORMAL = std::numeric_limits<float>::min();
        constexpr float MAX_VALUE = std::numeric_limits<float>::max();

        float absA = std::abs(a);
        float absB = std::abs(b);
        float diff = std::abs(a - b);

        if (a == b) // shortcut, handles infinities
        { 
            return true;
        }
        else if (a == 0 || b == 0 || (absA + absB < MIN_NORMAL)) {
            // a or b is zero or both are extremely close to it
            // relative error is less meaningful here
            return diff < (epsilon * MIN_NORMAL);
        }
        else { // use relative error
            return diff / std::min((absA + absB), MAX_VALUE) < epsilon;
        }
    }
}

