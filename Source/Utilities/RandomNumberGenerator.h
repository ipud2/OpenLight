#pragma once

#include "PCH.h"

class RandomNumberGenerator
{
public:
	RandomNumberGenerator( uint32_t seed = 5489UL )
	{
		mti = N + 1;		// ��ζ��mt[N]û�г�ʼ��
		Seed( seed );
	}

	void Seed( uint32_t seed ) const;

	float RandomFloat() const;

	uint32_t RandomUInt() const;

private:
	static const int N = 624;
	mutable unsigned long mt[N];
	mutable int mti;
};