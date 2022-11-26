/**
* Framework for a raytracer
* File: sphere.h
*
* Created for the Computer Science course "Introduction Computer Graphics"
* taught at the University of Groningen by Tobias Isenberg.
*
* Authors:
* Maarten Everts
* Jasper van de Gronde
*
* This framework is inspired by and uses code of the raytracer framework of
* Bert Freudenberg that can be found at
* http://isgwww.cs.uni-magdeburg.de/graphik/lehre/cg2/projekt/rtprojekt.html
*/

#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "object.hpp"

class Sphere : public Object
{
public:
	Sphere(Point position, double radius): position(position), radius(radius) {}

	virtual Hit intersect(const Ray& ray);

	const Point position;
	const double radius;
};

#endif
