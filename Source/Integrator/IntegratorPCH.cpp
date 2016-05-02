#include "PCH.h"
#include "Spectrum/Spectrum.h"
#include "Math/Ray.h"
#include "Renderer/Renderer.h"
#include "Primitive/IntersectRecord.h"
#include "Accelerator/Accelerator.h"
#include "BRDF/BSDF.h"
#include "BRDF/BxDF.h"
#include "IntegratorPCH.h"

Spectrum SpecularReflect( const Ray& ray , const Scene* scene , const Renderer* renderer , IntersectRecord* record , Accelerator* pAccelerator , BSDF* pBSDF )
{
	// ��ɫ��λ��
	const Point3f& p = record->HitPoint;

	// ��ɫ�㷨��
	const Normal& normal = Normalize( record->normal );

	double pdf;

	// ���߷���ķ�����Ϊ���䷽��
	Vector3f wo = -1.0f * ray.Direction;

	Vector3f wi;

	Point2f SamplePoint( ( double )rand() / ( double )RAND_MAX , ( double )rand() / ( double )RAND_MAX );

	Spectrum f = pBSDF->Sample_f( wo , normal , &wi , SamplePoint , &pdf , BxDFType( REFLECTION | SPECULAR ) );

	Spectrum L = 0.0;

	if( pdf > 0.0 && !f.IsBlack() && AbsDot( wi , normal ) != 0.0 )
	{
		// ���ŷ��߷����ƫ����
		Vector3f bias = Vector3f( normal.x * 1e-6f , normal.y * 1e-6f , normal.z * 1e-6f );

		// ���������ŷ��߷���ƫ��
		Ray r( record->HitPoint + bias , wi , ray , 1e-3f , Infinity );

		Spectrum Li = renderer->Li( scene , &r , record );

		L = f * Li * AbsDot( wi , normal ) / pdf;

		return L;
	}

	return Spectrum( 0.0 );
}

Spectrum SpecularTransmit( const Ray& ray , const Scene* scene , const Renderer* renderer , IntersectRecord* record , Accelerator* pAccelerator , BSDF* pBSDF )
{
	// ��ɫ��λ��
	const Point3f& p = record->HitPoint;

	// ��ɫ�㷨��
	const Normal& normal = record->normal;

	double pdf;

	// ���߷���ķ�����Ϊ���䷽��
	Vector3f wo = -1.0f * ray.Direction;

	Vector3f wi;

	Point2f SamplePoint( ( float )rand() / ( float )RAND_MAX , ( float )rand() / ( float )RAND_MAX );

	Spectrum f = pBSDF->Sample_f( wo , normal , &wi , SamplePoint , &pdf , BxDFType( TRANSMISSION | SPECULAR ) );

	Spectrum L = 0.0;

	if( pdf > 0.0 && !f.IsBlack() && AbsDot( wi , normal ) != 0.0 )
	{
		// ���ŷ��߷����ƫ����
		// Vector3f bias = Vector3f( normal.x * EPSILON , normal.y * EPSILON , normal.z * EPSILON );

		// ���������ŷ��߷���ƫ��
		Ray r( record->HitPoint /*+ bias */, wi , ray , 1e-3f , Infinity );

		Spectrum Li = renderer->Li( scene , &r , record );

		L = f * Li * AbsDot( wi , normal ) / pdf;

		return L;
	}

	return Spectrum( 0.0 );
}