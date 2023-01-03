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
	Camera camera;
	Mode mode;
	float near;
	float far;
	bool shadows_on;
	int recursions;
	int antialiasing;

public:

	Color trace(const Ray& ray, int depth = 0);
	void render(Image& image);
	void add_object(Object* object);
	void add_light(const Light& light);
	void set_camera(Camera camera);
	Camera get_camera() const;
	void set_mode(const std::string& mode);
	void set_distances(float near, float far);
	void set_shadows(bool shadows_on);
	void set_nb_recursions(int recursions);
	void set_antialiasing(int antialiasing);
	Mode get_mode();
	unsigned int get_nb_objects();
	unsigned int get_nb_lights();
};

#endif
