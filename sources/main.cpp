/**
* Framework for a raytracer
* File: main.cpp
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

#include "Raytracer.hpp"

int main(int argc, char* argv[])
{
	std::cout << "Introduction to Computer Graphics - Raytracer" << std::endl << std::endl;

	char* default_input = "scenes/custom.yaml";
	char* default_output = "output/custom.png";
	char* input_file;

	if ((argc < 2 || argc > 3) && default_input == "")
	{
		std::cerr << "Usage: " << argv[0] << " in-file [out-file.png]" << std::endl;
		return 1;
	}

	input_file = argc < 2 ? default_input : argv[1];

	Raytracer raytracer;

	if (!raytracer.readScene(input_file))
	{
		std::cerr << "Error: reading scene from " << input_file << " failed - no output generated."<< std::endl;
		return 1;
	}

	std::string ofname;

	if (argc >= 3)
		ofname = argv[2];

	else if (default_output != "")
		ofname = default_output;

	else
	{
		ofname = input_file;

		if (ofname.size() >= 5 && ofname.substr(ofname.size() - 5) == ".yaml")
			ofname = ofname.substr(0, ofname.size() - 5);

		ofname += ".png";
	}

	raytracer.renderToFile(ofname);

	return 0;
}
