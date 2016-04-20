#pragma once

#include "Camera.h"
#include "Math/Point2.h"
#include "Math/Point3.h"
#include "Math/Vector2.h"
#include "Film/Film.h"
#include "Sampler/Sampler.h"
#include "Core/Scene.h"

class ThinLensCamera : public Camera
{
public:
	ThinLensCamera();

	ThinLensCamera( const ThinLensCamera& rhs );

	void SetLensRadius( double _LensRadius );

	void SetLensFocus( double _LensFocus );

public:
	Ray GenerateRay( double RasterX , double RasterY , const CameraSample& SamplePoint );

public:
	void Deserialization( XMLElement* CameraRootElement );

private:
	double LensRadius;			// ͸���뾶
	double LensFocus;			// ����
};

typedef std::shared_ptr<ThinLensCamera> ThinLensPtr;