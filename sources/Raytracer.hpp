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

	Scene* scene;

	Material parse_material(const YAML::Node& node);
	Object* parse_object(const YAML::Node& node);
	Light parse_light(const YAML::Node& node);

public:

	bool read_scene(const std::string& inputFilename);
};

#endif
