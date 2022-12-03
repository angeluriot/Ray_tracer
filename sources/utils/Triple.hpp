#ifndef TRIPLE_HPP
#define TRIPLE_HPP

#include <iostream>

class Triple
{
public:

	explicit Triple(float x = 0.f, float y = 0.f, float z = 0.f): x(x), y(y), z(z) {}

	Triple operator+(const Triple& t) const
	{
		return Triple(x + t.x, y + t.y, z + t.z);
	}

	Triple operator+(float f) const
	{
		return Triple(x + f, y + f, z + f);
	}

	friend Triple operator+(float f, const Triple& t)
	{
		return Triple(f + t.x, f + t.y, f + t.z);
	}

	Triple operator-() const
	{
		return Triple(-x, -y, -z);
	}

	Triple operator-(const Triple& t) const
	{
		return Triple(x - t.x, y - t.y, z - t.z);
	}

	Triple operator-(float f) const
	{
		return Triple(x - f, y - f, z - f);
	}

	friend Triple operator-(float f, const Triple& t)
	{
		return Triple(f - t.x, f - t.y, f - t.z);
	}

	Triple operator*(const Triple& t) const
	{
		return Triple(x * t.x,y * t.y, z * t.z);
	}

	Triple operator*(float f) const
	{
		return Triple(x * f, y * f, z * f);
	}

	friend Triple operator*(float f, const Triple& t)
	{
		return Triple(f * t.x, f * t.y, f * t.z);
	}

	Triple operator/(float f) const
	{
		float invf = 1.f / f;
		return Triple(x * invf, y * invf, z * invf);
	}

	Triple& operator+=(const Triple& t)
	{
		x += t.x;
		y += t.y;
		z += t.z;
		return *this;
	}

	Triple& operator+=(float f)
	{
		x += f;
		y += f;
		z += f;
		return *this;
	}

	Triple& operator-=(const Triple& t)
	{
		x -= t.x;
		y -= t.y;
		z -= t.z;
		return *this;
	}

	Triple& operator-=(float f)
	{
		x -= f;
		y -= f;
		z -= f;
		return *this;
	}

	Triple& operator*=(const float f)
	{
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}

	Triple& operator/=(const float f)
	{
		float invf = 1.f / f;
		x *= invf;
		y *= invf;
		z *= invf;
		return *this;
	}

	float dot(const Triple& t) const
	{
		return x * t.x + y * t.y + z * t.z;
	}

	Triple cross(const Triple& t) const
	{
		return Triple(y * t.z - z * t.y, z * t.x - x * t.z, x * t.y - y * t.x);
	}

	float length() const
	{
		return sqrt(length_2());
	}

	float length_2() const
	{
		return x * x + y * y + z * z;
	}

	Triple normalized() const
	{
		return (*this) / length();
	}

	void normalize()
	{
		float l = length();
		float invl = 1.f / l;
		x *= invl;
		y *= invl;
		z *= invl;
	}

	friend std::istream& operator>>(std::istream& s, Triple& v);
	friend std::ostream& operator<<(std::ostream& s, const Triple& v);

	// Functions for when used as a Color:
	void set(float f)
	{
		r = g = b = f;
	}

	void set(float f, float max_value)
	{
		set(f / max_value);
	}

	void set(float red, float green, float blue)
	{
		r = red;
		g = green;
		b = blue;
	}

	void set(float r, float g, float b, float maxValue)
	{
		set(r / maxValue, g / maxValue, b / maxValue);
	}

	void clamp(float max_value = 1.f)
	{
		if (r > max_value) r = max_value;
		if (g > max_value) g = max_value;
		if (b > max_value) b = max_value;
	}

	union
	{
		float data[3];

		struct
		{
			float x;
			float y;
			float z;
		};

		struct
		{
			float r;
			float g;
			float b;
		};
	};
};

typedef Triple Color;
typedef Triple Point;
typedef Triple Vector;

#endif
