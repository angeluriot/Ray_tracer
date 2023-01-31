#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "light/Hit.hpp"
#include "light/Ray.hpp"
#include "utils/Material.hpp"
#include "image/Image.hpp"

class Object
{
public:

	Material material;
	Image* texture;

	virtual Hit intersect(const Ray& ray) const = 0;
};

#endif
