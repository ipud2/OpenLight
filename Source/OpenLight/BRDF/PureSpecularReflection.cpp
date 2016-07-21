#include "Utilities/PCH.h"
#include "PureSpecularReflection.h"

PureSpecularReflection::PureSpecularReflection( const Spectrum& R )
	: BxDF( BxDFType( REFLECTION | SPECULAR ) )
	, R( R )
{

}

PureSpecularReflection::~PureSpecularReflection()
{

}

Spectrum PureSpecularReflection::f( const Vector3f& wo , const Vector3f& wi ) const
{
	return Spectrum( 0.0 );
}

Spectrum PureSpecularReflection::Sample_f( const Vector3f& wo , const Vector3f& n , Vector3f* wi , const Point2f& samplePoint , float* pdf , bool& bNoOccur ) const
{
	*wi = Normalize( 2 * Dot( wo , n ) / n.Length() * Normalize( n ) - wo );

	*pdf = 1.0;

	return R / AbsDot( *wi , n );
}

float PureSpecularReflection::PDF( const Vector3f& wi , const Vector3f& wo , const Vector3f& n ) const
{
	// ���˷��䷽�����������PDFȫ��Ϊ0
	return 0;
}