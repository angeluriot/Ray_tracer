/**
* Framework for a raytracer
* File: image.cpp
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

#include <fstream>
#include "image.hpp"
#include "lodepng/lodepng.h"

// Create a picture. Answer false if failed.
bool Image::set_extent(int width, int height)
{
	_width = width;
	_height = height;
	if (_pixel) delete[] _pixel;
	_pixel = size() > 0 ? new Color[size()] : 0;
	return _pixel != 0;
}

void Image::write_png(const char* filename) const
{
	std::vector<unsigned char> image;
	image.resize(_width * _height * 4);
	std::vector<unsigned char>::iterator imageIterator = image.begin();
	Color* currentPixel = _pixel;

	while (imageIterator != image.end())
	{
		*imageIterator = (unsigned char)(currentPixel->r * 255.);
		imageIterator++;
		*imageIterator = (unsigned char)(currentPixel->g * 255.);
		imageIterator++;
		*imageIterator = (unsigned char)(currentPixel->b * 255.);
		imageIterator++;
		*imageIterator = 255;
		imageIterator++;
		currentPixel++;
	}

	LodePNG::encode(filename, image, _width, _height);
}

void Image::read_png(const char* filename)
{
	std::vector<unsigned char> buffer, image;

	// Load the image file with given filename
	LodePNG::loadFile(buffer, filename);

	// Decode the png
	LodePNG::Decoder decoder;
	decoder.decode(image, buffer.empty() ? 0 : &buffer[0], (unsigned)buffer.size());
	std::cout << decoder.getChannels() << std::endl;
	std::cout << decoder.getBpp() << std::endl;

	if (decoder.getChannels() < 3 || decoder.getBpp() < 24)
	{
		std::cerr << "Error: only color (RGBA), 8 bit per channel png images are supported." << std::endl;
		std::cerr << "Either convert your image or change the sourcecode." << std::endl;
		exit(1);
	}

	int w = decoder.getWidth();
	int h = decoder.getHeight();
	set_extent(w, h);

	// Now convert the image data
	std::vector<unsigned char>::iterator imageIterator = image.begin();
	Color* currentPixel = _pixel;

	while (imageIterator != image.end())
	{
		currentPixel->r = (*imageIterator) / 255.;
		imageIterator++;
		currentPixel->g = (*imageIterator) / 255.;
		imageIterator++;
		currentPixel->b = (*imageIterator) / 255.;
		imageIterator++;
		// Let's just ignore the alpha channel
		imageIterator++;
		currentPixel++;
	}
}
