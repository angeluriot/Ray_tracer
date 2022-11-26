/**
* Framework for a raytracer
* File: sphere.cpp
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

#include <iostream>
#include <math.h>
#include "sphere.hpp"

/************************** Sphere **********************************/

Hit Sphere::intersect(const Ray& ray)
{
	// The vector from the ray origin to the sphere center
	Vector OC = position - ray.origin;
	// The closest distance from the ray origin to the sphere
	double t = OC.dot(ray.direction);

	// The closest point on the ray to the sphere center
	Vector closest = ray.at(t);

	// If the closest point is outside the sphere, there is no intersection
	if ((closest - position).length() > radius)
		return Hit::NO_HIT();

	// The distance from the closest point to the sphere center
	double y = (position - ray.at(t)).length();
	// The distance from the closest point to the intersection points
	double x = sqrt(pow(radius, 2) - pow(y, 2));
	// The distance from the ray origin to the first intersection point
	double distance = t - x;

	// The first intersection point
	Point intersection = ray.at(distance);
	// The normal at the first intersection point
	Vector normal = (intersection - position).normalized();

	return Hit(distance, normal);
}
