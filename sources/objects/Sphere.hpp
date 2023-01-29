#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "utils/Triple.hpp"
#include "objects/Object.hpp"

class Sphere : public Object
{
public:

	Point position;
	float radius;

	Sphere(const Point& position, float radius): position(position), radius(radius) {}

	Hit intersect(const Ray& ray) const override;

	void compute_texture() const;
};

#endif
