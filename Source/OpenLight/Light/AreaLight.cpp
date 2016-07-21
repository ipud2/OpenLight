#include "Utilities/PCH.h"
#include "Primitive/Primitive.h"
#include "tinyxml2.h"
#include "AreaLighth.h"
#include "Utilities/srString.h"

AreaLight::AreaLight()
{
	m_pPrimitive = nullptr;
}

AreaLight::AreaLight( const Transform& LightToWorld , const Spectrum& Le )
	:Light( LightToWorld )
{

}

Spectrum AreaLight::Sample_L( const Point3f& p , Vector3f* wi , LightSample& _lightSample , float* pdf , VisibilityTester* pVisibility ) const
{
	// ������Դ��Ӧ��ͼԪ
	int index = ( int )( _lightSample.value[0] * ( m_pPrimitive->GetShapeCount() - 1 ) );

	Vector3f LightSourceSampleNormal;
	Point3f LightSourceSamplePoint = m_pPrimitive->GetShape( index )->Sample( p , _lightSample , LightSourceSampleNormal );

	*wi = Normalize( LightSourceSamplePoint - p );

	// Compute Primitive PDF value
	*pdf = m_pPrimitive->PDF( p , *wi );

	pVisibility->SetSegment( p , 1e-3f , LightSourceSamplePoint , 1e-3f );

	// Compute Li
	Spectrum Li = Le( LightSourceSamplePoint , LightSourceSampleNormal , -*wi );

	return Li;
}

// \Phi = \int_A\int_\Omega L(x \rightarrow \Theta )cos\theta d_{\omega_\Theta}dA
// ������������ԣ�L(x \rightarrow \Theta) = L
// \Phi = \int_A\int_\Omega Lcos\theta d_{\omega_\Theta}dA
// \Phi = L\int_AdA\int_\Omega cos\theta d_{\omega_\Theta}
// \Phi = LA\pi
Spectrum AreaLight::Power( const Scene* scene ) const
{
	return Lemission * m_pPrimitive->GetArea() * PI;
}

Spectrum AreaLight::Sample_L( const Scene* scene , LightSample& _lightSample , Rayf* ray , Vector3f* NormalShading , float* pdf ) const
{
	return Spectrum( 0.0 );
}

void AreaLight::Deserialization( tinyxml2::XMLElement* LightRootElement )
{
	ParseVector( LightRootElement->Attribute( "Le" ) , Lemission.GetDataPtr() );
}

void AreaLight::Serialization( tinyxml2::XMLDocument& xmlDoc , tinyxml2::XMLElement* pRootElement )
{
	{
		char* pText = new char[27];
		sprintf( pText , "%f,%f,%f" , Lemission[0] , Lemission[1] , Lemission[2] );

		pRootElement->SetAttribute( "Le" , pText );

		//SAFE_DELETE_ARRAY( pText );
	}
}

Spectrum AreaLight::Le( const Point3f& p , const Vector3f& n , const Vector3f& wo ) const
{
	// Note: ��AreaLight�������Դ�ļ��ϣ���ˣ����������жϣ��ĳ�ֱ�ӷ���Lemission

	/*return Dot( n , wo ) > 0.0 ? Lemission : 0.0;*/
	return Lemission;
}

float AreaLight::PDF( const Point3f& p , const Vector3f& wi ) const
{
	return m_pPrimitive->PDF( p , wi );
}

bool AreaLight::IsDelta()
{
	return false;
}

void AreaLight::SetPrimitive( Primitive* pPrimitive )
{
	m_pPrimitive = pPrimitive;
}