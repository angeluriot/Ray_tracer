#ifndef RAY_HPP
#define RAY_HPP

#include "utils/Triple.hpp"

class Ray
{
public:

	Point origin;
	Vector direction;

	Ray(const Point& origin, const Vector& direction): origin(origin), direction(direction) {}

	Point at(float t) const
	{
		return origin + t * direction;
	}

};

#endif
