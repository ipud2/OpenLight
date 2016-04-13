#pragma once

#include "PCH.h"
#include "Primitive/Primitive.h"
#include "Math/Ray.h"
#include "Light/Light.h"
#include "Spectrum/Spectrum.h"

class Scene
{
public:
	Scene();

	void AddObject( Primitive& prim );
	
	void AddLight( Light* light );

	/*Spectrum Trace( const Ray& ray ) const;*/

	// �ཻ���㣬���ཻ��Ϣ������IntersectRecord��
	bool Intersect( const Ray& ray , IntersectRecord* record ) const;

	// �ཻ���ԣ�ֻ�ж��Ƿ��ཻ�����������ཻ��Ϣ
	bool IntersectP( const Ray& ray ) const;

	const std::vector<Light*>& GetLights() const;

protected:
	std::vector<Primitive> Objects;

	std::vector<Light*> lights;
};