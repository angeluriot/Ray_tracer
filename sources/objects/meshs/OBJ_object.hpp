
#ifndef OBJ_OBJECT_HPP
#define OBJ_OBJECT_HPP


// Iostream - STD I/O Library
#include <iostream>

// fStream - STD File I/O Library
#include <fstream>

#include "OBJ_Loader.h"

#include <array>
#include "objects/meshs/Mesh.hpp"

class OBJ_object : public Mesh
{
public:

  objl::Loader Loader;

	OBJ_object(const char* filename){
    Loader.LoadFile(filename);
  }
};

#endif