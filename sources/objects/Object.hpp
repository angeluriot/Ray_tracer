#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "light/Hit.hpp"
#include "light/Ray.hpp"

class Material;

class Object
{
public:

	Material* material;

	virtual ~Object() {}

	virtual Hit intersect(const Ray& ray) = 0;
};

#endif
