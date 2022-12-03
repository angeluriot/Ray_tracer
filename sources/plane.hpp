#ifndef PLANE_HPP
#define PLANE_HPP

#include "object.hpp"

class Plane : public Object
{
public:
	Plane(Point position, Vector normal): position(position), normal(normal) {}

	virtual Hit intersect(const Ray& ray);

	Point position;
	Vector normal;
};

#endif
