#pragma once

#include <vector>

#include <string>

#include <fstream>

namespace objl
{
	struct Vector2
	{
		Vector2()
		{

		}
		Vector2(float X_, float Y_)
		{
			X = X_;
			Y = Y_;
		}
		bool operator==(const Vector2& other) const
		{
			return (this->X == other.X && this->Y == other.Y);
		}
		bool operator!=(const Vector2& other) const
		{
			return !(this->X == other.X && this->Y == other.Y);
		}
		Vector2 operator+(const Vector2& right) const
		{
			return Vector2(this->X + right.X, this->Y + right.Y);
		}
		Vector2 operator-(const Vector2& right) const
		{
			return Vector2(this->X - right.X, this->Y - right.Y);
		}
		Vector2 operator*(const float& other) const
		{
			return Vector2(this->X *other, this->Y * other);
		}

		float X, Y = 0.0f;
	};

	struct Vector3
	{
		Vector3()
		{

		}
		Vector3(float X_, float Y_, float Z_)
		{
			X = X_;
			Y = Y_;
			Z = Z_;
		}
		bool operator==(const Vector3& other) const
		{
			return (this->X == other.X && this->Y == other.Y && this->Z == other.Z);
		}
		bool operator!=(const Vector3& other) const
		{
			return !(this->X == other.X && this->Y == other.Y && this->Z == other.Z);
		}
		Vector3 operator+(const Vector3& right) const
		{
			return Vector3(this->X + right.X, this->Y + right.Y, this->Z + right.Z);
		}
		Vector3 operator-(const Vector3& right) const
		{
			return Vector3(this->X - right.X, this->Y - right.Y, this->Z - right.Z);
		}
		Vector3 operator*(const float& other) const
		{
			return Vector3(this->X *other, this->Y * other, this->Z - other);
		}

		float X, Y, Z = 0.0f;
	};

	Vector3 operator*(const float& left, const Vector3& right)
	{
		return Vector3(right.X * left, right.Y * left, right.Z * left);
	}

	inline void split(const std::string &in,
		std::vector<std::string> &out,
		std::string token)
	{
		out.clear();

		std::string temp;

		for (int i = 0; i < int(in.size()); i++)
		{
			std::string test = in.substr(i, token.size());

			if (test == token)
			{
				if (!temp.empty())
				{
					out.push_back(temp);
					temp.clear();
					i += token.size() - 1;
				}
				else
				{
					out.push_back("");
				}
			}
			else if (i + token.size() >= in.size())
			{
				temp += in.substr(i, token.size());
				out.push_back(temp);
				break;
			}
			else
			{
				temp += in[i];
			}
		}
	}

	Vector3 CrossV3(const Vector3 a, const Vector3 b)
	{
		return Vector3(a.Y * b.Z - a.Z * b.Y,
			a.Z * b.X - a.X * b.Z,
			a.X * b.Y - a.Y * b.X);
	}

	float MagnitudeV3(const Vector3 in)
	{
		return (sqrtf(powf(in.X, 2) + powf(in.Y, 2) + powf(in.Z, 2)));
	}

	float DotV3(const Vector3 a, const Vector3 b)
	{
		return (a.X * b.X) + (a.Y * b.Y) + (a.Z * b.Z);
	}

	bool inTriangle(Vector3 point, Vector3 tri1, Vector3 tri2, Vector3 tri3)
	{
		// Starting vars
		Vector3 u = tri2 - tri1;
		Vector3 v = tri3 - tri1;
		Vector3 w = point - tri1;
		Vector3 n = CrossV3(u, v);

		float y = (DotV3(CrossV3(u, w), n) / DotV3(n, n));
		float b = (DotV3(CrossV3(u, w), n) / DotV3(n, n));
		float a = 1 - y - b;

		// Projected point
		Vector3  p = (a * tri1) + (b * tri2) + (y * tri3);

		if (a >= 0 && a <= 1
			&& b >= 0 && b <= 1
			&& y >= 0 && y <= 1)
		{
			return true;
		}
		else
			return false;
	}



