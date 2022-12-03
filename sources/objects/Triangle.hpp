#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "utils/Triple.hpp"
#include "objects/Object.hpp"

class Triangle : public Object
{
public:

	Point point_1;
	Point point_2;
	Point point_3;

	Triangle(const Point& point_1, const Point& point_2, const Point& point_3): point_1(point_1), point_2(point_2), point_3(point_3) {}

	Hit intersect(const Ray& ray) const override;
};

#endif
