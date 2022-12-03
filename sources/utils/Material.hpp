#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "utils/Triple.hpp"

class Material
{
public:

	Color color;	// Base color
	double ka;		// Ambient intensity
	double kd;		// Diffuse intensity
	double ks;		// Specular intensity
	double n;		// Exponent for specular highlight size

	Material() {}
};

#endif