	float AngleBetweenV3(const Vector3 a, const Vector3 b)
	{
		float angle = DotV3(a, b);
		angle /= (MagnitudeV3(a) * MagnitudeV3(b));
		return angle = acosf(angle);
	}

	struct Vertex
	{
		// Position Vector
		Vector3 Position;

		// Normal Vector
		Vector3 Normal;

		// Texture Coordinate Vector
		Vector2 TextureCoordinate;
	};

	struct Mesh
	{
		Mesh()
		{

		}
		Mesh(std::vector<Vertex>& _Vertices, std::vector<unsigned int>& _Indices)
		{
			Vertices = _Vertices;
			Indices = _Indices;
		}
		std::string MeshName;
		std::vector<Vertex> Vertices;
		std::vector<unsigned int> Indices;
	};

	class Loader
	{
	public:
		Loader()
		{

		}

		bool LoadFile(std::string Path)
		{
			std::ifstream file(Path);

			if (!file.is_open())
				return false;

			LoadedMeshes.clear();
			LoadedVertices.clear();
			LoadedIndices.clear();

			std::vector<Vector3> Positions;
			std::vector<Vector2> TCoords;
			std::vector<Vector3> Normals;

			std::vector<Vertex> Vertices;
			std::vector<unsigned int> Indices;

			bool listening = false;
			std::string meshname;

			Mesh tempMesh;

			std::string curline;
			while (std::getline(file, curline))
			{
				if (curline.substr(0, 2) == "o " || curline.substr(0, 2) == "g " || curline[0] == 'g')
				{
					if (!listening)
					{
						listening = true;

						if (curline.substr(0, 2) == "o " || curline.substr(0, 2) == "g ")
						{
							meshname = curline.substr(2, curline.size());
						}
						else
						{
							meshname = "unnamed";
						}
					}
					else
					{
						// Generate the mesh to put into the array

						if (!Indices.empty() && !Vertices.empty())
						{
							// Create Mesh
							tempMesh = Mesh(Vertices, Indices);
							tempMesh.MeshName = meshname;

							// Insert Mesh
							LoadedMeshes.push_back(tempMesh);

							// Cleanup
							Vertices.clear();
							Indices.clear();
							meshname.clear();

							meshname = curline.substr(2, curline.size());
						}
						else
						{
							if (curline.substr(0, 2) == "o " || curline.substr(0, 2) == "g ")
							{
								meshname = curline.substr(2, curline.size());
							}
							else
							{
								meshname = "unnamed";
							}
						}
					}
				}
				if (curline.substr(0, 2) == "v ")
				{
					std::vector<std::string> spos;
					Vector3 vpos;
					split(curline.substr(2, curline.size() - 1), spos, " ");

					vpos.X = std::stof(spos[0]);
					vpos.Y = std::stof(spos[1]);
					vpos.Z = std::stof(spos[2]);

					Positions.push_back(vpos);
				}
				if (curline.substr(0, 3) == "vt ")
				{
					std::vector<std::string> stex;
					Vector2 vtex;
					split(curline.substr(3, curline.size()), stex, " ");

					vtex.X = std::stof(stex[0]);
					vtex.Y = std::stof(stex[1]);

					TCoords.push_back(vtex);
				}
				if (curline.substr(0, 3) == "vn ")
				{
					std::vector<std::string> snor;
					Vector3 vnor;
					split(curline.substr(3, curline.size()), snor, " ");

					vnor.X = std::stof(snor[0]);
					vnor.Y = std::stof(snor[1]);
					vnor.Z = std::stof(snor[2]);

					Normals.push_back(vnor);
				}
				if (curline.substr(0, 2) == "f ")
				{
					// Generate the vertices
					std::vector<Vertex> vVerts;
					GenVerticesFromRawOBJ(vVerts, Positions, TCoords, Normals, curline);

					// Add Vertices
					for (int i = 0; i < int(vVerts.size()); i++)
					{
						Vertices.push_back(vVerts[i]);
					}

					std::vector<unsigned int> iIndices;

					VertexTriangluation(iIndices, vVerts);

					// Add Indices
					for (int i = 0; i < int(iIndices.size()); i++)
					{
						int indnum = ((Vertices.size()) - vVerts.size()) + iIndices[i];
						Indices.push_back(indnum);
					}
				}
			}

			// Deal with last mesh

			if (!Indices.empty() && !Vertices.empty())
			{
				// Create Mesh
				tempMesh = Mesh(Vertices, Indices);
				tempMesh.MeshName = meshname;

				// Insert Mesh
				LoadedMeshes.push_back(tempMesh);
			}

			file.close();
		}

