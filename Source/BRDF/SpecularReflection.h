#pragma once

#include "BxDF.h"
#include "Fresnel.h"

class SpecularReflection : public BxDF
{
public:
	SpecularReflection( const Spectrum& R , const Fresnel* fresnel );

	~SpecularReflection();

	Spectrum f( const Vector3f& wo , const Vector3f& wi ) const;

	Spectrum Sample_f( const Vector3f& wo , const Normal& n , Vector3f* wi , const Point2f& samplePoint , double* pdf ) const;

	double PDF( const Vector3f& wi , const Vector3f& wo ) const;

private:
	const Spectrum R;			// �������ŷ�����ɫ
	const Fresnel* fresnel;	// ���ڼ�������ⱻ����ı���
};