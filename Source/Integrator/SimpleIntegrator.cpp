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
#include "Sampler/Sampling.h"
#include "Accelerator/Grid.h"
#include "SimpleIntegrator.h"

IMPLEMENT_DYNAMIC_CREATE_DERIVED( SimpleIntegrator , SurfaceIntegrator )

Spectrum SimpleIntegrator::Li( const Scene* scene , const Renderer* renderer , IntersectRecord* record , Ray* ray , Accelerator* pAccelerator ) const
{
	Spectrum L( 0.0 );

	if (ray->depth < MaxDepth)
	{
		// ����Hit Point����BRDF
		BSDF* brdf = record->GetBSDF();

		// ��ɫ��λ�ã���ɫ�㷨��
		const Point3f& p = record->HitPoint;

		const Normal& normal = record->normal;

		// ���߷���ķ�����Ϊ���䷽��
		Vector3f wo = -1.0f * ray->Direction;

		for (int i = 0; i < SamplePathNumber; i++)
		{
			double u0 = (double)rand() / (double)RAND_MAX;
			double u1 = (double)rand() / (double)RAND_MAX;

			// ��������
			Vector3f& wi = CosineSampleHemisphere(Point2f(u0, u1));

			if (Dot(normal, wi) < 0)
			{
				wi *= -1;
			}

			// ���ŷ��߷����ƫ����
			Vector3f bias = Vector3f(normal.x * EPSILON , normal.y * EPSILON , normal.z * EPSILON );

			// ���������ŷ��߷���ƫ��
			Ray r(record->HitPoint + bias , wi, *ray, 1e-3f , Infinity);

			// �������䷽���볡��ͼԪ���ڽ���
			if( pAccelerator->Intersect( r , scene , record ) )
			{
				// pdfǿ��ʹ��INV_PI
				L += Li( scene , renderer , record , &r , pAccelerator ) * brdf->f( wo , wi , record->normal , BxDFType( DIFFUSE ) ) *AbsDot( normal , wi ) / INV_PI;
			}
		}

		L /= SamplePathNumber;
	}

	return L;
}

void SimpleIntegrator::SetMaxRecusiveDepth( int maxdepth )
{
	MaxDepth = maxdepth;
}

void SimpleIntegrator::Deserialization(XMLElement* IntegratorRootElement)
{
	IntegratorRootElement->FirstChildElement("MaxDepth")->QueryIntText( &MaxDepth );

	IntegratorRootElement->FirstChildElement( "SamplePathNumber" )->QueryIntText( &SamplePathNumber );
}