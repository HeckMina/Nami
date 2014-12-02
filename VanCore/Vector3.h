#pragma 
#ifdef VanCore_EXPORT
#elif
#define VanCore_EXPORT __declspec(dllimport)
#endif

namespace Van
{
	class	VanCore_EXPORT	Vector3
	{
	public:
		union
		{
			struct
			{
				float x,y,z;
			};
			float v[3];
		};
	public:
		Vector3(float x,float y,float z);
		Vector3(const Vector3 &v);
		Vector3();

	public:
		Vector3&operator=(const Vector3 &v);
		Vector3 operator+(const Vector3 &v) const;
		Vector3 operator-(const Vector3 &v) const;
		Vector3 operator*(const float scalar)const;
		float	 operator*(const Vector3 &v) const;
		Vector3 operator^(const Vector3 &v) const;
		float&	 operator[](int index);
		float	 Length();
		Vector3 Normalize();
	};
}
