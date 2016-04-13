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

	void SetFitMode( FitMode _Mode );

	void SetFilm( Film* _film );
	
public:
	Point3f GetCameraPosition() const;

	Vector2f GetApertureResolution() const;

	double GetViewDistance() const;

	double GetApertureDistance() const;

	double GetExposureTime() const;

	Film* GetFilm() const;

public:
	virtual Ray GenerateRay( double RasterX, double RasterY , const CameraSample& SamplePoint ) = 0;

	virtual void UpdateProperty();

public:
	virtual void ParseCamera( XMLElement* CameraRootElement ) = 0;

protected:
	Point3f		Eye;						// �������
	Point3f		Target;						// ���߷���
	double		ViewDistance;				// ����ƽ��ľ���
	double		ApertureDistance;			// ����Ȧ�ľ���
	Vector2f	ApertureResolution;			// ��Ȧ��С
	double		ExposureTime;				// �ع�ʱ��
	FitMode		Mode;

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