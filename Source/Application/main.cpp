#include "PCH.h"
#include "Core/Scene.h"
#include "Renderer/SamplerRenderer.h"
#include "Primitive/Primitive.h"
#include "Math/Transform.h"
#include "Math/Point3.h"
#include "Shapes/Sphere.h"
#include "Camera/ThinLensCamera.h"
#include "Camera/PinholeCamera.h"
#include "Sampler/PureRandomSampler.h"
#include "Spectrum/Spectrum.h"
#include "Utilities/srString.h"
#include "IO/FileSystem.h"
#include "Sampler/NRooksSampler.h"
#include "Integrator/SimpleIntegrator.h"
#include "Integrator/WhittedIntegrator.h"
#include "BRDF/Lambertian.h"
#include "Light/PointLight.h"
#include "Accelerator/Grid.h"
#include "tinyxml2.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace tinyxml2;

Renderer* DeserializationScene( Scene* scene , Camera*& camera , SurfaceIntegrator* pSurfaceIntegrator , Sampler* pSampler )
{
	FileSystem fs;
	std::wstring SceneFilename = fs.GetSceneFolder() + L"secondScene.xml";

	XMLDocument doc;
	doc.LoadFile( srString::ToAscii( SceneFilename ).c_str() );

	// ----------------------------------Primitive---------------------------------------------
	XMLElement* PrimitiveElement = doc.FirstChildElement()->FirstChildElement( "primitive" );
	while( PrimitiveElement )
	{
		Primitive* primitive = new Primitive;
		primitive->Deserialization( PrimitiveElement );
		scene->AddObject( *primitive );

		PrimitiveElement = PrimitiveElement->NextSiblingElement( "primitive" );
	}
	
	// -----------------------------------Light---------------------------------------------
	XMLElement* LightRootElement = doc.FirstChildElement()->FirstChildElement( "light" );
	while( LightRootElement )
	{
		// for test , hard core
		Light* light = new PointLight;
		light->Deserialization( LightRootElement );
		scene->AddLight( light );

		LightRootElement = LightRootElement->NextSiblingElement( "light" );
	}

	// ---------------------------------Film---------------------------------------------
	Film* film = new Film();
	XMLElement* FilmElement = doc.FirstChildElement()->FirstChildElement( "Film" );
	film->Deserialization( FilmElement );

	// ---------------------------------Camera---------------------------------------------
	XMLElement* CameraElement = doc.FirstChildElement()->FirstChildElement( "Camera" );
	const char* CameraType = CameraElement->FirstAttribute()->Value();
	if( !std::strcmp( "ThinLens" , CameraType ) )
	{
		SAFE_DELETE( camera );
		
		camera = new ThinLensCamera;

		camera->SetFilm( film );

		camera->Deserialization( CameraElement );	
	}
	else if( !std::strcmp( "Pinhole" , CameraType ) )
	{
		SAFE_DELETE( camera );

		camera = new PinholeCamera;

		camera->SetFilm( film );

		camera->Deserialization( CameraElement );
	}
	else
	{
		Assert( "don't support \'%s\' Camera" , CameraType );
	}

	// -----------------------------Integrator--------------------------------------
	XMLElement* IntegratorRootElement = doc.FirstChildElement()->FirstChildElement( "Integrator" );
	const char* IntegratorType = IntegratorRootElement->FirstAttribute()->Value();
	if( !std::strcmp( "Whitted" , IntegratorType ) )
	{
		pSurfaceIntegrator = new WhittedIntegrator;
		pSurfaceIntegrator->Deserialization( IntegratorRootElement );
	}
	else
	{
		Assert( "don't support \'%s\' Integrator" , IntegratorType );
	}

	// --------------------------Sampler--------------------------------------------
	XMLElement* SamplerRootElement = doc.FirstChildElement()->FirstChildElement( "Sampler" );
	const char* SamplerType = SamplerRootElement->FirstAttribute()->Value();
	if( !std::strcmp( "PureRandom" , SamplerType ) )
	{
		pSampler = new PureRandomSampler;
		pSampler->Deserialization( SamplerRootElement );
	}
	else if( !std::strcmp( "NRooks" , SamplerType ) )
	{
		pSampler = new NRooksSampler;
		pSampler->Deserialization( SamplerRootElement );
	}
	else
	{
		Assert( "don't support \'%s\' Sampler" , SamplerType );
	}

	Grid* pGrid = new Grid;
	pGrid->Setup( scene );

	// ----------------------Renderer----------------------------------------
	XMLElement* RendererRootElement = doc.FirstChildElement()->FirstChildElement( "Renderer" );
	const char* RendererType = RendererRootElement->FirstAttribute()->Value();
	if( !std::strcmp( "Sampler" , RendererType ) )
	{
		Renderer* renderer = new SamplerRenderer( pSampler , camera , pSurfaceIntegrator , pGrid );

		renderer->Deserialization( RendererRootElement );

		return renderer;
	}
	else
	{
		Assert( "don't support \'%s\' Renderer" , RendererType );
	}

	return nullptr;
}

int main( void )
{	
	srand( ( unsigned int )time( NULL ) );

	Scene* scene = new Scene;

	Camera* camera = nullptr;

	SurfaceIntegrator* pSurfaceIntegrator = nullptr;

	Sampler* pSampler = nullptr;

	Renderer* renderer = DeserializationScene( scene , camera , pSurfaceIntegrator , pSampler);

	if( renderer != nullptr )
	{
		renderer->Render( scene );
	}

	return 0;
}