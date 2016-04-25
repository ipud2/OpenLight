#include "PCH.h"
#include "BRDF/BxDF.h"
#include "Primitive/IntersectRecord.h"
#include "Math/Ray.h"
#include "BRDF/BSDF.h"
#include "Integrator/IntegratorPCH.h"
#include "WhittedIntegrator.h"

Spectrum WhittedIntegrator::Li( const Scene* scene , const Renderer* renderer , IntersectRecord* record , Ray* ray , Accelerator* pAccelerator ) const
{
	Spectrum L( 0 );

	// ����Hit Point����BRDF
	BSDF* bsdf = record->GetBSDF();

	// ��ɫ��λ�ã���ɫ�㷨��
	const Point3f& p = record->HitPoint;

	const Normal& normal = record->normal;

	// ���߷���ķ�����Ϊ���䷽��
	Vector3f wo = -1.0f * ray->Direction;

	// �Է���
	L += record->Emmisive;

	// ������ �� TO DO...

	// Ligtt , TO DO...

	if( ray->depth < mMaxDepth )
	{
		// ���ٷ������
		L += SpecularReflect( *ray , scene , renderer , record , pAccelerator , bsdf );

		// �����������
		L += SpecularTransmit( *ray , scene , renderer , record , pAccelerator , bsdf );
	}

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