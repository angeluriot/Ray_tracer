/**
* Framework for a raytracer
* File: material.h
*
* Created for the Computer Science course "Introduction Computer Graphics"
* taught at the University of Groningen by Tobias Isenberg.
*
* Author: Maarten Everts
*
* This framework is inspired by and uses code of the raytracer framework of
* Bert Freudenberg that can be found at
* http://isgwww.cs.uni-magdeburg.de/graphik/lehre/cg2/projekt/rtprojekt.html
*/

#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <iostream>
#include "triple.hpp"

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
