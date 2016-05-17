#include "Utilities/PCH.h"
#include "Spectrum/Spectrum.h"
#include "Math/Ray.h"
#include "Renderer/Renderer.h"
#include "Primitive/IntersectRecord.h"
#include "Accelerator/Accelerator.h"
#include "BRDF/BSDF.h"
#include "BRDF/BxDF.h"
#include "IntegratorPCH.h"

Spectrum SpecularReflect( const Ray& ray , const Scene* scene , const Renderer* renderer , IntersectRecord* record , Accelerator* pAccelerator , BSDF* pBSDF , bool& bNoOccur )
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

	Spectrum f = pBSDF->Sample_f( wo , normal , &wi , SamplePoint , &pdf , BxDFType( REFLECTION | SPECULAR ) , bNoOccur );

	Spectrum L = 0.0;

	if( pdf > 0.0 && !f.IsBlack() && AbsDot( wi , normal ) != 0.0 )
	{
		// ���ŷ��߷����ƫ��
		Vector3f bias = Vector3f( wi.x * 1e-2f , wi.y * 1e-2f , wi.z * 1e-2f );

		// ���������ŷ��߷���ƫ��
		Ray r( record->HitPoint + bias , wi , ray , 1e-4f , Infinity );

		Spectrum Li = renderer->Li( scene , &r , record );

		L = f * Li * AbsDot( wi , normal ) / pdf;

		return L;
	}

	return Spectrum( 0.0 );
}

Spectrum SpecularTransmit( const Ray& ray , const Scene* scene , const Renderer* renderer , IntersectRecord* record , Accelerator* pAccelerator , BSDF* pBSDF , bool& bNoOccur )
{
	// ��ɫ��λ��
	const Point3f& p = record->HitPoint;

	// ��ɫ�㷨��
	const Normal& normal = Normalize( record->normal );

	double pdf;

	Vector3f wi;

	Point2f SamplePoint( ( double )rand() / ( double )RAND_MAX , ( double )rand() / ( double )RAND_MAX );

	Spectrum f = pBSDF->Sample_f( ray.Direction , normal , &wi , SamplePoint , &pdf , BxDFType( TRANSMISSION | SPECULAR ) , bNoOccur );

	Spectrum L = 0.0;

	if( pdf > 0.0 && !f.IsBlack() && AbsDot( wi , normal ) != 0.0 )
	{
		// ���ŷ��߷����ƫ����
		Vector3f bias = Vector3f( wi.x * 0.01 , wi.y * 0.01 , wi.z * 0.01 );

		// ���������ŷ��߷���ƫ��
		Ray r( record->HitPoint + bias , wi , ray , 1e-3 );

		Spectrum Li = renderer->Li( scene , &r , record );

		L = f * Li * AbsDot( wi , normal ) / pdf;
	}

	return L;
}

double PowerHeuristic( int nf , double fPdf , int ng , double gPdf )
{
	return ( nf * fPdf * nf * fPdf ) / ( nf * fPdf * nf * fPdf + ng * ng * gPdf * gPdf );
}