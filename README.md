# OBJ LOADER

## Quick Description

OBJ Loader is a simple .obj File Loader

## Slightly Longer Description

OBJ Loader is a simple .obj model file loader that will take in a path to a file, load it into the Loader class object, then allow you to get the data from each mesh loaded.

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



## License

OBJ Loader uses the MIT license. The MIT license allows free use and modification of the software as long as they provide credit back to me and don't hold me liable for anything that may go wrong. If you want to read the license in full look into the file entitled: LICENSE.md