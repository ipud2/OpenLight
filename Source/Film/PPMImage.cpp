#include "PCH.h"
#include "Spectrum/Spectrum.h"
#include "PPMImage.h"

PPMImage::PPMImage( char* filename , int width , int height )
	:Image( filename , width , height )
{
	data = new Spectrum[Width * height];
}

void PPMImage::SetColor( int row , int col , Spectrum spectrum )
{
	if( 0 > col || col >= Width )
	{
		Log::Get().Error( "col value is outside of Image resolution in %s , %s line" , __FILE__ , __LINE__ );
	}

	if( 0 > row || row > Height )
	{
		Log::Get().Error( "row value is outside of Image resolution in %s , %s line" , __FILE__ , __LINE__ );
	}

	data[row * Width + col] = spectrum;
}

Spectrum PPMImage::GetColor( int row , int col ) const
{
	if( 0 > col || col >= Width )
	{
		Log::Get().Error( "col value is outside of Image resolution in %s , %s line" , __FILE__ , __LINE__ );
	}

	if( 0 > row || row > Height )
	{
		Log::Get().Error( "row value is outside of Image resolution in %s , %s line" , __FILE__ , __LINE__ );
	}

	return data[row * Width + col];
}

void PPMImage::Display()
{
	std::ofstream ofs( Filename );

	ofs << "P6\n";
	ofs << Width << ' ' << Height << '\n';
	ofs << "255\n";

	unsigned int ired , igreen , iblue;
	unsigned char red , green , blue;

	float RGB[3];

	for( int row = 0; row < Height; row++ )
	{
		for( int col = 0; col < Width; col++ )
		{
			data[row * Width + col].ToRGB( RGB );

			ired   = ( unsigned int )( 255 * RGB[0] );
			igreen = ( unsigned int )( 255 * RGB[1] );
			iblue  = ( unsigned int )( 255 * RGB[2] );

			Clamp( ired   , 0 , 255 );
			Clamp( igreen , 0 , 255 );
			Clamp( iblue  , 0 , 255 );

			red   = ( unsigned char )( ired );
			green = ( unsigned char )( igreen );
			blue  = ( unsigned char )( iblue );

			ofs.put( green );
			ofs.put( blue );
			ofs.put( red );
		}
	}
}