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
private:

	std::vector<Object*> objects;
	std::vector<Light*> lights;
	Triple eye;
	bool isNormalBufferImage;

public:

	Color trace(const Ray& ray);
	void render(Image& img);
	void addObject(Object* o);
	void addLight(Light* l);
	void setEye(Triple e);
	void setIsNormalBufferImage(bool value) 
	{ 
		this->isNormalBufferImage = value;
	}

	bool getIsNormalBufferImage()
	{ 
		return isNormalBufferImage; 
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
