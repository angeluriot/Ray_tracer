#include "Raytracer.hpp"
#include <chrono>
#include <ctime>

int main(int argc, char* argv[])
{
	std::cout << "Introduction to Computer Graphics - Raytracer" << std::endl << std::endl;

	char* default_input = "scenes/final.yaml";
	char* default_output = "output/final.png";
	char* input_file;

	if ((argc < 2 || argc > 3) && default_input == "")
	{
		std::cerr << "Usage: " << argv[0] << " in-file [out-file.png]" << std::endl;
		return EXIT_FAILURE;
	}

	input_file = argc < 2 ? default_input : argv[1];

	Raytracer raytracer;

	if (!raytracer.read_scene(input_file))
	{
		std::cerr << "Error: reading scene from " << input_file << " failed - no output generated." << std::endl;
		return EXIT_FAILURE;
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

	auto start = std::chrono::system_clock::now();

	raytracer.render_to_file(ofname);

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<float> elapsed_seconds = end - start;
	std::cout << "Computation time: " << elapsed_seconds.count() << "s" << std::endl;

	return EXIT_SUCCESS;
}
