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

	Light(Point pos,Color c) : position(pos), color(c) {}

	Point position;
	Color color;
};

class Ray
{
public:

	Point O;
	Vector D;

	Ray(const Point& from, const Vector& dir): O(from), D(dir) {}

	Point at(double t) const
	{
		return O + t * D;
	}

};

class Hit
{
public:

	double t;
	Vector N;
	bool no_hit;

	Hit(const double t, const Vector& normal, bool nohit = false): t(t), N(normal), no_hit(nohit) {}

	static const Hit NO_HIT()
	{
		static Hit no_hit(std::numeric_limits<double>::quiet_NaN(), Vector(std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN()), true);
		return no_hit;
	}
};

#endif
