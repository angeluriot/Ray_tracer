#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include "objects/Triangle.hpp"

class Mesh : public Object
{
public:

	std::vector<Triangle> triangles;

	virtual ~Mesh() = 0;

	Hit intersect(const Ray& ray) const override;
};

#endif
