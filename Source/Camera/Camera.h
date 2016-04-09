#pragma once

#include "Math/Ray.h"
#include "Math/ONB.h"
#include "Film/Film.h"
#include "Math/Vector3.h"
#include "Sampler/CameraSample.h"

class Scene;

class Camera
{
public:
	enum FitMode
	{
		FILL ,
		OverScan
	};

public:
	Camera();

	Camera( const Camera& orig );

	void SetCameraPositionAndLookAt( const Point3f& eye , const Point3f& TargetPoint );

	void SetApertureDistance( float d );

	void SetViewDistance( float d );

	void SetApertureResolution( const Vector2f& resolution );
	
	void SetExposureTime( float ExposureTime );

	void SetFitMode( FitMode _Mode );

	void SetFilm( Film* _film );
	
public:
	Point3f GetCameraPosition() const;

	Vector2f GetApertureResolution() const;

	float GetViewDistance() const;

	float GetApertureDistance() const;

	float GetExposureTime() const;

	Film* GetFilm() const;

public:
	virtual Ray GenerateRay( float RasterX, float RasterY , const CameraSample& SamplePoint ) = 0;

	virtual void UpdateProperty();

protected:
	Point3f		Eye;						// �������
	Point3f		Target;						// ���߷���
	float		ViewDistance;				// ����ƽ��ľ���
	float		ApertureDistance;			// ����Ȧ�ľ���
	Vector2f	ApertureResolution;			// ��Ȧ��С
	float		ExposureTime;				// �ع�ʱ��
	FitMode		Mode;

protected:
	bool		NeedUpdateParams;
	float		Top;
	float		Bottom;
	float		Left;
	float		Right;
	float		FilmAspectRatio;
	
	ONB uvw;							// ����ϵ

protected:
	Camera& operator = ( const Camera& camera );

private:
	Film * film;
};

typedef std::shared_ptr<Camera> CameraPtr;