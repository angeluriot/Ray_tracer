#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "utils/Triple.hpp"
#include "light/Light.hpp"
#include "light/Ray.hpp"
#include "objects/Object.hpp"
#include "image/Image.hpp"

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
	Point eye;
	Mode mode;
	float near;
	float far;
	bool shadows_on;

public:

	Color trace(const Ray& ray);
	void render(Image& image);
	void add_object(Object* object);
	void add_light(const Light& light);
	void set_eye(Point eye);
	void set_mode(const std::string& mode);
	void set_distances(float near, float far);
	void set_shadows(bool shadows_on);
	Mode get_mode();
	unsigned int get_nb_objects();
	unsigned int get_nb_lights();
};

#endif
