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

'std::string MeshName' :                            The Mesh Name given in the .obj
'std::vector<Vertex> Vertices' :                    Vertex List
'std::vector<unsigned int> Indices' :               Index List

### Vertex

'Vector3 Position' :                                Position vector
'Vector3 Normal' :                                  Normal vector
'Vector2 TextureCoordinate' :                       Texture Coordinate vector

### Vector3

'float X, Y, Z' :                                   XYZ Position Variables

### Vector2

'float X, Y' :                                      XY Position Variables

### Loader

'bool LoadFile(sstd::string Path)' :                Load a file from a path. Return true if found and loaded. Return false if not
                                                    
'std::vector<Mesh> LoadedMeshes' :                  Loaded Mesh Objects



## License

OBJ Loader uses the MIT license. The MIT license allows free use and modification of the software as long as they provide credit back to me and don't hold me liable for anything that may go wrong. If you want to read the license in full look into the file entitled: LICENSE.md