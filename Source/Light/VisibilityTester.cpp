#include "PCH.h"
#include "Core/Scene.h"
#include "VisibilityTester.h"

void VisibilityTester::SetSegment( const Point3f& p1 , float eps1 , const Point3f& p2 , float eps2 )
{
	float dist = ( p2 - p1 ).Length();

	r = Ray( p1 , ( p2 - p1 ) / dist , eps1 , dist + ( 1 - eps2 ) );
}

bool VisibilityTester::Unoccluded( const Scene* scene ) const
{
	if( !scene->IntersectP( r ) )
	{
		return true;
	}

	return false;
}