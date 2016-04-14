#include "PCH.h"
#include "Math/Ray.h"
#include "Math/Transform.h"
#include "Primitive/IntersectRecord.h"
#include "Sampler/Sampling.h"
#include "Sphere.h"

Sphere::Sphere()
{
	m_Radius = 0;
}

Sphere::Sphere( Point3f Center , double radius )
	: m_Radius( radius )
	, m_Center( Center )
{
	*ObjectToWorld = Translate( Vector3f( Center ) );
	
	*WorldToObject = Inverse( *ObjectToWorld );
}

Sphere::~Sphere()
{
}

Bound3f Sphere::ObjectBound() const
{
	return Bound3f( Point3f( -m_Radius , -m_Radius , -m_Radius ) , Point3f( m_Radius , m_Radius , m_Radius ) );
}

bool Sphere::Intersect( Ray& r , IntersectRecord* record ) const
{
	// �����ߴ�����ռ�任���ֲ��ռ�
	Ray ray = ( *WorldToObject )( r );

	// ������η��̵Ĳ���
	double A = ray.Direction.x * ray.Direction.x + ray.Direction.y * ray.Direction.y + ray.Direction.z * ray.Direction.z;
	double B = 2 * ray.Origin.x * ray.Direction.x + 2 * ray.Origin.y * ray.Direction.y + 2 * ray.Origin.z * ray.Direction.z;
	double C = ray.Origin.x * ray.Origin.x + ray.Origin.y * ray.Origin.y + ray.Origin.z * ray.Origin.z - m_Radius * m_Radius;

	double t0 , t1;
	if( !Quadtratic( A , B , C , &t0 , &t1 ) )
	{
		// û��ʵ����
		return false;
	}

	// �ж��ཻ�㣬λ�ڹ��ߵĺ���λ��
	if( t0 > ray.MaxT || t1 < ray.MinT )
	{
		return false;
	}

	double t = t0;
	if( t0 < ray.MinT )
	{
		t = t1;
		if( t > ray.MaxT )
		{
			return false;
		}
	}

	/*Vector3f v = r( t ) - m_Center;

	if( v.Length() < m_Radius )
	{
		double length = v.Length();

		Point3f v1 = r( t );

		return false;
	}*/
	

	r.MaxT = t;
	record->HitT = t;
	record->ObjectToWorld = *ObjectToWorld;
	record->WorldToObject = *WorldToObject;
	record->normal = Normal( Normalize( r( t ) - m_Center ) );

	return true;
}

bool Sphere::IntersectP( const Ray& r ) const
{
	Ray ray = ( *WorldToObject )( r );

	// ������η��̵Ĳ���
	double A = ray.Direction.x * ray.Direction.x + ray.Direction.y * ray.Direction.y + ray.Direction.z * ray.Direction.z;
	double B = 2 * ray.Origin.x * ray.Direction.x + 2 * ray.Origin.y * ray.Direction.y + 2 * ray.Origin.z * ray.Direction.z;
	double C = ray.Origin.x * ray.Origin.x + ray.Origin.y * ray.Origin.y + ray.Origin.z * ray.Origin.z - m_Radius * m_Radius;

	double t0 , t1;
	if( !Quadtratic( A , B , C , &t0 , &t1 ) )
	{
		// û��ʵ����
		return false;
	}

	// �ж��ཻ�㣬λ�ڹ��ߵĺ���λ��
	if( t0 > ray.MaxT || t1 < ray.MinT )
	{
		return false;
	}

	double t = t0;
	if( t0 < ray.MinT )
	{
		t = t1;
		if( t > ray.MaxT )
		{
			return false;
		}
	}

	return true;
}

void Sphere::ParseShape( XMLElement* ShapeRootElement )
{
	XMLElement* PrimitivePosiitonElement = ShapeRootElement->FirstChildElement( "transform" )->FirstChildElement( "position" );

	PrimitivePosiitonElement->FirstChildElement( "x" )->QueryDoubleText( &( m_Center.x ) );
	PrimitivePosiitonElement->FirstChildElement( "y" )->QueryDoubleText( &( m_Center.y ) );
	PrimitivePosiitonElement->FirstChildElement( "z" )->QueryDoubleText( &( m_Center.z ) );

	ShapeRootElement->FirstChildElement( "radius" )->QueryDoubleText( &m_Radius );

	double r, g, b;
	ShapeRootElement->FirstChildElement("emmisive")->FirstChildElement("r")->QueryDoubleText(&r);
	ShapeRootElement->FirstChildElement("emmisive")->FirstChildElement("g")->QueryDoubleText(&g);
	ShapeRootElement->FirstChildElement("emmisive")->FirstChildElement("b")->QueryDoubleText(&b);

	emmisive = Spectrum::FromRGB(r, g, b);

	*ObjectToWorld = Translate( Vector3f( m_Center ) );
	*WorldToObject = Inverse( *ObjectToWorld );
}