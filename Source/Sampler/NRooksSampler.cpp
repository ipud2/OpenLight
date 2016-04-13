#include "PCH.h"
#include "NRooksSampler.h"

NRooksSampler::NRooksSampler()
	:Sampler()
{
	GenerateUnitSquareSamples();
}

NRooksSampler::NRooksSampler( const int num_samples )
	: Sampler( num_samples )
{
	GenerateUnitSquareSamples();
}

NRooksSampler::NRooksSampler( const int num_samples , const int num_sets )
	: Sampler( num_samples , num_sets )
{
	GenerateUnitSquareSamples();
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

NRooksSampler* NRooksSampler::clone() const
{
	return ( new NRooksSampler( *this ) );
}

void NRooksSampler::GenerateUnitSquareSamples()
{
	for( int i = 0; i < NumSets; i++ )
	{
		for( int j = 0; j < NumSamples; j++ )
		{
			CameraSample* samples = new CameraSample;
			samples->ImageSamples = Point2f( ( double )rand() / RAND_MAX , ( double )rand() / RAND_MAX );
			samples->LensSamples = Point2f( ( double )rand() / RAND_MAX , ( double )rand() / RAND_MAX );
			samples->TimeSamples = ( double )rand() / RAND_MAX;

			SamplePoints.push_back( samples );
		}
	}

	for( int i = 0; i < NumSets; i++ )
	{
		for( int j = 0; j < NumSamples; j++ )
		{
			// ���ŶԽ��߲���
			CameraSample* samples = new CameraSample;
			samples->ImageSamples = Point2f( ( j + ( double )rand() ) / ( double )NumSamples , ( j + ( double )rand() ) / ( double )NumSamples );
			samples->LensSamples = Point2f( ( j + ( double )rand() ) / ( double )NumSamples , ( j + ( double )rand() ) / ( double )NumSamples );
			samples->TimeSamples = ( j + ( double )rand() ) / ( double )NumSamples;

			SamplePoints.push_back( samples );
		}
	}

	// x�����������
	ShuffleXCoordinate();

	// y�����������
	ShuffleYCoordinate();
}