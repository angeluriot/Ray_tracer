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
	std::vector<Light*> lights;
	Triple eye;
	Mode mode;

public:

	Color trace(const Ray& ray);
	void render(Image& img);
	void addObject(Object* o);
	void addLight(Light* l);
	void setEye(Triple e);

	void setMode(const std::string& mode)
	{
		if (mode == "default")
			this->mode = Mode::Default;
		else if (mode == "normals")
			this->mode = Mode::Normals;
		else if (mode == "z-buffer")
			this->mode = Mode::ZBuffer;
	}

	Mode getMode()
	{
		return mode;
	}

	unsigned int getNumObjects()
	{
		return objects.size();
	}

	unsigned int getNumLights()
	{
		return lights.size();
	}
};

#endif
