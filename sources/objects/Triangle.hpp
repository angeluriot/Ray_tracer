#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "utils/Triple.hpp"
#include "objects/Object.hpp"

class Triangle : public Object
{
public:

	Triangle() = default;
	Triangle(Point point_1, Point point_2, Point point_3): point_1(point_1), point_2(point_2), point_3(point_3) {}

	virtual Hit intersect(const Ray& ray);

	Point point_1;
	Point point_2;
	Point point_3;
};

#endif
