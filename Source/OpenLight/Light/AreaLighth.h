#pragma once

#include "Light.h"

class Primitive;
namespace tinyxml2
{
	class XMLDocument;
	class XMLElement;
}

class AreaLight : public Light
{
	DECLARE_DYNAMIC_CREATE_DERIVED( AreaLight , Light )

public:
	AreaLight();

	AreaLight( const Transform& LightToWorld , const Spectrum& Le );

	Spectrum Sample_L( const Point3f& p , Vector3f* wi , LightSample& _lightSample , float* pdf , VisibilityTester* pVisibility ) const;

	Spectrum Power( const Scene* scene ) const;

	Spectrum Sample_L( const Scene* scene , LightSample& _lightSample , Rayf* ray , Vector3f* NormalShading , float* pdf ) const;

	Spectrum Le( const Point3f& p , const Vector3f& n , const Vector3f& wo ) const;

	float PDF( const Point3f& p , const Vector3f& wi ) const;

	bool IsDelta();

public:
	void SetPrimitive( Primitive* pPrimitive );

public:
	void Deserialization( tinyxml2::XMLElement* LightRootElement );

	void Serialization( tinyxml2::XMLDocument& xmlDoc , tinyxml2::XMLElement* pRootElement );

protected:
	Primitive* m_pPrimitive;	// Associated Primitive
	Spectrum Lemission;
};