#pragma once

#include <string>

class Point3f;
class Normal;
class Point2f;
class Triangle;

void ModelParse( const std::string& filename , Point3f*& points , Normal*& normals , Vector2f*& uvs , Triangle*& traingles , int& VertexCount , int& FaceCount );