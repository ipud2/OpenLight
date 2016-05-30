#include "Utilities/PCH.h"
#include "Math/Normal.h"
#include "SpecularReflection.h"
#include "Utilities/RNG.h"

SpecularReflection::SpecularReflection( const Spectrum& R , const Fresnel* fresnel )
	: BxDF( BxDFType( REFLECTION | SPECULAR ) )
	, R( R )
	, fresnel( fresnel )
{

}

SpecularReflection::~SpecularReflection()
{
	SAFE_DELETE( fresnel );
}

Spectrum SpecularReflection::f( const Vector3f& wo , const Vector3f& wi ) const
{
	return Spectrum( 0.0 );
}

Spectrum SpecularReflection::Sample_f( const Vector3f& wo , const Normal& n , Vector3f* wi , const Point2f& samplePoint , double* pdf , bool& bNoOccur ) const
{
	*wi = Normalize( 2 * Dot( wo , n ) / n.Length() * Normalize( n ) - wo );

	*pdf = 1.0;

	Spectrum F = fresnel->Evalute( wo * n );

	double P = 0.25 + 0.5 * F[0];

	if( RNG::Get().GetDouble() > /*F[0]*/P )
	{
		// �޷���
		bNoOccur = true;
		return Spectrum( 0 );
	}

	return F / P * R / AbsDot( *wi , n );
}

double SpecularReflection::PDF( const Vector3f& wi , const Vector3f& wo , const Normal& n ) const
{
	// ���˷��䷽�����������PDFȫ��Ϊ0
	return 0;
}