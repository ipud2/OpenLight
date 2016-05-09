#include "MathHelper.h"
#include <float.h>
#include <cmath>

const float MathHelper::Infinity = FLT_MAX;		//���������ֵ
const float MathHelper::Pi = 3.1415926535f;


float MathHelper::AngleFromXY(float x, float y)
{
	float theta = 0.0f;

	if (x >= 0.0f)
	{
		theta = atanf(y / x);	//�����н�

		if (theta < 0.0f)
		{
			theta += 2 * Pi;
		}
	}

	else
	{
		theta = atanf(y / x) + Pi;		//���е�������Pi
	}


	return theta;
}


DirectX::XMVECTOR MathHelper::RandHemisphereUnitVec3(DirectX::XMVECTOR n)
{
	DirectX::XMVECTOR One = DirectX::XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f);
	DirectX::XMVECTOR Zero = DirectX::XMVectorZero();


	while (true)
	{
		//����һ����������[-1 , 1]^3�ڵ������
		DirectX::XMVECTOR v = DirectX::XMVectorSet(MathHelper::RandF(-1.0f, 1.0f), MathHelper::RandF(-1.0f, 1.0f), MathHelper::RandF(-1.0f, 1.0f) , 0.0f);

		//������ɵĵ��ڵ�λ���⣬���������ɣ���ֹ��ۼ�����������ĸ���
		if (DirectX::XMVector3Greater(DirectX::XMVector3LengthSq(v), One))
			continue;

		//���Ծۼ������ĵĵ�
		if (DirectX::XMVector3Less(DirectX::XMVector3Dot(n, v), Zero))
			continue;

		//���
		return DirectX::XMVector3Normalize(v);
	}
}


DirectX::XMVECTOR MathHelper::RandUnitVec3()
{
	DirectX::XMVECTOR One = DirectX::XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f);
	DirectX::XMVECTOR Zero = DirectX::XMVectorZero();

	while (true)
	{
		//����һ����λ�������е������
		DirectX::XMVECTOR v = DirectX::XMVectorSet( MathHelper::RandF( -1.0f , 1.0f ) , MathHelper::RandF( -1.0f , 1.0f ) , MathHelper::RandF( -1.0f , 1.0f ) , 0.0f );

		//ȥ���ڵ�λ��֮��ĵ�
		if ( DirectX::XMVector3Greater( DirectX::XMVector3LengthSq( v ) , One ) )
			continue;

		return DirectX::XMVector3Normalize( v );
	}
}