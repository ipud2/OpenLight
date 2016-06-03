#pragma once

#include "Texture.h"

/*
	Format:
		<kd type="ConstantTexture" value="1.0,1.0,1.0" />
	kd��ʾ������ڵ�����֣���һ��Ϊ������
	��DiffuseMaterial Desserializationʱ������kd�ڵ㣬�͵���������
	����ڵ㲻�ᵥ�����֣��ض���������ĳ��Material�ϣ���������Material�ڲ��Ѿ�ȷ��
*/
class ConstantTexture : public Texture
{
	DECLARE_DYNAMIC_CREATE_DERIVED( ConstantTexture , Texture )

public:
	ConstantTexture();

	ConstantTexture( const Spectrum& v );

	virtual Spectrum Evalute( const Vector2f& uv , const Point3f& p ) const;

public:
	void Deserialization( tinyxml2::XMLElement* RootElement );

	void Serialization( tinyxml2::XMLDocument& xmlDoc , tinyxml2::XMLElement* pRootElement );

public:
	Spectrum& GetValue();

	void SetValue( Spectrum& _value );

private:
	Spectrum value;
};