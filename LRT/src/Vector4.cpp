#include "utilit.h"
#include "Vector4.h"

LRT::vec4::vec4()
    :
    vec3(0.0f, 0.0f, 0.0f), w(1.0f)
{
}

LRT::vec4::vec4(float x, float y, float z, float w)
    :
    vec3(x, y, z), w(w)
{
}

LRT::vec4::vec4(const vec3& a, float w)
    :
    vec3(a.x, a.y, a.z), w(w)
{
}

LRT::vec4 LRT::vec4::zero()
{
    return vec4(0.0f, 0.0f, 0.0f, 0.0f);
}

LRT::vec4 LRT::vec4::up()
{
    return vec4(0.0f, 1.0f, 0.0f, 0.0f);
}

LRT::vec4 LRT::vec4::down()
{
    return vec4(0.0f, -1.0f, 0.0f, 0.0f);
}

LRT::vec4 LRT::vec4::right()
{
    return vec4(1.0f, 0.0f, 0.0f, 0.0f);
}

LRT::vec4 LRT::vec4::left()
{
    return vec4(-1.0f, 0.0f, 0.0f, 0.0f);
}

LRT::vec4 LRT::vec4::forward()
{
    return vec4(0.0f, 0.0f, 1.0f, 0.0f);
}

LRT::vec4 LRT::vec4::back()
{
    return vec4(0.0f, 0.0f, -1.0f, 0.0f);
}

bool LRT::vec4::operator==(const vec4& a) const
{
    return LRT::Equal(a.x, x) && LRT::Equal(a.y, y) && LRT::Equal(a.z, z) && LRT::Equal(a.w, w);
}

LRT::vec4& LRT::vec4::operator+=(const vec4& a)
{
    x += a.x;
    y += a.y;
    z += a.z;
    w += a.w;

    return *this;
}

LRT::vec4 LRT::vec4::operator+(const vec4& a) const
{
    vec4 r(x + a.x, y + a.y, z + a.z, w + a.w);
    return r;
}

LRT::vec4& LRT::vec4::operator-=(const vec4& a)
{
    x -= a.x;
    y -= a.y;
    z -= a.z;
    w -= a.w;

    return *this;
}

LRT::vec4 LRT::vec4::operator-(const vec4& a) const
{
    vec4 r(x - a.x, y - a.y, z - a.z, w - a.w);
    return r;
}

LRT::vec4 LRT::vec4::operator-() const
{
    return vec4(-x, -y, -z, -w);
}

LRT::vec4& LRT::vec4::operator*=(float num)
{
    x *= num;
    y *= num;
    z *= num;
    w *= num;

    return *this;
}

LRT::vec4 LRT::vec4::operator*(float num) const
{
    vec4 r(this->x * num, this->y * num, this->z * num, this->w * num);
    return r;
}

LRT::vec4& LRT::vec4::operator/=(float num)
{
    x /= num;
    y /= num;
    z /= num;
    w /= num;

    return *this;
}

LRT::vec4 LRT::vec4::operator/(float num) const
{
    vec4 r(this->x / num, this->y / num, this->z / num, this->w / num);

    return r;
}

float& LRT::vec4::operator[](int i)
{
    if (i == 0)
    {
        return x;
    }
    else if (i == 1)
    {
        return y;
    }
    else if (i == 2)
    {
        return z;
    }
    else if (i == 3)
    {
        return w;
    }
}

LRT::vec4 LRT::operator*(float num, const vec4& a)
{
    vec4 r(a.x * num, a.y * num, a.z * num, a.w * num);
    return r;
}
