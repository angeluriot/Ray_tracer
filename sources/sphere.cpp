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
	/****************************************************
	* RT1.1: INTERSECTION CALCULATION
	*
	* Given: ray, position, r
	* Sought: intersects? if true: *t
	*
	* Insert calculation of ray/sphere intersection here.
	*
	* You have the sphere's center (C) and radius (r) as well as
	* the ray's origin (ray.O) and direction (ray.D).
	*
	* If the ray does not intersect the sphere, return Hit::NO_HIT().
	* Otherwise, return an instance of Hit() with the distance of the
	* intersection point from the ray origin as t and the normal ad N (see example).
	****************************************************/

	// place holder for actual intersection calculation

	Vector OC = (position - ray.O).normalized();

	if (OC.dot(ray.D) < 0.999)
		return Hit::NO_HIT();

	double t = 1000;

	/****************************************************
	* RT1.2: NORMAL CALCULATION
	*
	* Given: t, C, r
	* Sought: N
	*
	* Insert calculation of the sphere's normal at the intersection point.
	****************************************************/

	Vector N /* = ... */;

	return Hit(t, N);
}
