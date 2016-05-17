#include "DirectIntegrator.h"
#include "tinyxml2.h"
#include "BRDF/BSDF.h"
#include "Primitive/IntersectRecord.h"
#include "Math/Ray.h"
#include "Math/Vector3.h"
#include "Math/Point3.h"
#include "Math/Normal.h"
#include "Core/Scene.h"
#include "Utilities/RNG.h"
#include "Light/Light.h"
#include "Integrator/IntegratorPCH.h"

Spectrum UniformSampleOneLight( const Scene* scene , const Renderer* renderer , Accelerator* pAccelerator , BSDF* bsdf , const Point3f& point , const Vector3f& wo , const Normal& n )
{
	// ���ѡ��һ����Դ
	int LightCount = ( int )( scene->GetLights().size() );

	if( LightCount == 0 )
	{
		return Spectrum( 0.0 );
	}

	int LightIndex = std::min( ( int )std::floor( RNG::Get().GetDouble() * LightCount ) , LightCount - 1 );

	Light* light = scene->GetLight( LightIndex );

	return EstimateDirect( scene , renderer , pAccelerator , light , bsdf , point , wo , n , BxDFType( ALL_TYPE & ~SPECULAR ) );
}

Spectrum EstimateDirect( const Scene* scene , const Renderer* renderer , Accelerator* pAccelerator , Light* light , BSDF* bsdf , const Point3f& point , const Vector3f& wo , const Normal& n , BxDFType flags )
{
	// http://lonelywaiting.github.io/MIS/

	Spectrum Ld( 0.0 );
	Vector3f wi;
	// -----------------------------------------������Դ-----------------------------------------------------------
	VisibilityTester visibility;
	double LightPdf;
	Spectrum Li = light->Sample_L( point , &wi , LightSample( RNG::Get().GetDouble() , RNG::Get().GetDouble() ) , &LightPdf , &visibility );

	if( LightPdf > 0.0 && !Li.IsBlack() && visibility.Unoccluded( scene , pAccelerator ) )
	{
		// ����BSDF��ֵ
		Spectrum f = bsdf->f( wo , wi , n , flags );

		// �����ڸ÷���Զ��ԣ�BSDF�Ƿ���ֵ�����໥�ɼ�
		if( !f.IsBlack() )
		{
			if( light->IsDelta() )		// ����Delta Light���ԣ�ֻ����Light����������BSDF
			{
				Ld += f * AbsDot( wi , n ) * Li / LightPdf;
			}
			else
			{
				// ����Mulity Importance Sampling����Ȩ��
				// ƽ��BRDF��Light֮���PDF
				double BsdfPdf = bsdf->PDF( wo , wi , n ,  flags );
				double weight = PowerHeuristic( 1 , LightPdf , 1 , BsdfPdf );
				Ld += f * AbsDot( wi , n ) * Li * weight / LightPdf;
			}
		}
	}

	// ----------------------------------����BSDF------------------------------------------
	if( !light->IsDelta() )
	{
		// ֻ�е�lightΪ��Delta distributionʱ���Ż����BSDF
		double BsdfPdf = 0.0;
		bool bNoOccur;
		BxDFType BrdfType;
		Spectrum f = bsdf->Sample_f( wo , n , &wi , Point2f( RNG::Get().GetDouble() , RNG::Get().GetDouble() ) , &BsdfPdf , flags , bNoOccur , &BrdfType );
		if( !f.IsBlack() && BsdfPdf > 0.0 )
		{
			double weight = 1.0;

			if( !( BrdfType & SPECULAR ) )
			{
				// �Ǿ��棬��Ҫ�������light��pdf���Ӷ�����Ȩֵ
				LightPdf = light->PDF( point , wi );
				if( LightPdf == 0.0 )
				{
					// ��Դ���Ÿ÷���û���κι���
					return Ld;
				}

				weight = PowerHeuristic( 1 , BsdfPdf , 1 , LightPdf );
			}

			Spectrum Li( 0.0 );
			IntersectRecord record;
			Ray r( point , wi );
			if( scene->Intersect( r , &record ) )
			{
				if( record.primitivePtr->GetAreaLight() == light )
				{
					Li = record.Le( -wi );
				}

				// ��������ͼԪ��ס��
			}
			else
			{
				Li = Spectrum( 0.0 );
			}

			if( !Li.IsBlack() )
			{
				Ld += f * Li * AbsDot( wi , n ) * weight / BsdfPdf;
			}
		}
	}

	return Ld;
}

void DirectIntegrator::Deserialization( tinyxml2::XMLElement * IntegratorRootElement )
{
	IntegratorRootElement->FirstChildElement( "MaxDepth" )->QueryIntText( &mMaxDepth );
}

void DirectIntegrator::Serialization( tinyxml2::XMLDocument & xmlDoc , tinyxml2::XMLElement * pRootElement )
{
	pRootElement->SetAttribute( "type" , GetName() );

	{
		tinyxml2::XMLElement* pMaxDepthElement = xmlDoc.NewElement( "MaxDepth" );

		pMaxDepthElement->SetText( mMaxDepth );

		pRootElement->InsertEndChild( pMaxDepthElement );
	}
}

Spectrum DirectIntegrator::Li( const Scene* scene , const Renderer* renderer , IntersectRecord* record , Ray* ray , Accelerator* pAccelerator ) const
{
	Spectrum L( 0.0 );

	BSDF* bsdf = record->GetBSDF();

	Vector3f wo = -ray->Direction;
	Point3f HitPoint = record->HitPoint;
	Normal nomral = record->normal;

	// �Է���
	L += record->Le( wo );

	L += UniformSampleOneLight( scene , renderer , pAccelerator , bsdf , record->HitPoint , wo , record->normal );

	L *= record->SurfaceColor;

	if( ray->depth < mMaxDepth )
	{
		Spectrum Li( 0.0 );

		bool bNoReflectOccur = false;

		// ���ٷ������
		Li += SpecularReflect( *ray , scene , renderer , record , pAccelerator , bsdf , bNoReflectOccur );

		if( bNoReflectOccur )
		{
			// �����������
			Li += SpecularTransmit( *ray , scene , renderer , record , pAccelerator , bsdf , bNoReflectOccur );
		}

		L = L + Li;
	}

	SAFE_DELETE( bsdf );

	return L;

}

