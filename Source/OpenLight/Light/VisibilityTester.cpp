#include "Utilities/PCH.h"
#include "Core/Scene.h"
#include "Accelerator/Accelerator.h"
#include "VisibilityTester.h"

void VisibilityTester::SetSegment( const Point3f& p1 , float eps1 , const Point3f& p2 , float eps2 )
{
	float dist = ( p2 - p1 ).Length();

	r = Rayf( p1 , ( p2 - p1 ) / dist , eps1 , dist - eps2 );
}

bool VisibilityTester::Unoccluded( const Scene* scene , Accelerator* pAccelerator ) const
{
	IntersectRecord record;
	if( !pAccelerator->Intersect( r , scene , &record ) )
	{
		// δ������ײ����δ���ڵ�������true
		return true;
	}

	return false;
}