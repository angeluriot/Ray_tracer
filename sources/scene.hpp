/**
* Framework for a raytracer
* File: scene.h
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

#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "triple.hpp"
#include "light.hpp"
#include "object.hpp"
#include "image.hpp"

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
