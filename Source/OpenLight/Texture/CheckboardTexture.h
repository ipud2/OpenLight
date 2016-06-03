#pragma once

#include "Texture.h"

class ConstantTexture;

/*
	Format:
		<kd type="CheckboardTexture" value1="1.0,1.0,1.0" value2="0.0,0.0,0.0"/>
	kdΪ������ڵ�����kd�����ڱ�ʾ����������
	typeΪ����class name
	value1��value2�ֱ�Ϊ���������������ɫֵ
*/
class CheckerboardTexture : public Texture
{
	DECLARE_DYNAMIC_CREATE_DERIVED( CheckerboardTexture , Texture )

public:
	CheckerboardTexture();

	CheckerboardTexture( ConstantTexture* tex1 , ConstantTexture* tex2 );

	~CheckerboardTexture();

	virtual Spectrum Evalute( const Vector2f& uv , const Point3f& p ) const;

public:
	void Deserialization( tinyxml2::XMLElement* RootElement );

	void Serialization( tinyxml2::XMLDocument& xmlDoc , tinyxml2::XMLElement* pRootElement );

private:
	ConstantTexture* texture1;
	ConstantTexture* texture2;
};