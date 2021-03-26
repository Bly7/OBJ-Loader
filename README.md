# OBJ LOADER

The quick to use single header OBJ loader

## Quick Description

OBJ Loader is a simple, header only, .obj model file loader that will take in a path to a file, load it into the Loader class object, then allow you to get the data from each mesh loaded. This will load each mesh within the model with the corresponding data such as vertices, indices, and material. Plus a large array of vertices, indices and materials which you can do whatever you want with.

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

### Vector2

1. float X, Y : Position Variables

### Vector3

1. float X, Y, Z : Position Variables

### Vertex

1. Vector3 Position : Position vector
2. Vector3 Normal : Normal vector
3. Vector2 TextureCoordinate : Texture Coordinate vector

### Material

1. std::string name : Name of loaded material
2. Vector3 Ka : Ambient color
3. Vector3 Kd : Diffuse color
4. Vector3 Ks : Specular color
5. float Ns : Specular exponent
6. float Ni : Optical density
7. float d : Dissolve variable
8. int illum : Illumination variable
9. std::string map_Ka : Ambient texture map name
10. std::string map_Kd : Diffuse texture map name
11. std::string map_Ks : Specular texture map name
12. std::string map_d : Alpha texture map name
13. std::string map_bump : Bump map name

### Mesh

1. std::string MeshName : The Mesh Name given in the .obj
2. std::vector<Vertex> Vertices : Vertex List
3. std::vector<unsigned int> Indices : Index List
4. Material MeshMaterial : Material assigned to this mesh

### Loader

1. bool LoadFile(std::string Path) : Load a file from a path. Return true if found and loaded. Return false if not                                                  
2. std::vector<Mesh> LoadedMeshes : Loaded Mesh Objects
3. std::vector<Vertex> LoadedVertices : Loaded Vertex Objects
4. std::vector<unsigned int> LoadedIndices : Loaded Index Positions
5. std::vector<Material> LoadedMaterials : Loaded Material Objects

## Credits

Robert Smith

## License

OBJ Loader uses the MIT license. The MIT license allows free use and modification of the software as long as they provide credit back to me and don't hold me liable for anything that may go wrong. If you want to read the license in full look into the file entitled: LICENSE

## Version Information

### Current Version

Version 2.0

### Upcoming Features

---- THIS IS NO LONGER BEING SUPPORTED ----

1. Bug Fixing
2. Adding more variables

### Previous Versions

#### Version 1.0 (September-13-2016)

1. Base Implementation Done
2. README Created
3. LICENSE Created
4. Mesh Index and Vertex Load Implemented

#### Version 2.0 (September-14-2016)

1. Now Reads Material Data
