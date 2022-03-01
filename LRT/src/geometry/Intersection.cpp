#include "Intersection.h"
#include "Primitive.h"

namespace LRT
{
    Intersection::Intersection(f32 distance, u64 pPrimitive)
        :
        m_distance(distance),
        m_pPrimitive(pPrimitive)
    {

    }

    bool Intersection::operator==(const Intersection& other) const
    {
        return this->m_distance == other.m_distance && this->m_pPrimitive == other.m_pPrimitive;
    }

    bool Intersection::operator!=(const Intersection& other) const
    {
        return !(*this == other);
    }
}