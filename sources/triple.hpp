/**
* Framework for a raytracer
* File: triple.h
*
* Created for the Computer Science course "Introduction Computer Graphics"
* taught at the University of Groningen by Tobias Isenberg.
*
* Author: Maarten Everts
*
* This framework is inspired by and uses code of the raytracer framework of
* Bert Freudenberg that can be found at
* http://isgwww.cs.uni-magdeburg.de/graphik/lehre/cg2/projekt/rtprojekt.html
*/

#ifndef TRIPLE_HPP
#define TRIPLE_HPP

#include <math.h>
#include <iostream>

class Triple
{
public:

	explicit Triple(double X = 0, double Y = 0, double Z = 0): x(X), y(Y), z(Z) {}

	Triple operator+(const Triple& t) const
	{
		return Triple(x + t.x, y + t.y, z + t.z);
	}

	Triple operator+(double f) const
	{
		return Triple(x + f, y + f, z + f);
	}

	friend Triple operator+(double f, const Triple& t)
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

	Triple operator-(double f) const
	{
		return Triple(x - f, y - f, z - f);
	}

	friend Triple operator-(double f, const Triple& t)
	{
		return Triple(f - t.x, f - t.y, f - t.z);
	}

	Triple operator*(const Triple& t) const
	{
		return Triple(x * t.x,y * t.y, z * t.z);
	}

	Triple operator*(double f) const
	{
		return Triple(x * f, y * f, z * f);
	}

	friend Triple operator*(double f, const Triple& t)
	{
		return Triple(f * t.x, f * t.y, f * t.z);
	}

	Triple operator/(double f) const
	{
		double invf = 1. / f;
		return Triple(x * invf, y * invf, z * invf);
	}

	Triple& operator+=(const Triple& t)
	{
		x += t.x;
		y += t.y;
		z += t.z;
		return *this;
	}

	Triple& operator+=(double f)
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

	Triple& operator-=(double f)
	{
		x -= f;
		y -= f;
		z -= f;
		return *this;
	}

	Triple& operator*=(const double f)
	{
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}

	Triple& operator/=(const double f)
	{
		double invf = 1. / f;
		x *= invf;
		y *= invf;
		z *= invf;
		return *this;
	}

	double dot(const Triple& t) const
	{
		return x * t.x + y * t.y + z * t.z;
	}

	Triple cross(const Triple& t) const
	{
		return Triple(y * t.z - z * t.y, z * t.x - x * t.z, x * t.y - y * t.x);
	}

	double length() const
	{
		return sqrt(length_2());
	}

	double length_2() const
	{
		return x * x + y * y + z * z;
	}

	Triple normalized() const
	{
		return (*this) / length();
	}

	void normalize()
	{
		double l = length();
		double invl = 1. / l;
		x *= invl;
		y *= invl;
		z *= invl;
	}

	friend std::istream& operator>>(std::istream& s, Triple& v);
	friend std::ostream& operator<<(std::ostream& s, const Triple& v);

	// Functions for when used as a Color:
	void set(double f)
	{
		r = g = b = f;
	}

	void set(double f, double maxValue)
	{
		set(f / maxValue);
	}

	void set(double red, double green, double blue)
	{
		r = red;
		g = green;
		b = blue;
	}

	void set(double r, double g, double b, double maxValue)
	{
		set(r / maxValue, g / maxValue, b / maxValue);
	}

	void clamp(double maxValue = 1.)
	{
		if (r > maxValue) r = maxValue;
		if (g > maxValue) g = maxValue;
		if (b > maxValue) b = maxValue;
	}

	union
	{
		double data[3];

		struct
		{
			double x;
			double y;
			double z;
		};

		struct
		{
			double r;
			double g;
			double b;
		};
	};
};

typedef Triple Color;
typedef Triple Point;
typedef Triple Vector;

#endif
