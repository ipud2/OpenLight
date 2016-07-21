#pragma once

#include "Fresnel.h"

// ����
class FresnelConductor : public Fresnel
{
public:
	Spectrum Evalute( float cosThetaI ) const;

	FresnelConductor( const Spectrum& etaI , const Spectrum& etaT , const Spectrum& k );

private:
	Spectrum etaI;		// ����ý���������
	Spectrum etaT;		// ����ý���������
	Spectrum k;			// ����ϵ��
};