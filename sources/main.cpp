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

	if (!raytracer.read_scene(input_file))
	{
		std::cerr << "Error: reading scene from " << input_file << " failed - no output generated." << std::endl;
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

	raytracer.render_to_file(ofname);

	return 0;
}
