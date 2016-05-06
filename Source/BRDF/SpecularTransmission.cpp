#include "PCH.h"
#include "Math/Normal.h"
#include "BxDFHelper.h"
#include "SpecularTransmission.h"

SpecularTransmission::SpecularTransmission( double etaI , double etaT , const Spectrum & T )
	: BxDF( BxDFType( TRANSMISSION | SPECULAR ) )
	, etaI( etaI )
	, etaT( etaT )
	, T( T )
	, fresnel( etaI , etaT )
{

}

SpecularTransmission::~SpecularTransmission()
{

}

Spectrum SpecularTransmission::f( const Vector3f& wo , const Vector3f& wi ) const
{
	return Spectrum( 0.0 );
}

// woΪ���ߵĴ������򣬷Ƿ�����
Spectrum SpecularTransmission::Sample_f( const Vector3f& wo , const Normal& n , Vector3f* wi , const Point2f& samplePoint , double* pdf , bool& bNoOccur ) const
{
	// �������䷽��
	bool entering = Dot( n , wo ) < 0.0;

	double newetaI = etaI;
	double newetaT = etaT;

	if( !entering )
	{
		Swap( newetaI , newetaT );
	}

	if( !Refract( wo , n , newetaI / newetaT , wi , entering ) )
	{
		// δ��������
		return Spectrum( 0 );
	}

	// �����䷽����pdfλ1
	*pdf = 1.0;

	return ( newetaT * newetaT ) / ( newetaI * newetaI ) * T * ( Spectrum( 1.0 ) - fresnel.Evalute( Dot( -wo , n ) ) ) / AbsDot( *wi , n );
}

double SpecularTransmission::PDF( const Vector3f& wi , const Vector3f& wo ) const
{
	return 0;
}