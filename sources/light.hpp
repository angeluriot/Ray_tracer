/**
* Framework for a raytracer
* File: light.h
*
* Created for the Computer Science course "Introduction Computer Graphics"
* taught at the University of Groningen by Tobias Isenberg.
*
* Authors:
* Maarten Everts
* Jasper van de Gronde
* adjustment of Hit class by Olivier Wavrin
*
* This framework is inspired by and uses code of the raytracer framework of
* Bert Freudenberg that can be found at
* http://isgwww.cs.uni-magdeburg.de/graphik/lehre/cg2/projekt/rtprojekt.html
*/

#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <iostream>
#include <limits>
#include "triple.hpp"

class Light
{
public:

	Light(Point pos, Color c) : position(pos), color(c) {}

	Point position;
	Color color;
};

class Ray
{
public:

	Point origin;
	Vector direction;

	Ray(const Point& origin, const Vector& direction): origin(origin), direction(direction) {}

	Point at(double t) const
	{
		return origin + t * direction;
	}

};

class Hit
{
public:

	double distance;
	Vector normal;
	bool no_hit;

	Hit(const double distance, const Vector& normal, bool no_hit = false): distance(distance), normal(normal), no_hit(no_hit) {}

	static const Hit NO_HIT()
	{
		static Hit no_hit(std::numeric_limits<double>::quiet_NaN(), Vector(std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN()), true);
		return no_hit;
	}
};

#endif
