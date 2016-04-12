#include "PCH.h"
#include "BRDF/BxDF.h"
#include "Primitive/IntersectRecord.h"
#include "Math/Normal.h"
#include "Math/Ray.h"
#include "Light/Light.h"
#include "Core/Scene.h"
#include "Light/VisibilityTester.h"
#include "Math/UtilitiesFunction.h"
#include "Renderer/Renderer.h"
#include "WhittedIntegrator.h"

Spectrum WhittedIntegrator::Li( const Scene* scene , const Renderer* renderer , IntersectRecord* record , Ray* ray ) const
{
	Spectrum L( 0.0 );

	// ����Hit Point����BRDF
	BxDF* brdf = record->GetBxDF();

	// ��ɫ��λ�ã���ɫ�㷨��
	const Point3f& p = record->HitPoint;

	const Normal& normal = record->normal;

	// ���߷���ķ�����Ϊ���䷽��
	Vector3f wo = -1.0f * ray->Direction;

	// ���ÿ����Դ�Ĺ���
	for( uint32_t i = 0; i < scene->GetLights().size(); i++ )
	{
		Vector3f wi;

		float pdf;

		VisibilityTester visibility;

		Spectrum Li = ( scene->GetLights() )[i]->Sample_L( p , &wi , &pdf );

		if( Li.IsBlack() || pdf == 0.0f )
		{
			continue;
		}

		Spectrum f = brdf->f( wo , wi );

		if( !f.IsBlack() && visibility.Unoccluded( scene ) )
		{
			L += f * Li * AbsDot( wi , normal ) / pdf;
		}
	}

	if( ray->depth + 1 < MaxDepth )
	{
		// ���� �� ͸��
		Ray reflectRay = Reflect( *ray , normal , record->HitPoint , 1e-3f );

		Spectrum Temp( 1.0f );
		L += renderer->Li( scene , &reflectRay , record , &Temp );
	}

	return L;
}

void WhittedIntegrator::SetMaxRecusiveDepth( int maxdepth )
{
	MaxDepth = maxdepth;
}