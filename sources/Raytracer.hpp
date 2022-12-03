/**
* Framework for a raytracer
* File: raytracer.h
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

#ifndef RAYTRACER_HPP
#define RAYTRACER_HPP

#include <iostream>
#include <string>
#include "utils/Triple.hpp"
#include "light/Light.hpp"
#include "scene/Scene.hpp"
#include "yaml/yaml.h"

class Raytracer
{
private:

	Scene* scene;

	// Couple of private functions for parsing YAML nodes
	Material* parseMaterial(const YAML::Node& node);
	Object* parseObject(const YAML::Node& node);
	Light* parseLight(const YAML::Node& node);

public:

	Raytracer() {}

	bool readScene(const std::string& inputFilename);
	void renderToFile(const std::string& outputFilename);
};

#endif
