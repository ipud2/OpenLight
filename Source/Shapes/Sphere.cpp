#include "PCH.h"
#include "Math/Ray.h"
#include "Math/Transform.h"
#include "Primitive/IntersectRecord.h"
#include "Sampler/Sampling.h"
#include "Light/Light.h"
#include "Sphere.h"

IMPLEMENT_DYNAMIC_CREATE_DERIVED( Sphere , Shape )

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

	BBoxLocal = Bound3f( Point3f( -m_Radius , -m_Radius , -m_Radius ) , Point3f( m_Radius , m_Radius , m_Radius ) );

	BBoxWorld = ( *ObjectToWorld )( BBoxLocal );
}

Sphere::~Sphere()
{
}

bool Sphere::Intersect( Ray& r , IntersectRecord* record ) const
{
	if( BBoxWorld.IntersectP( r ) )
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

		r.MaxT                = t;
		record->primitivePtr  = pPrimitive;
		record->HitT          = t;
		record->ObjectToWorld = *ObjectToWorld;
		record->WorldToObject = *WorldToObject;
		record->normal        = Normal( Normalize( r( t ) - m_Center ) );
		record->SurfaceColor  = SurfaceColor;
		record->HitPoint      = r( t );
		return true;
	}
	
	return false;
}

void Sphere::Deserialization( XMLElement* ShapeRootElement )
{
	XMLElement* PrimitivePosiitonElement = ShapeRootElement->FirstChildElement( "transform" )->FirstChildElement( "position" );

	PrimitivePosiitonElement->FirstChildElement( "x" )->QueryDoubleText( &( m_Center.x ) );
	PrimitivePosiitonElement->FirstChildElement( "y" )->QueryDoubleText( &( m_Center.y ) );
	PrimitivePosiitonElement->FirstChildElement( "z" )->QueryDoubleText( &( m_Center.z ) );

	ShapeRootElement->FirstChildElement( "radius" )->QueryDoubleText( &m_Radius );

	double r, g, b;

	// Read Surface Color
	ShapeRootElement->FirstChildElement( "SurfaceColor" )->FirstChildElement( "r" )->QueryDoubleText( &r );
	ShapeRootElement->FirstChildElement( "SurfaceColor" )->FirstChildElement( "g" )->QueryDoubleText( &g );
	ShapeRootElement->FirstChildElement( "SurfaceColor" )->FirstChildElement( "b" )->QueryDoubleText( &b );
	
	SurfaceColor = Spectrum::FromRGB( r , g , b );

	*ObjectToWorld = Translate( Vector3f( m_Center ) );
	*WorldToObject = Inverse( *ObjectToWorld );

	BBoxLocal = Bound3f( Point3f( -m_Radius , -m_Radius , -m_Radius ) , Point3f( m_Radius , m_Radius , m_Radius ) );

	BBoxWorld = ( *ObjectToWorld )( BBoxLocal );
}

double Sphere::Area() const
{
	return 4.0 * PI * m_Radius * m_Radius;
}

double Sphere::PDF( const Point3f& p , const Vector3f& wi ) const
{
	// Test whether inside sphere
	if( ( p - m_Center ).LengthSq() - m_Radius * m_Radius < 1e4f )
	{
		return Shape::PDF( p , wi );
	}

	double SinThetaMax2 = m_Radius * m_Radius / ( p - m_Center ).LengthSq();
	double CosThetaMax = sqrtf( MAX( 0.0 , 1.0 - SinThetaMax2 ) );

	return UniformConePDF( CosThetaMax );
}

Point3f Sphere::Sample( const Point3f& p , LightSample& lightSample , Normal& SampleNormal )
{
	Vector3f dirZ = Normalize( m_Center - p );

	// �������ϲ���һ����
	if( ( p - m_Center ).LengthSq() - m_Radius * m_Radius < 1e4f )
	{
		// ʹ��Ĭ�ϵĲ���
		Vector3f SampleDir = UniformSampleHemisphere( Point2f( lightSample.value[0] , lightSample.value[1] ) );

		if( Dot( SampleDir , dirZ ) < 0.0 )
		{
			SampleDir *= -1.0;
		}

		Point3f SamplePoint = m_Center + Normalize( dirZ ) * m_Radius;

		// Compute Normal Dir
		SampleNormal = Normalize( Normal( SamplePoint - m_Center ) );
		
		return SamplePoint;
	}

	
	Vector3f dirX , dirY;
	CoordinateSystem( dirZ , &dirX , &dirY );

	// ���Ȳ���cone
	double sinThetaMax2 = m_Radius * m_Radius / ( p - m_Center ).LengthSq();
	double cosThetaMax = sqrtf( MAX( 0.0 , 1.0 - sinThetaMax2 ) );

	Ray r( p , UniformSampleCone( lightSample.value[0] , lightSample.value[1] , cosThetaMax , dirX , dirY , dirZ ) );

	// Test whether intersect
	double t;
	IntersectRecord record;
	Point3f SamplePoint;
	if( !Intersect( r , &record ) )
	{
		// �ض������ߵ����ж�Ϊ�޽���
		t = Dot( m_Center - p , r.Direction );
		SamplePoint = r( t );
	}
	else
	{
		SamplePoint = record.HitPoint;
	}
	
	SampleNormal = Normalize( SamplePoint - m_Center );

	return SamplePoint;
}