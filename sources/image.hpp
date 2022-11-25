/**
* Framework for a raytracer
* File: image.h
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

#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <iostream>
#include "triple.hpp"

class Image
{
protected:

	Color* _pixel;
	int _width;
	int _height;

public:

	Image(int width = 0, int height = 0): _pixel(0), _width(0), _height(0)
	{
		set_extent(width, height); //creates array
	}

	Image(const char* imageFilename): _pixel(0), _width(0), _height(0)
	{
		read_png(imageFilename);
	}

	~Image()
	{
		if (_pixel) delete[] _pixel;
	}

	// Normal accessors
	inline void put_pixel(int x, int y, Color c);
	inline Color get_pixel(int x, int y) const;

	// Handier accessors
	// Usage: color = img(x,y);
	// 	img(x,y) = color;
	inline const Color& operator()(int x, int y) const;
	inline Color& operator()(int x, int y);

	// Normalized accessors, interval is (0...1, 0...1)
	inline const Color& colorAt(float x, float y) const;

	// Normalized accessors for bumpmapping. Uses green component.
	inline void derivativeAt(float x, float y, float* dx, float* dy) const;

	// Image parameters
	inline int width() const
	{
		return _width;
	}

	inline int height() const
	{
		return _height;
	}

	inline int size() const
	{
		return _width * _height;
	}

	// File stuff
	void write_png(const char* filename) const;
	void read_png(const char* filename);

protected:

	// Integer index
	inline int index(int x, int y) const
	{
		return y * _width + x;
	}

	// Wrapped integer index
	inline int windex(int x, int y) const
	{
		return index(x % _width, y % _height);
	}

	// Float index
	inline int findex(float x, float y) const
	{
		return index(int(x * (_width - 1)), int(y * (_height - 1)));
	}

	// Create a picture. Return false if failed.
	bool set_extent(int width, int height);
};

// Inline functions

inline void Image::put_pixel(int x, int y, Color c)
{
	(*this)(x, y) = c;
}

inline Color Image::get_pixel(int x, int y) const
{
	return (*this)(x, y);
}

inline const Color& Image::operator()(int x, int y) const
{
	return _pixel[index(x, y)];
}

inline Color& Image::operator()(int x, int y)
{
	return _pixel[index(x, y)];
}

inline const Color& Image::colorAt(float x, float y) const
{
	return _pixel[findex(x, y)];
}

inline void Image::derivativeAt(float x, float y, float* dx, float* dy) const
{
	int ix = (int)(x * (_width - 1));
	int iy = (int)(y * (_height - 1));
	*dx = _pixel[windex(ix, iy + 1)].g - _pixel[index(ix, iy)].g;
	*dy = _pixel[windex(ix + 1, iy)].g - _pixel[index(ix, iy)].g;
}

#endif
