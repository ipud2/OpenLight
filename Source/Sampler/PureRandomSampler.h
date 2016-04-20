#pragma once
#include "Sampler.h"

class PureRandomSampler : public Sampler
{
public:
	PureRandomSampler();

	PureRandomSampler( const PureRandomSampler& r );

	PureRandomSampler& operator = ( const PureRandomSampler& rhs );

public:
	void Deserialization( XMLElement* SamplerRootElement );

private:
	virtual void GenerateUnitSquareSamples();
};