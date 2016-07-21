#pragma once

#include "Math/MathHelper.h"
#include "Shape.h"

class TriangleMesh;
namespace tinyxml2
{
	class XMLElement;
}

class Triangle : public Shape
{
	DECLARE_DYNAMIC_CREATE_DERIVED( Triangle , Shape )

public:
	Triangle();

	~Triangle();

public:
	void Set( int _index0 , int _index1 , int _index2 );

	void SetTriangleMesh( TriangleMesh* _pMesh );

	bool Intersect( Rayf& ray , IntersectRecord* record ) const;

	Point3f Sample( const Point3f& p , LightSample& lightSample , Vector3f& normalSample );

public:
	float Area() const;

public:
	void Deserialization( tinyxml2::XMLElement* RootElement );

private:
	int index0 , index1 , index2;
	TriangleMesh* pMesh;
};