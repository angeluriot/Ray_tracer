#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "light/Hit.hpp"
#include "light/Ray.hpp"
#include "utils/Material.hpp"

class Object
{
public:

	Material material;
	int texture_png;

	virtual Hit intersect(const Ray& ray) const = 0;

	//virtual void compute_texture() const = 0;
};

#endif
