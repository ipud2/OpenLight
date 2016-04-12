#include "PCH.h"
#include "Sampler/Sampling.h"
#include "BxDF.h"

BxDF::~BxDF()
{

}

Spectrum BxDF::Sample_f( const Vector3f& wo , Vector3f* wi , const Point2f& samplePoint , float* pdf ) const
{
	// ���ɰ����������
	*wi = CosineSampleHemisphere( samplePoint );

	// ����wi->z����Ϊ��
	// ���Ե�woΪ��ֵʱ
	// ��Ҫ��תwi->z,�Ӷ���֤λ��ͬһ������
	if( wo.z < 0.0f )
	{
		wi->z *= -1.0f;
	}

	// ����÷���Ե�pdf
	*pdf = PDF( *wi , wo );

	return f( wo , *wi );
}

// wi��λ������ľֲ��ռ�
// ��˷���Ϊ(0 , 0 , 1)
// ���cos(theta) = (0 , 0 , 1) * wi = wi.z
float BxDF::PDF( const Vector3f& wi , const Vector3f& wo ) const
{
	return ( wi.z * wo.z > 0.0 ) ? fabs( wi.z ) * INV_PI : 0.0f;
}

Spectrum BxDF::rho( int nSamples , Point2f* Samples1 , Point2f* Samples2 ) const
{
	Spectrum r = 0;

	for( int i = 0; i < nSamples; i++ )
	{
		Vector3f wo , wi;

		// ���ݴ���Ķ�ά������
		// ���ɰ����ڵ������������
		wo = UniformSampleHemisphere( Samples2[i] );

		float PdfOutput = INV_TWO_PI; 
		float PdfInput = 0.0f;

		Spectrum f = Sample_f( wo , &wi , Samples1[i] , &PdfInput );

		if( PdfInput > 0.0f )
		{
			r += f * fabs( wo.z ) * fabs( wi.z ) / ( PdfInput * PdfOutput );
		}
	}

	return r / ( PI * nSamples );
}

// �������䷽���Լ�һ�������
// �����������������һ�����䷽��
Spectrum BxDF::rho( const Vector3f& wo , int nSamples , Point2f* samples ) const
{ 
	Spectrum r = 0;

	for( int i = 0; i < nSamples; i++ )
	{
		Vector3f wi;
		float pdf = 0.0f;

		Spectrum f = Sample_f( wo , &wi , samples[i] , &pdf );

		if( pdf > 0.0 )
		{
			r += f * fabs( wi.z ) / pdf;
		}
	}

	return r / float( nSamples );
}