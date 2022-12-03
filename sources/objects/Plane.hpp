#ifndef PLANE_HPP
#define PLANE_HPP

#include "utils/Triple.hpp"
#include "objects/Object.hpp"

class Plane : public Object
{
public:

	Plane(Point position, Vector normal): position(position), normal(normal) {}

	virtual Hit intersect(const Ray& ray);

	Point position;
	Vector normal;
};

#endif