		std::vector<Mesh> LoadedMeshes;
		std::vector<Vertex> LoadedVertices;
		std::vector<unsigned int> LoadedIndices;

	private:
		void GenVerticesFromRawOBJ(std::vector<Vertex>& oVerts,
			const std::vector<Vector3>& iPositions,
			const std::vector<Vector2>& iTCoords,
			const std::vector<Vector3>& iNormals,
			std::string icurline)
		{
			std::vector<std::string> sface, svert;
			Vertex vVert;
			split(icurline.substr(2, icurline.size()), sface, " ");

			bool noNormal = false;

			// For every given vertex do this
			for (int i = 0; i < int(sface.size()); i++)
			{
				// See What type the vertex is.
				int vtype;

				split(sface[i], svert, "/");

				// Check for just position - v1
				if (svert.size() == 1)
				{
					// Only position
					vtype = 1;
				}

				// Check for position & texture - v1/vt1
				if (svert.size() == 2)
				{
					// Position & Texture
					vtype = 2;
				}

				// Check for Position, Texture and Normal - v1/vt1/vn1
				// or if Position and Normal - v1//vn1
				if (svert.size() == 3)
				{
					if (svert[1] != "")
					{
						// Position, Texture, and Normal
						vtype = 4;
					}
					else
					{
						// Position & Normal
						vtype = 3;
					}
				}

				// Calculate and store the vertex
				switch (vtype)
				{
				case 1: // P
				{
					vVert.Position = iPositions[stoi(svert[0]) - 1];
					vVert.TextureCoordinate = Vector2(0, 0);
					noNormal = true;
					oVerts.push_back(vVert);
					break;
				}
				case 2: // P/T
				{
					vVert.Position = iPositions[stoi(svert[0]) - 1];
					vVert.TextureCoordinate = iTCoords[stoi(svert[1]) - 1];
					noNormal = true;
					oVerts.push_back(vVert);
					break;
				}
				case 3: // P//N
				{
					vVert.Position = iPositions[stoi(svert[0]) - 1];
					vVert.TextureCoordinate = Vector2(0, 0);
					vVert.Normal = iNormals[stoi(svert[2]) - 1];
					oVerts.push_back(vVert);
					break;
				}
				case 4: // P/T/N
				{
					vVert.Position = iPositions[stoi(svert[0]) - 1];
					vVert.TextureCoordinate = iTCoords[stoi(svert[1]) - 1];
					vVert.Normal = iNormals[stoi(svert[2]) - 1];
					oVerts.push_back(vVert);
					break;
				}
				default:
				{
					break;
				}
				}
			}

			// take care of missing normals
			// these may not be truly acurate but it is the 
			// best they get for not compiling a mesh with normals	
			if (noNormal)
			{
				Vector3 A = oVerts[0].Position - oVerts[1].Position;
				Vector3 B = oVerts[2].Position - oVerts[1].Position;

				Vector3 normal = CrossV3(A, B);

				for (int i = 0; i < int(oVerts.size()); i++)
				{
					oVerts[i].Normal = normal;
				}
			}
		}

