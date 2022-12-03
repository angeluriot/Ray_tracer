#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "utils/Triple.hpp"
#include "objects/Object.hpp"

class Sphere : public Object
{
public:

	Sphere(Point position, double radius): position(position), radius(radius) {}

	virtual Hit intersect(const Ray& ray);

	Point position;
	double radius;
};

#endif
