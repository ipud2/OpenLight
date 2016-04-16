#include "PCH.h"
#include "Math/Bound3.h"
#include "Math/Ray.h"
#include "Primitive/IntersectRecord.h"
#include "ModelParser.h"
#include "TriangleMesh.h"

TriangleMesh::TriangleMesh()
{

}

TriangleMesh::TriangleMesh( const Transform* ObjectToWorld , const Transform* WorldToObject , Point3f* _points , Normal* _normals , int _TriangleCount )
{

}

TriangleMesh::~TriangleMesh()
{

}

Bound3f TriangleMesh::ObjectBound() const
{
	Bound3f bbox;

	for( int i = 0; i < VertexNum; i++ )
	{
		bbox.ExpendToInclude( points[i] );
	}

	return bbox;
}

bool TriangleMesh::Intersect( Ray& ray , IntersectRecord* record ) const
{
	// ��World Space�任��Object Space
	Ray r = ( *WorldToObject )( ray );

	int bHitIndex = -1;

	for( int i = 0; i < TriangleCount; i++ )
	{
		if( triangles[i].Intersect( r , points , record ) )
		{
			bHitIndex = i;
		}
	}

	if( bHitIndex != -1 )
	{
		ray.MaxT = r.MaxT;
		record->ObjectToWorld = *ObjectToWorld;
		record->WorldToObject = *WorldToObject;
		record->normal = normals[3 * bHitIndex];
		return true;
	}

	return false;
}

bool TriangleMesh::IntersectP( const Ray& ray ) const
{
	Ray r = ( *WorldToObject )( ray );

	bool bHit = false;

	for( int i = 0; i < TriangleCount; i++ )
	{
		if( triangles[i].IntersectP( r , points ) )
		{
			return true;
		}
	}

	return false;
}

void TriangleMesh::ParseShape( XMLElement* ShapeRootElement )
{
	const char* filename = ShapeRootElement->FirstChildElement( "filename" )->GetText();

	XMLElement* ShapeTransformElement = ShapeRootElement->FirstChildElement( "transform" );

	double x , y , z;

	ShapeTransformElement->FirstChildElement( "position" )->FirstChildElement( "x" )->QueryDoubleText( &x );
	ShapeTransformElement->FirstChildElement( "position" )->FirstChildElement( "y" )->QueryDoubleText( &y );
	ShapeTransformElement->FirstChildElement( "position" )->FirstChildElement( "z" )->QueryDoubleText( &z );

	*ObjectToWorld = Translate( Vector3f( x , y , z ) );
	*WorldToObject = Inverse( *ObjectToWorld );

	double r , g , b;
	XMLElement* ShapeEmmisiveElement = ShapeRootElement->FirstChildElement( "emmisive" );
	ShapeEmmisiveElement->FirstChildElement( "r" )->QueryDoubleText( &r );
	ShapeEmmisiveElement->FirstChildElement( "g" )->QueryDoubleText( &g );
	ShapeEmmisiveElement->FirstChildElement( "b" )->QueryDoubleText( &b );

	emmisive = Spectrum::FromRGB( r , g , b );

	// ����OBJģ��
	ModelParser( filename , points , normals , triangles , VertexNum , TriangleCount );
}