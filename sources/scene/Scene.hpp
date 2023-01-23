#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "utils/Triple.hpp"
#include "light/Light.hpp"
#include "light/Ray.hpp"
#include "objects/Object.hpp"
#include "image/Image.hpp"
#include "utils/Camera.hpp"

class Scene
{
public:

	enum class Mode
	{
		Default,
		Normals,
		ZBuffer
	};

private:

	std::vector<Object*> objects;
	std::vector<Light> lights;

public:

	std::array<int, 2> resolution;
	Mode mode;
	Camera camera;
	float near;
	float far;
	bool shadows_on;
	int recursions;
	int antialiasing;

	Color trace(const Ray& ray, int depth = 0);
	void render(Image& image);
	void add_object(Object* object);
	void add_light(const Light& light);
	void set_mode(const std::string& mode);
	unsigned int get_nb_objects();
	unsigned int get_nb_lights();
};

#endif
