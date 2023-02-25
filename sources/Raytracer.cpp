#include <ctype.h>
#include <fstream>
#include <assert.h>
#include "Raytracer.hpp"
#include "objects/Object.hpp"
#include "objects/Sphere.hpp"
#include "objects/Triangle.hpp"
#include "objects/Plane.hpp"
#include "objects/meshs/Cube.hpp"
#include "utils/Material.hpp"
#include "light/Hit.hpp"
#include "light/Ray.hpp"
#include "image/Image.hpp"
#include "yaml/yaml.h"

// Functions to ease reading from YAML input
void operator>> (const YAML::Node& node, Triple& t);
Triple parse_triple(const YAML::Node& node);

void operator>> (const YAML::Node& node, Triple& t)
{
	assert(node.size() == 3);
	node[0] >> t.x;
	node[1] >> t.y;
	node[2] >> t.z;
}

Triple parse_triple(const YAML::Node& node)
{
	Triple t;
	node[0] >> t.x;
	node[1] >> t.y;
	node[2] >> t.z;
	return t;
}

void Raytracer::parse_settings(const YAML::Node& node)
{
	node["resolution"][0] >> scene.resolution[0];
	node["resolution"][1] >> scene.resolution[1];

	node["threads"] >> scene.nb_threads;

	std::string mode;
	node["mode"] >> mode;
	scene.set_mode(mode);

	node["near"] >> scene.near;
	node["far"] >> scene.far;
	node["shadows"] >> scene.shadows_on;
	node["soft_shadows"] >> scene.soft_shadows;
	node["recursions"] >> scene.recursions;
	node["antialiasing"] >> scene.antialiasing;
	node["gooch"] >> scene.gooch;
}

void Raytracer::parse_gooch(const YAML::Node& node)
{
	node["b"] >> scene.b;
	node["y"] >> scene.y;
	node["alpha"] >> scene.alpha;
	node["beta"] >> scene.beta;
}

Material Raytracer::parse_material(const YAML::Node& node)
{
	Material m;
	node["color"] >> m.color;
	node["ambient"] >> m.ambient;
	node["diffuse"] >> m.diffuse;
	node["specular"] >> m.specular;
	node["shininess"] >> m.shininess;
	node["refractive_index"] >> m.refractive_index;
	return m;
}

Object* Raytracer::parse_object(const YAML::Node& node)
{
	Object* returnObject = nullptr;
	std::string objectType;
	node["type"] >> objectType;

	if (objectType == "sphere")
	{
		Point pos;
		node["position"] >> pos;
		float r;
		node["radius"] >> r;
		Vector n;
		node["north"] >> n;
		Vector s;
		node["start"] >> s;
		returnObject = new Sphere(pos, r, n, s);
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
		normal.normalize();
		returnObject = new Plane(position, normal);
	}

	else if (objectType == "cube")
	{
		Point position;
		node["position"] >> position;
		float size;
		node["size"] >> size;
		float pitch;
		node["pitch"] >> pitch;
		float yaw;
		node["yaw"] >> yaw;
		float roll;
		node["roll"] >> roll;
		returnObject = new Cube(position, size, pitch, yaw, roll);
	}

	else if (objectType == "obj")
	{
		std::string path;
		node["file"] >> path;
		Point position;
		node["position"] >> position;
		float size;
		node["size"] >> size;
		float pitch;
		node["pitch"] >> pitch;
		float yaw;
		node["yaw"] >> yaw;
		float roll;
		node["roll"] >> roll;
		returnObject = new Mesh(path, position, size, pitch, yaw, roll);
	}

	if (returnObject)
	{
		// Textures
		std::string texture_path;
		node["texture"] >> texture_path;

		if (texture_path != "none")
			returnObject->texture = new Image(texture_path.data());

		// Normals
		std::string normals_path;
		node["normals"] >> normals_path;

		if (normals_path != "none")
			returnObject->normals = new Image(normals_path.data());

		// Specular
		std::string specular_path;
		node["specular"] >> specular_path;

		if (specular_path != "none")
			returnObject->specular = new Image(specular_path.data());

		// Read the material and attach to object
		returnObject->material = parse_material(node["material"]);
	}

	return returnObject;
}

Light Raytracer::parse_light(const YAML::Node& node)
{
	Point position;
	node["position"] >> position;
	Color color;
	node["color"] >> color;
	return Light(position, color);
}

Camera Raytracer::parse_camera(const YAML::Node& node)
{
	Camera camera;
	node["position"] >> camera.position;
	node["direction"] >> camera.direction;
	camera.direction.normalize();
	node["up"] >> camera.up;
	camera.up.normalize();
	return camera;
}

// Read a scene from file
bool Raytracer::read_scene(const std::string& inputFilename)
{
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

			parse_settings(doc["Settings"]);

			if (scene.gooch)
				parse_gooch(doc["Gooch"]);

			scene.camera = parse_camera(doc["Camera"]);

			// Read and parse the scene objects
			const YAML::Node& sceneObjects = doc["Objects"];

			if (sceneObjects.GetType() != YAML::CT_SEQUENCE)
			{
				std::cerr << "Error: expected a sequence of objects." << std::endl;
				return false;
			}

			for(YAML::Iterator it = sceneObjects.begin(); it != sceneObjects.end(); ++it)
			{
				Object* obj = parse_object(*it);
				// Only add object if it is recognized
				if (obj)
					scene.add_object(obj);
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
				scene.add_light(parse_light(*it));
		}

		if (parser)
			std::cerr << "Warning: unexpected YAML document, ignored." << std::endl;

	}

	catch(YAML::ParserException& e)
	{
		std::cerr << "Error at line " << e.mark.line + 1 << ", col " << e.mark.column + 1 << ": " << e.msg << std::endl;
		return false;
	}

	std::cout << "YAML parsing results: " << scene.get_nb_objects() << " objects read." << std::endl;
	return true;
}

void Raytracer::render_to_file(const std::string& outputFilename)
{
	Image img(scene.resolution[0], scene.resolution[1]);
	std::cout << "Tracing..." << std::endl;
	scene.render(img);
	std::cout << "Writing image to " << outputFilename << "..." << std::endl;
	img.write_png(outputFilename.c_str());
	std::cout << "Done." << std::endl;
}
