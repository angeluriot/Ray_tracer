/**
* Framework for a raytracer
* File: object.h
*
* Created for the Computer Science course "Introduction Computer Graphics"
* taught at the University of Groningen by Tobias Isenberg.
*
* Authors:
* Maarten Everts
* Jasper van de Gronde
*
* This framework is inspired by and uses code of the raytracer framework of
* Bert Freudenberg that can be found at
* http://isgwww.cs.uni-magdeburg.de/graphik/lehre/cg2/projekt/rtprojekt.html
*/

#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "triple.hpp"
#include "light.hpp"

class Material;

class Object
{
public:

	Material* material;

	virtual ~Object() {}

	virtual Hit intersect(const Ray& ray) = 0;
};

#endif
