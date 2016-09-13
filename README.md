# OBJ LOADER

The quick to use single header OBJ loader

## Quick Description

OBJ Loader is a simple, header only, .obj model file loader that will take in a path to a file, load it into the Loader class object, then allow you to get the data from each mesh loaded. This does not load any material data. Only Vertices, Indicies, and Meshes. Good for any prototyping where you need a quick .obj model loaded.

## Prerequisites

OBJ Loader was made with compatibility in mind. So you only need the header file to get going as it uses only STD and self made data structures.

## Installation

All you need to to is copy over the OBJ_Loader.h header file, include it in your solution, and you are good to go. It is located within the source folder.

## Examples

Examples are found within the examples folder. In order to compile these you will need to link OBJ_Loader.h to the compiler in since it is not included within the example folders.

## Quick Use Guide

1. Include OBJ_Loader.h:                         '#include "OBJ_Loader.h"'
2. Create a Loader Object:                       'objl::Loader loader'
3. Load a File Into the Loader Object:           'loader.LoadFile("path_to_object_and_name.obj")'
4. Get What you want out of the Mesh Objects:    'cout << loader.LoadedMeshes[0].MeshName << endl'

## Classes & Structures

These are all of the included classes and only the relevant members and methods. There are others to find if you want but these are all you will need to know to operate.

### Mesh

1. std::string MeshName : The Mesh Name given in the .obj
2. std::vector<Vertex> Vertices : Vertex List
3. std::vector<unsigned int> Indices : Index List

### Vertex

1. Vector3 Position : Position vector
2. Vector3 Normal : Normal vector
3. Vector2 TextureCoordinate : Texture Coordinate vector

### Vector3

1. float X, Y, Z : Position Variables

### Vector2

1. float X, Y : Position Variables

### Loader

1. bool LoadFile(std::string Path) : Load a file from a path. Return true if found and loaded. Return false if not                                                  
2. std::vector<Mesh> LoadedMeshes : Loaded Mesh Objects

## Credits

Robert Smith

## License

OBJ Loader uses the MIT license. The MIT license allows free use and modification of the software as long as they provide credit back to me and don't hold me liable for anything that may go wrong. If you want to read the license in full look into the file entitled: LICENSE