		void VertexTriangluation(std::vector<unsigned int>& oIndices,
			const std::vector<Vertex>& iVerts)
		{
			// If there are 2 or less verts,
			// no triangle can be created,
			// so exit
			if (iVerts.size() < 3)
			{
				return;
			}
			// If it is a triangle no need to calculate it
			if (iVerts.size() == 3)
			{
				oIndices.push_back(0);
				oIndices.push_back(1);
				oIndices.push_back(2);
				return;
			}

			// Create a list of vertices
			std::vector<Vertex> tVerts = iVerts;

			while (true)
			{
				// For every vertex
				for (int i = 0; i < int(tVerts.size()); i++)
				{
					// pPrev = the previous vertex in the list
					Vertex pPrev;
					if (i == 0)
					{
						pPrev = tVerts[tVerts.size() - 1];
					}
					else
					{
						pPrev = tVerts[i - 1];
					}

					// pCur = the current vertex;
					Vertex pCur = tVerts[i];

					// pNext = the next vertex in the list
					Vertex pNext;
					if (i == tVerts.size() - 1)
					{
						pNext = tVerts[0];
					}
					else
					{
						pNext = tVerts[i + 1];
					}

					// Check to see if there are only 3 verts left
					// if so this is the last triangle
					if (tVerts.size() == 3)
					{
						// Create a triangle from pCur, pPrev, pNext
						for (int j = 0; j < int(tVerts.size()); j++)
						{
							if (iVerts[j].Position == pCur.Position)
								oIndices.push_back(j);
							if (iVerts[j].Position == pPrev.Position)
								oIndices.push_back(j);
							if (iVerts[j].Position == pNext.Position)
								oIndices.push_back(j);
						}

						tVerts.clear();
						break;
					}
					if (tVerts.size() == 4)
					{
						// Create a triangle from pCur, pPrev, pNext
						for (int j = 0; j < int(iVerts.size()); j++)
						{
							if (iVerts[j].Position == pCur.Position)
								oIndices.push_back(j);
							if (iVerts[j].Position == pPrev.Position)
								oIndices.push_back(j);
							if (iVerts[j].Position == pNext.Position)
								oIndices.push_back(j);
						}

						Vector3 tempVec;
						for (int j = 0; j < int(tVerts.size()); j++)
						{
							if (tVerts[j].Position != pCur.Position
								&& tVerts[j].Position != pPrev.Position
								&& tVerts[j].Position != pNext.Position)
							{
								tempVec = tVerts[j].Position;
								break;
							}
						}

						// Create a triangle from pCur, pPrev, pNext
						for (int j = 0; j < int(iVerts.size()); j++)
						{
							if (iVerts[j].Position == pPrev.Position)
								oIndices.push_back(j);
							if (iVerts[j].Position == pNext.Position)
								oIndices.push_back(j);
							if (iVerts[j].Position == tempVec)
								oIndices.push_back(j);
						}

						tVerts.clear();
						break;
					}

					// If Vertex is not an interior vertex
					float angle = AngleBetweenV3(pPrev.Position - pCur.Position, pNext.Position - pCur.Position) * (180 / 3.14159265359);
					if (angle <= 0 && angle >= 180)
						continue;

					// If any vertices are within this triangle
					bool inTri = false;
					for (int j = 0; j < int(iVerts.size()); j++)
					{
						if (inTriangle(iVerts[j].Position, pPrev.Position, pCur.Position, pNext.Position)
							&& iVerts[j].Position != pPrev.Position
							&& iVerts[j].Position != pCur.Position
							&& iVerts[j].Position != pNext.Position)
						{
							inTri = true;
							break;
						}
					}
					if (inTri)
						continue;

					// Create a triangle from pCur, pPrev, pNext
					for (int j = 0; j < int(iVerts.size()); j++)
					{
						if (iVerts[j].Position == pCur.Position)
							oIndices.push_back(j);
						if (iVerts[j].Position == pPrev.Position)
							oIndices.push_back(j);
						if (iVerts[j].Position == pNext.Position)
							oIndices.push_back(j);
					}

					// Delete pCur from the list
					for (int j = 0; j < int(tVerts.size()); j++)
					{
						if (tVerts[j].Position == pCur.Position)
						{
							tVerts.erase(tVerts.begin() + j);
							break;
						}
					}

					// reset i to the start
					// -1 since loop will add 1 to it
					i = -1;
				}

				// if no triangles were created
				if (oIndices.size() == 0)
					break;

				// if no more vertices
				if (tVerts.size() == 0)
					break;
			}
		}
	};
}