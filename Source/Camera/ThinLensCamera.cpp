#include "PCH.h"
#include "Sampler/Sampling.h"
#include "ThinLensCamera.h"

IMPLEMENT_DYNAMIC_CREATE_DERIVED( ThinLensCamera , Camera )

ThinLensCamera::ThinLensCamera()
{

}

ThinLensCamera::ThinLensCamera( const ThinLensCamera& rhs )
	:Camera( rhs )
{
	LensRadius = rhs.LensRadius;
	LensFocus = rhs.LensFocus;
}

void ThinLensCamera::SetLensRadius( double _LensRadius )
{
	if( LensRadius != _LensRadius )
	{
		LensRadius = _LensRadius;
	}
}

void ThinLensCamera::SetLensFocus( double _LensFocus )
{
	if( LensFocus != _LensFocus )
	{
		LensFocus = _LensFocus;
	}
}

Ray ThinLensCamera::GenerateRay( double RasterX , double RasterY , const CameraSample& SamplePoint )
{
	Vector2f RasterResolution = GetFilm()->GetResolution();

	// x , yΪ��ƽ���ϵĲ�����
	Point2f ImageSamples;
	ImageSamples.x = ( RasterX + SamplePoint.ImageSamples.x ) / RasterResolution.x * ( Right - Left ) + Left;
	ImageSamples.y = ( RasterY + SamplePoint.ImageSamples.y ) / RasterResolution.y  * ( Top - Bottom ) + Bottom;

	double x = ImageSamples.x / ViewDistance * LensFocus;
	double y = ImageSamples.y / ViewDistance * LensFocus;

	Point2f LensSamples = MapUnitSquareToUnitDisk( SamplePoint.LensSamples );

	Point3f Orig = Eye + LensRadius * LensSamples.x * uvw.U + LensRadius * LensSamples.y * uvw.V;

	Vector3f dir = ( x - LensRadius * LensSamples.x ) * uvw.U + ( y - LensRadius * LensSamples.y ) * uvw.V + LensFocus * uvw.W;

	return Ray( Orig , Normalize( dir ) , 1e-3f );
}

void ThinLensCamera::Deserialization( XMLElement* CameraRootElement )
{
	CameraRootElement->FirstChildElement( "Position" )->FirstChildElement( "x" )->QueryDoubleText( &( Eye.x ) );
	CameraRootElement->FirstChildElement( "Position" )->FirstChildElement( "y" )->QueryDoubleText( &( Eye.y ) );
	CameraRootElement->FirstChildElement( "Position" )->FirstChildElement( "z" )->QueryDoubleText( &( Eye.z ) );

	CameraRootElement->FirstChildElement( "Target" )->FirstChildElement( "x" )->QueryDoubleText( &( Target.x ) );
	CameraRootElement->FirstChildElement( "Target" )->FirstChildElement( "y" )->QueryDoubleText( &( Target.y ) );
	CameraRootElement->FirstChildElement( "Target" )->FirstChildElement( "z" )->QueryDoubleText( &( Target.z ) );

	CameraRootElement->FirstChildElement( "LensFocus" )->QueryDoubleText( &LensFocus );

	CameraRootElement->FirstChildElement( "LensRadius" )->QueryDoubleText( &LensRadius );

	CameraRootElement->FirstChildElement( "ExposureTime" )->QueryDoubleText( &ExposureTime );

	CameraRootElement->FirstChildElement( "ViewDistance" )->QueryDoubleText( &ViewDistance );

	CameraRootElement->FirstChildElement( "Fovy" )->QueryDoubleText( &fovy );

	UpdateProperty();
}