#ifndef RAYTRACER_HPP
#define RAYTRACER_HPP

#include <string>
#include "utils/Triple.hpp"
#include "light/Light.hpp"
#include "scene/Scene.hpp"
#include "yaml/yaml.h"

class Raytracer
{
private:

	Scene scene;

	// Couple of private functions for parsing YAML nodes
	Material parse_material(const YAML::Node& node);
	Object* parse_object(const YAML::Node& node);
	Light parse_light(const YAML::Node& node);

public:

	Raytracer() {}

	bool read_scene(const std::string& inputFilename);
	void render_to_file(const std::string& outputFilename);
};

#endif
