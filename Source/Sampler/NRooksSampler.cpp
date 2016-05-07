#include "Utilities/PCH.h"
#include "tinyxml2.h"
#include "NRooksSampler.h"

NRooksSampler::NRooksSampler()
	:Sampler()
{
	
}

NRooksSampler::NRooksSampler( const NRooksSampler& rhs )
	: Sampler( rhs )
{
	GenerateUnitSquareSamples();
}

NRooksSampler& NRooksSampler::operator = ( const NRooksSampler& rhs )
{
	if( this == &rhs )
	{
		return ( *this );
	}

	Sampler::operator=( rhs );

	return ( *this );
}

NRooksSampler::~NRooksSampler()
{

}

void NRooksSampler::GenerateUnitSquareSamples()
{
	for( int i = 0; i < SampleGroupCount; i++ )
	{
		for( int j = 0; j < SampleCount; j++ )
		{
			CameraSample* samples = new CameraSample;
			samples->ImageSamples = Point2f( ( double )rand() / RAND_MAX , ( double )rand() / RAND_MAX );
			samples->LensSamples = Point2f( ( double )rand() / RAND_MAX , ( double )rand() / RAND_MAX );
			samples->TimeSamples = ( double )rand() / RAND_MAX;

			SamplePoints.push_back( samples );
		}
	}

	for( int i = 0; i < SampleGroupCount; i++ )
	{
		for( int j = 0; j < SampleCount; j++ )
		{
			// ���ŶԽ��߲���
			CameraSample* samples = new CameraSample;
			samples->ImageSamples = Point2f( ( j + ( double )rand() ) / ( double )SampleCount , ( j + ( double )rand() ) / ( double )SampleCount );
			samples->LensSamples = Point2f( ( j + ( double )rand() ) / ( double )SampleCount , ( j + ( double )rand() ) / ( double )SampleCount );
			samples->TimeSamples = ( j + ( double )rand() ) / ( double )SampleCount;

			SamplePoints.push_back( samples );
		}
	}

	// x�����������
	ShuffleXCoordinate();

	// y�����������
	ShuffleYCoordinate();
}

void NRooksSampler::Deserialization( tinyxml2::XMLElement* SamplerRootElement )
{
	SamplerRootElement->FirstChildElement( "SampleGroupCount" )->QueryIntText( &SampleGroupCount );
	SamplerRootElement->FirstChildElement( "SampleCount" )->QueryIntText( &SampleCount );

	SetProperty( SampleCount , SampleGroupCount );
}

void NRooksSampler::Serialization( tinyxml2::XMLDocument& xmlDoc , tinyxml2::XMLElement* pRootElement )
{
	pRootElement->SetAttribute( "type" , GetName() );

	{
		tinyxml2::XMLElement* pSampleGroupCountElement = xmlDoc.NewElement( "SampleGroupCount" );

		pSampleGroupCountElement->SetText( SampleGroupCount );

		pRootElement->InsertEndChild( pSampleGroupCountElement );

		tinyxml2::XMLElement* pSampleCountElement = xmlDoc.NewElement( "SampleCount" );

		pSampleCountElement->SetText( SampleCount );

		pRootElement->InsertEndChild( pSampleCountElement );
	}
}