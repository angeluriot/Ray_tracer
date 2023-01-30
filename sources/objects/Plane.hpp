#ifndef PLANE_HPP
#define PLANE_HPP

#include "utils/Triple.hpp"
#include "objects/Object.hpp"

class Plane : public Object
{
public:

	Point position;
	Vector normal;

	Plane(const Point& position, const Vector& normal);
	Hit intersect(const Ray& ray) const override;
};

#endif
