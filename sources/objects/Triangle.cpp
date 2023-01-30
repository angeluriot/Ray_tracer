#include "objects/Triangle.hpp"

Triangle::Triangle(const Point& point_1, const Point& point_2, const Point& point_3)
{
	this->point_1 = point_1;
	this->point_2 = point_2;
	this->point_3 = point_3;
	texture = nullptr;
}

Hit Triangle::intersect(const Ray& ray) const
{
	// Compute plane's normal
	Vector p0p1 = point_2 - point_1;
	Vector p0p2 = point_3 - point_1;
	Vector normal = p0p1.cross(p0p2);
	normal.normalize();

	// Check if ray and plane are parallel.
	float NdotRayDirection = normal.dot(ray.direction);

	if (fabs(NdotRayDirection) < 0.0001f)
		return Hit::NO_HIT();

	// Compute d parameter
	float d = -normal.dot(point_1);

	// Compute t
	float t = -(normal.dot(ray.origin) + d) / NdotRayDirection;

	// Check if the triangle is in behind the ray
	if (t < 0.01f)
		return Hit::NO_HIT();

	// Compute the intersection point
	Vector intersection = ray.at(t);

	// Vector perpendicular to triangle's plane
	Vector C;

	// Edge 1
	Vector edge1 = point_2 - point_1;
	Vector vp1 = intersection - point_1;
	C = edge1.cross(vp1);

	if (normal.dot(C) < 0.f)
		return Hit::NO_HIT();

	// Edge 2
	Vector edge2 = point_3 - point_2;
	Vector vp2 = intersection - point_2;
	C = edge2.cross(vp2);

	if (normal.dot(C) < 0.f)
		return Hit::NO_HIT();

	// Edge 3
	Vector edge3 = point_1 - point_3;
	Vector vp3 = intersection - point_3;
	C = edge3.cross(vp3);

	if (normal.dot(C) < 0.f)
		return Hit::NO_HIT();

	return Hit(t, normal, material.color);
}
