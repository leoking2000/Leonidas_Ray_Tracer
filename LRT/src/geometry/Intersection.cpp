#include "Intersection.h"


namespace LRT
{
    Intersection::Intersection(f32 t, u32 index)
        :
        t(t),
        shapeID(index)
    {
    }

    bool Intersection::operator==(const Intersection& other) const
    {
        return this->t == other.t && this->shapeID == other.shapeID;
    }

    bool Intersection::operator!=(const Intersection& other) const
    {
        return !(*this == other);
    }
}