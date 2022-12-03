/**
* Framework for a raytracer
* File: raytracer.cpp
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

#include <ctype.h>
#include <fstream>
#include <assert.h>
#include "raytracer.hpp"
#include "object.hpp"
#include "sphere.hpp"
#include "triangle.hpp"
#include "plane.hpp"
#include "cube.hpp"
#include "material.hpp"
#include "light.hpp"
#include "image.hpp"
#include "yaml/yaml.h"

// Functions to ease reading from YAML input
void operator>> (const YAML::Node& node, Triple& t);
Triple parseTriple(const YAML::Node& node);

void operator>> (const YAML::Node& node, Triple& t)
{
	assert(node.size() == 3);
	node[0] >> t.x;
	node[1] >> t.y;
	node[2] >> t.z;
}

Triple parseTriple(const YAML::Node& node)
{
	Triple t;
	node[0] >> t.x;
	node[1] >> t.y;
	node[2] >> t.z;
	return t;
}

Material* Raytracer::parseMaterial(const YAML::Node& node)
{
	Material* m = new Material();
	node["color"] >> m->color;
	node["ka"] >> m->ka;
	node["kd"] >> m->kd;
	node["ks"] >> m->ks;
	node["n"] >> m->n;
	return m;
}

Object* Raytracer::parseObject(const YAML::Node& node)
{
	Object* returnObject = NULL;
	std::string objectType;
	node["type"] >> objectType;

	if (objectType == "sphere")
	{
		Point pos;
		node["position"] >> pos;
		double r;
		node["radius"] >> r;
		returnObject = new Sphere(pos,r);
	}

	else if (objectType == "triangle")
	{
		Point point_1;
		node["point_1"] >> point_1;
		Point point_2;
		node["point_2"] >> point_2;
		Point point_3;
		node["point_3"] >> point_3;
		returnObject = new Triangle(point_1, point_2, point_3);
	}

	else if (objectType == "plane")
	{
		Point position;
		node["position"] >> position;
		Vector normal;
		node["normal"] >> normal;
		returnObject = new Plane(position, normal);
	}

	else if (objectType == "cube")
	{
		Point position;
		node["position"] >> position;
		double size;
		node["size"] >> size;
		double pitch;
		node["pitch"] >> pitch;
		double yaw;
		node["yaw"] >> yaw;
		double roll;
		node["roll"] >> roll;
		returnObject = new Cube(position, size, pitch, yaw, roll);
	}

	if (returnObject)
	{
		// Read the material and attach to object
		returnObject->material = parseMaterial(node["material"]);
	}

	return returnObject;
}

Light* Raytracer::parseLight(const YAML::Node& node)
{
	Point position;
	node["position"] >> position;
	Color color;
	node["color"] >> color;
	return new Light(position,color);
}

// Read a scene from file
bool Raytracer::readScene(const std::string& inputFilename)
{
	// Initialize a new scene
	scene = new Scene();

	// Open file stream for reading and have the YAML module parse it
	std::ifstream fin(inputFilename.c_str());

	if (!fin)
	{
		std::cerr << "Error: unable to open " << inputFilename << " for reading." << std::endl;
		return false;
	}

	try
	{
		YAML::Parser parser(fin);

		if (parser)
		{
			YAML::Node doc;
			parser.GetNextDocument(doc);

			scene->setIsNormalBufferImage(doc["Params"]["isNormalBufferImage"]);

			// Read scene configuration options
			scene->setEye(parseTriple(doc["Eye"]));

			// Read and parse the scene objects
			const YAML::Node& sceneObjects = doc["Objects"];

			if (sceneObjects.GetType() != YAML::CT_SEQUENCE)
			{
				std::cerr << "Error: expected a sequence of objects." << std::endl;
				return false;
			}

			for(YAML::Iterator it = sceneObjects.begin(); it != sceneObjects.end(); ++it)
			{
				Object* obj = parseObject(*it);
				// Only add object if it is recognized
				if (obj)
					scene->addObject(obj);
				else
					std::cerr << "Warning: found object of unknown type, ignored." << std::endl;
			}

			// Read and parse light definitions
			const YAML::Node& sceneLights = doc["Lights"];

			if (sceneObjects.GetType() != YAML::CT_SEQUENCE)
			{
				std::cerr << "Error: expected a sequence of lights." << std::endl;
				return false;
			}

			for(YAML::Iterator it = sceneLights.begin(); it != sceneLights.end(); ++it)
				scene->addLight(parseLight(*it));
		}

		if (parser)
			std::cerr << "Warning: unexpected YAML document, ignored." << std::endl;

	}

	catch(YAML::ParserException& e)
	{
		std::cerr << "Error at line " << e.mark.line + 1 << ", col " << e.mark.column + 1 << ": " << e.msg << std::endl;
		return false;
	}

	std::cout << "YAML parsing results: " << scene->getNumObjects() << " objects read." << std::endl;
	return true;
}

void Raytracer::renderToFile(const std::string& outputFilename)
{
	Image img(400, 400);
	std::cout << "Tracing..." << std::endl;
	scene->render(img);
	std::cout << "Writing image to " << outputFilename << "..." << std::endl;
	img.write_png(outputFilename.c_str());
	std::cout << "Done." << std::endl;
}
