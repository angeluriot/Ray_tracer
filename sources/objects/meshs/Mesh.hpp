#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include "objects/Triangle.hpp"

class Mesh : public Object
{
public:

	std::vector<Triangle> triangles;

	Mesh() = default;
	Mesh(const std::string& filename, const Point& position, float size, float pitch, float yaw, float roll);

	void init(const Point& position, float size, float pitch, float yaw, float roll);
	Hit intersect(const Ray& ray) const override;
};

#endif
