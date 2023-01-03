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

	static Scene scene;

	static Material parse_material(const YAML::Node& node);
	static Object* parse_object(const YAML::Node& node);
	static Light parse_light(const YAML::Node& node);

public:

	static bool read_scene(const std::string& inputFilename);
};

#endif
