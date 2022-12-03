#ifndef CUBE_HPP
#define CUBE_HPP

#include <array>
#include "objects/Triangle.hpp"

class Cube : public Object
{
public:

	Cube(Point position, double size, double pitch, double yaw, double roll);

	virtual Hit intersect(const Ray& ray);

	std::array<Triangle, 12> triangles;
};

#endif
