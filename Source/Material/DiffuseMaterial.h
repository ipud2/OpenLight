#pragma once

#include "Material/Material.h"

namespace tinyxml2
{
	class XMLElement;
}

class DiffuseMaterial : public Material
{
	DECLARE_DYNAMIC_CREATE_DERIVED( DiffuseMaterial , Material )

public:
	DiffuseMaterial();

	BSDF* GetBSDF( const Point3f& point , const Normal& normal ) const;

	DiffuseMaterial( Spectrum R );

public:
	void Deserialization( tinyxml2::XMLElement* RootElement );

private:
	mutable Spectrum R;
};