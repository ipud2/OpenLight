#pragma once

#include "Light.h"
#include "Math/Point3.h"

namespace tinyxml2
{
	class XMLElement;
}

class PointLight : public Light
{
	DECLARE_DYNAMIC_CREATE_DERIVED( PointLight , Light )

public:
	PointLight();

	PointLight( const Transform& LightToWorld , const Spectrum & intensity );

	Spectrum Sample_L( const Point3f& p , Vector3f* wi , LightSample& _lightSample , double* pdf , VisibilityTester* pVisibility ) const;

	Spectrum Power( const Scene* scene ) const;
	
	Spectrum Sample_L( const Scene* scene , LightSample& _lightSample , Ray* ray , Normal* NormalShading , double* pdf ) const;

	double PDF( const Point3f& p , const Vector3f& wi ) const;

public:
	void Deserialization( tinyxml2::XMLElement* LightRootElement );

private:
	Point3f LightPosWorld;
	Spectrum intensity;
};