#define VanCore_EXPORT	__declspec(dllexport)
#include <math.h>
#include "Vector3.h"

template<typename T>
inline T SQUARE(const T &x)
{
	return x*x;
}

template<typename T>
inline void Clamp(T &x,T &minParam,T &maxParam)
{
	x=(x<minParam?minParam:x<maxParam?x:maxParam);
}

namespace Van
{
	Vector3::Vector3(float x,float y,float z):x(x),y(y),z(z)
	{

	}

	Vector3::Vector3(const Vector3 &v):x(v.x),y(v.y),z(v.z)
	{

	}

	Vector3::Vector3():x(0.0f),y(0.0f),z(0.0f)
	{

	}

	Vector3& Vector3::operator=(const Vector3 &v)
	{
		x=v.x;
		y=v.y;
		z=v.z;
		return *this;
	}
	// vector add
	Vector3 Vector3::operator+(const Vector3 &v) const
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	// vector subtract
	Vector3 Vector3::operator-(const Vector3 &v) const
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	// scalar multiplication
	Vector3 Vector3::operator*(const float scalar) const
	{
		return Vector3(x * scalar, y * scalar, z * scalar);
	}

	// dot product
	float Vector3::operator*(const Vector3 &v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}

	// cross product
	Vector3 Vector3::operator^(const Vector3 &v) const
	{
		return Vector3(y * v.z - v.y * z, v.x * z - x * v.z, x * v.y - v.x * y);
	}

	float& Vector3:: operator[](int index)
	{
		return v[index];
	}


	float Vector3::Length()
	{
		float length = (float)sqrt(SQUARE(x) + SQUARE(y) + SQUARE(z));
		return (length != 0.0f) ? length : 1.0f;
	}

	Vector3 Vector3::Normalize()
	{
		*this = *this * (1.0f/Length());
		return *this;
	}
}
