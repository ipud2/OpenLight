#include "PCH.h"
#include "BRDF/BxDF.h"
#include "Primitive/IntersectRecord.h"
#include "Math/Ray.h"
#include "BRDF/BSDF.h"
#include "Integrator/IntegratorPCH.h"
#include "Core/Scene.h"
#include "Light/Light.h"
#include "WhittedIntegrator.h"
#include "BRDF/BxDFType.h"

Spectrum WhittedIntegrator::Li( const Scene* scene , const Renderer* renderer , IntersectRecord* record , Ray* ray , Accelerator* pAccelerator ) const
{
	Spectrum L( 0.0 );

	// 计算Hit Point处的BRDF
	BSDF* bsdf = record->GetBSDF();

	// 自发光
	L += record->Emission;

	Point3f HitPoint = record->HitPoint;
	Normal n = Normalize( record->normal );

	Vector3f wo = -ray->Direction;

	for( int i = 0; i < scene->GetLights().size(); i++ )
	{
		Vector3f wi;
		double pdf;
		VisibilityTester* pVisibility = new VisibilityTester;

		Spectrum Li = scene->GetLight( i )->Sample_L( HitPoint , &wi , &pdf , pVisibility );

		if( Li.IsBlack() || pdf == 0.0f )
		{
			continue;
		}

		Spectrum f = bsdf->f( wo , wi , n , BxDFType( DIFFUSE | SPECULAR | REFLECTION | TRANSMISSION ) );

		if( !f.IsBlack() && pVisibility->Unoccluded( scene , pAccelerator ) )
		{
			L += f * Li * AbsDot( wi , n ) / pdf * record->SurfaceColor;
		}

		SAFE_DELETE( pVisibility );
	}

	if( ray->depth < mMaxDepth )
	{
		Spectrum Li( 0.0 );

		// 跟踪反射光线
		Li += SpecularReflect( *ray , scene , renderer , record , pAccelerator , bsdf );

		// 跟踪折射光线
		Li += SpecularTransmit( *ray , scene , renderer , record , pAccelerator , bsdf );

		L = L + Li * record->SurfaceColor;
	}

	SAFE_DELETE( bsdf );

	return L;
}

void WhittedIntegrator::SetMaxRecusiveDepth( int maxdepth )
{
	mMaxDepth = maxdepth;
}

void WhittedIntegrator::Deserialization( XMLElement* IntegratorRootElement )
{
	IntegratorRootElement->FirstChildElement( "MaxDepth" )->QueryIntText( &mMaxDepth );
}