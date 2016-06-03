#ifndef TEXTURE_H
#define TEXTURE_H

#include "Spectrum/Spectrum.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Core/VSerializableObject.h"
#include "Core/VCustomRTTI.h"

class Texture : public VSerializableObject
{
	DECLARE_DYNAMIC_CREATE_BASE( Texture )

public:
	// ͨ�ýӿڣ�����λ�ú��������귵����Ӧ������ֵ
	virtual Spectrum Evalute( const Vector2f& uv , const Point3f& p ) const = 0;
	virtual ~Texture();
};
#endif