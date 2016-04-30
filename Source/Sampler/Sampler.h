#pragma once

#include "PCH.h"
#include "RandomNumberGenerator.h"
#include "Math/Point2.h"
#include "Math/Point3.h"
#include "CameraSample.h"
#include "Core/VCustomRTTI.h"

class Sampler
{
	DECLARE_DYNAMIC_CREATE_BASE( Sampler )

public:
	Sampler();

	Sampler( const Sampler& s );

	Sampler& operator = ( const Sampler& rhs );

	virtual void GenerateUnitSquareSamples() = 0;

public:
	void SetProperty( const int SampleCount , const int SampleGroupCount );

protected:
	void SetupShuffledIndices();

	void ShuffleXCoordinate();

	void ShuffleYCoordinate();

public:
	CameraSample GetSamplePoint();

public:
	virtual void Deserialization( XMLElement* SamplerRootElement ) = 0;

public:
	std::vector<int>			ShuffledIndices;					// ����������Ŀ
	unsigned long				SamplePos;							// ��ǰʹ�õĲ�������Ŀ

	std::vector<CameraSample*> SamplePoints;

	int SampleCount;													// ÿ�������Ĳ�������Ŀ
	int SampleGroupCount;													// ��������
};

typedef Sampler* SamplerPtr;