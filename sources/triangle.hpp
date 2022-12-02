#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "object.hpp"

class Triangle : public Object
{
public:
	Triangle(Point point_1, Point point_2, Point point_3): point_1(point_1), point_2(point_2), point_3(point_3) {}

	virtual Hit intersect(const Ray& ray);

	const Point point_1;
	const Point point_2;
	const Point point_3;
};

#endif
