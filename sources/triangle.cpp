#include <iostream>
#include <math.h>
#include "triangle.hpp"

/************************** Sphere **********************************/

Hit Triangle::intersect(const Ray& ray)
{
	// Compute plane's normal
	Vector p0p1 = point_2 - point_1;
	Vector p0p2 = point_3 - point_1;
	// No need to normalize
	Vector normal = p0p1.cross(p0p2); // N
	float area2 = normal.length();

	// Step 1: finding P

	// Check if ray and plane are parallel.
	float NdotRayDirection = normal.dot(ray.direction);

	if (fabs(NdotRayDirection) < 10e-8) // Almost 0
		return Hit::NO_HIT(); // They are parallel so they don't intersect !

	// Compute d parameter
	float d = -normal.dot(point_1);

	// Compute t
	double t = -(normal.dot(ray.origin) + d) / NdotRayDirection;

	// Check if the triangle is in behind the ray
	if (t < 0.)
		return Hit::NO_HIT(); // The triangle is behind

	// Compute the intersection point using
	Vector intersection = ray.at(t);

	// Step 2: inside-outside test
	Vector C; // Vector perpendicular to triangle's plane

	// Edge 1
	Vector edge1 = point_2 - point_1;
	Vector vp1 = intersection - point_1;
	C = edge1.cross(vp1);

	if (normal.dot(C) < 0.)
		return Hit::NO_HIT(); // P is on the right side

	// Edge 2
	Vector edge2 = point_3 - point_2;
	Vector vp2 = intersection - point_2;
	C = edge2.cross(vp2);

	if (normal.dot(C) < 0.)
		return Hit::NO_HIT(); // P is on the right side

	// Edge 3
	Vector edge3 = point_1 - point_3;
	Vector vp3 = intersection - point_3;
	C = edge3.cross(vp3);

	if (normal.dot(C) < 0.)
		return Hit::NO_HIT(); // P is on the right side;

	return Hit(t, normal);
}
