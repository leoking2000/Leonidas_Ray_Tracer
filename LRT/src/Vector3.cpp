#include "LRT.h"
#include <cmath>

LRT::vec3::vec3()
    :
    x(0.0f), y(0.0f), z(0.0f)
{
}

LRT::vec3::vec3(float x, float y, float z)
    :
    x(x), y(y), z(z)
{
}

LRT::vec3 LRT::vec3::zero()
{
    return vec3(0.0f, 0.0f, 0.0f);
}

LRT::vec3 LRT::vec3::up()
{
    return vec3(0.0f, 1.0f, 0.0f);
}

LRT::vec3 LRT::vec3::down()
{
    return vec3(0.0f, -1.0f, 0.0f);
}

LRT::vec3 LRT::vec3::right()
{
    return vec3(1.0f, 0.0f, 0.0f);
}

LRT::vec3 LRT::vec3::left()
{
    return vec3(-1.0f, 0.0f, 0.0f);
}

LRT::vec3 LRT::vec3::forward()
{
    return vec3(0.0f, 0.0f, 1.0f);
}

LRT::vec3 LRT::vec3::back()
{
    return vec3(0.0f, 0.0f, -1.0f);
}

float LRT::vec3::distance(const vec3& a, const vec3& b)
{
    return (a - b).length();
}

float LRT::vec3::dot(const vec3& a, const vec3& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

LRT::vec3 LRT::vec3::cross(const vec3& a, const vec3& b)
{
    return vec3(a.y * b.z - a.z * b.y , a.z * b.x - a.x * b.z , a.x * b.y - a.y * b.x);
}

LRT::vec3 LRT::vec3::reflect(const vec3& a, const vec3& normal)
{
    return a - 2.0f * normal * a.dot(normal);
}

float LRT::vec3::sqrLength() const
{
    return this->dot(*this);
}

float LRT::vec3::length() const
{
    return std::sqrt(this->dot(*this));
}

LRT::vec3 LRT::vec3::getNormalized() const
{
    return *this / this->length();
}

float LRT::vec3::distance(const vec3& a) const
{
    return (*this - a).length();
}

float LRT::vec3::dot(const vec3& a) const
{
    return dot(*this, a);
}

LRT::vec3 LRT::vec3::cross(const vec3& a)
{
    return cross(*this, a);
}

void LRT::vec3::normalize()
{
    *this = *this / this->length();
}

bool LRT::vec3::operator==(const vec3& a) const
{
    return LRT::Equal(a.x, x) && LRT::Equal(a.y, y) && LRT::Equal(a.z, z);
}

bool LRT::vec3::operator!=(const vec3& a) const
{
    return !(*this == a);
}

LRT::vec3& LRT::vec3::operator+=(const vec3& a)
{
    x += a.x;
    y += a.y;
    z += a.z;

    return *this;
}

LRT::vec3 LRT::vec3::operator+(const vec3& a) const
{
    vec3 r(x + a.x, y + a.y, z + a.z);
    return r;
}

LRT::vec3& LRT::vec3::operator-=(const vec3& a)
{
    x -= a.x;
    y -= a.y;
    z -= a.z;

    return *this;
}

LRT::vec3 LRT::vec3::operator-(const vec3& a) const
{
    vec3 r(x - a.x, y - a.y, z - a.z);
    return r;
}

LRT::vec3 LRT::vec3::operator-() const
{
    return vec3(-x, -y, -z);
}

LRT::vec3& LRT::vec3::operator*=(float num)
{
    x *= num;
    y *= num;
    z *= num;

    return *this;
}

LRT::vec3 LRT::vec3::operator*(float num) const
{
    vec3 r(this->x * num, this->y * num, this->z * num);
    return r;
}

LRT::vec3& LRT::vec3::operator/=(float num)
{
    x /= num;
    y /= num;
    z /= num;

    return *this;
}

LRT::vec3 LRT::vec3::operator/(float num) const
{
    vec3 r(this->x / num, this->y / num, this->z / num);

    return r;
}

float& LRT::vec3::operator[](int i)
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
}

LRT::vec3 LRT::operator*(float num, const vec3& a)
{
    vec3 r(a.x * num, a.y * num, a.z * num);
    return r;
}

LRT::Color LRT::operator*(const Color& c1, const Color& c2)
{
    return Color(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b);
}

