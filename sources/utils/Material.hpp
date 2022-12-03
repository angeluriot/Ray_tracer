#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "utils/Triple.hpp"

class Material
{
public:

	Color color;		// Base color
	float ambient;		// Ambient intensity
	float diffuse;		// Diffuse intensity
	float specular;		// Specular intensity
	float shininess;	// Exponent for specular highlight size

	Material() {}
};

#endif
