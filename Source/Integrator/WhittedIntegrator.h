#pragma once

#include "SurfaceIntegrator.h"

class WhittedIntegrator : public SurfaceIntegrator
{
public:
	Spectrum Li( const Scene* scene , const Renderer* renderer , IntersectRecord* record , Ray* ray ) const;

	void SetMaxRecusiveDepth( int maxdepth );

	void ParseIntegrator(XMLElement* IntegratorRootElement);

private:
	int MaxDepth;
	int SamplePathNumber;
};