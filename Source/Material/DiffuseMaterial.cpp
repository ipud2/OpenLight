#include "PCH.h"
#include "DiffuseMaterial.h"
#include "BRDF/Lambertian.h"

DiffuseMaterial::DiffuseMaterial(Spectrum Reflection)
	:Material()
{
	brdf = new Lambertian( Reflection );
}

BxDF* DiffuseMaterial::GetBxDF(const Point3f& point, const Normal& normal) const
{
	return brdf;
}