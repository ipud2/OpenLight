#include "PCH.h"
#include "Math/Vector3.h"
#include "Sampler/Sampling.h"
#include "Math/Ray.h"
#include "Math/Normal.h"
#include "PointLight.h"

IMPLEMENT_DYNAMIC_CREATE_DERIVED( PointLight , Light )

PointLight::PointLight()
{

}

PointLight::PointLight( const Transform& LightToWorld , const Spectrum & _intensity )
	:Light( LightToWorld )
{
	LightPosWorld = LightToWorld( Point3f( 0.0f , 0.0f , 0.0f ) );

	intensity = _intensity;
}

Spectrum PointLight::Sample_L( const Scene* scene , LightSample& lightSample , Ray* ray , Normal* NormalShading , double* pdf ) const
{
	*ray = Ray( LightPosWorld , UniformSampleSphere( lightSample.value[0] , lightSample.value[1] ) , 0.0f , Infinity );

	*NormalShading = Normal( ray->Direction.x , ray->Direction.y , ray->Direction.z );

	*pdf = UniformSpherePDF();

	return intensity;
}

Spectrum PointLight::Sample_L( const Point3f& p , Vector3f* wi , double* pdf , VisibilityTester* pVisibility ) const
{
	// �����������
	*wi = Normalize( LightPosWorld - p );

	*pdf = 1.0f;
	
	// �����߶�
	pVisibility->SetSegment( p , EPSILON , LightPosWorld , 0 );

	// ������p�㴦��ǿ��
	return intensity / ( LightPosWorld - p ).Length();
}

Spectrum PointLight::Power( const Scene* scene ) const
{
	return 4.0f * PI * intensity;
}

double PointLight::PDF( const Point3f& p , const Vector3f& wi ) const
{
	return 0;
}

void PointLight::Deserialization( XMLElement* LightRootElement )
{
	XMLElement* LightPositionRootElement = LightRootElement->FirstChildElement( "transform" )->FirstChildElement( "position" );
	LightPositionRootElement->FirstChildElement( "x" )->QueryDoubleText( &LightPosWorld.x );
	LightPositionRootElement->FirstChildElement( "y" )->QueryDoubleText( &LightPosWorld.y );
	LightPositionRootElement->FirstChildElement( "z" )->QueryDoubleText( &LightPosWorld.z );

	LightToWorld = Translate( Vector3f( LightPosWorld ) );
	WorldToLight = Inverse( LightToWorld );

	double r , g , b;
	XMLElement* IntensityRootElement = LightRootElement->FirstChildElement( "intensity" );
	IntensityRootElement->FirstChildElement( "r" )->QueryDoubleText( &r );
	IntensityRootElement->FirstChildElement( "g" )->QueryDoubleText( &g );
	IntensityRootElement->FirstChildElement( "b" )->QueryDoubleText( &b );

	intensity = Spectrum::FromRGB( r , g , b );
}