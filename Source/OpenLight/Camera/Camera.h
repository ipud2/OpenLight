#pragma once

#include "Math/Ray.h"
#include "Math/ONB.h"
#include "Film/Film.h"
#include "Math/Vector3.h"
#include "Sampler/CameraSample.h"
#include "Core/VCustomRTTI.h"
#include "Core/VSerializableObject.h"

namespace tinyxml2
{
	class XMLElement;
}

class Scene;

class Camera : public VSerializableObject
{
	DECLARE_DYNAMIC_CREATE_BASE( Camera )

public:
	enum FitMode
	{
		FILL ,
		OverScan
	};

public:
	Camera();

	Camera( const Camera& orig );

	void SetFilm( Film* _film );
	
public:
	Point3f GetCameraPosition() const;

	double GetViewDistance() const;

	double GetExposureTime() const;

	Film* GetFilm() const;

	void SetFovy( double fov );

	float GetFovy() const;

public:
	virtual Ray GenerateRay( double RasterX, double RasterY , const CameraSample& SamplePoint ) = 0;

	virtual void UpdateProperty();

protected:
	Point3f		Eye;						// �������
	Point3f		Target;						// ���߷���
	double		ViewDistance;				// ����ƽ��ľ���
	double		ExposureTime;				// �ع�ʱ��
	double		fovy;						// y�����fov
	double		NearPlane;

protected:
	double		Top;
	double		Bottom;
	double		Left;
	double		Right;
	double		FilmAspectRatio;
	
	ONB uvw;							// ����ϵ

protected:
	Camera& operator = ( const Camera& camera );

private:
	Film * film;
};

typedef std::shared_ptr<Camera> CameraPtr;