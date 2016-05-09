#include "Utilities/PCH.h"
#include "PPMImage.h"
#include "tinyxml2.h"
#include "Film.h"

Film::Film()
{
	Width = 800;
	Height = 600;

	Gamma = 2.4;
	InvGamma = 1.0f / Gamma;

	Filename = "result.ppm";

	image = new PPMImage( Filename , Width , Height );
}

void Film::SetResolution( int xResolution , int yResolution )
{
	Width = xResolution;
	Height = yResolution;
}

void Film::SetGamma( double gamma )
{
	Gamma = gamma;
	InvGamma = 1.0f / Gamma;
}

void Film::SetFilename( char* filename )
{
	Filename = filename;

	std::string name( Filename );

	if( name.size() >= 5 )
	{
		uint32_t suffixOffset = name.size() - 4;
		
		if( !strcmp( name.c_str() + suffixOffset , ".ppm" ) ||
			!strcmp( name.c_str() + suffixOffset , ".PPM" ) )
		{
			if( image )
			{
				SAFE_DELETE( image );
			}

			image = new PPMImage( Filename , Width , Height );
		}
	}
}

void Film::SetColor( int row , int col , Spectrum color )
{
	image->SetColor( row , col , color );
}

double Film::GetAspectio() const
{
	return double( Width ) / double( Height );
}

void Film::Display()
{
	image->Display();
}

Vector2f Film::GetResolution() const
{
	return Vector2f( Width , Height );
}

void Film::Deserialization( const tinyxml2::XMLElement* FilmRootElement )
{
	// ---------------------------------Film---------------------------------------------
	Filename = new char[20];
	strcpy_s( Filename , 20 , FilmRootElement->FirstChildElement( "filename" )->GetText() );

	FilmRootElement->FirstChildElement( "width" )->QueryIntText( &Width );
	FilmRootElement->FirstChildElement( "height" )->QueryIntText( &Height );

	SAFE_DELETE( image );

	image = new PPMImage( Filename , Width , Height );
}

void Film::Serialization( tinyxml2::XMLDocument& xmlDoc , tinyxml2::XMLElement* pRootElement )
{
	{
		tinyxml2::XMLElement* pFilenameElement = xmlDoc.NewElement( "filename" );
		pFilenameElement->SetText( Filename );
		pRootElement->InsertEndChild( pFilenameElement );
	}

	{
		tinyxml2::XMLElement* pWidthElement = xmlDoc.NewElement( "width" );
		pWidthElement->SetText( Width );
		pRootElement->InsertEndChild( pWidthElement );

		tinyxml2::XMLElement* pHeightElement = xmlDoc.NewElement( "height" );
		pHeightElement->SetText( Height );
		pRootElement->InsertEndChild( pHeightElement );
	}
}

Image* Film::GetImage()
{
	return image;
}

void Film::Resize( int _Width , int _Height )
{
	SAFE_DELETE( image );

	Width = _Width;
	Height = _Height;

	image = new PPMImage( Filename , Width , Height );
}