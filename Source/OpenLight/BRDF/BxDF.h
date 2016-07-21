#pragma once

#include "Spectrum/Spectrum.h"
#include "Math/Vector3.h"
#include "Math/Point2.h"
#include "BxDFHelper.h"

class BxDF
{
public:
	BxDF( BxDFType type );

	virtual ~BxDF();

	virtual Spectrum f( const Vector3f& wo , const Vector3f& wi ) const = 0;

	// �������䷽���Լ���ά�����㣬��������������䷽��
	// ���㷽��Ե�pdf������ֵΪ�õ㴦���÷��������Ӧ��BRDF
	virtual Spectrum Sample_f( const Vector3f& wo , const Vector3f& n , Vector3f* wi , const Point2f& samplePoint , float* pdf , bool& bNoOccur ) const;

	// �������䷽��һ�����䷽������㣬��������һ��������䷽��
	virtual Spectrum rho( const Vector3f& wo , const Vector3f& n , int nSamples , Point2f* samples ) const;

	virtual Spectrum rho( const Vector3f& n , int nSamples , Point2f* Samples1 , Point2f* Samples2 ) const;

	// ���鷽�������Ӧ�ĸ����ܶ�ֵ
	virtual float PDF( const Vector3f& wi , const Vector3f& wo , const Vector3f& n ) const;

	bool IsMatch( const BxDFType& flag );

public:
	BxDFType type;
};