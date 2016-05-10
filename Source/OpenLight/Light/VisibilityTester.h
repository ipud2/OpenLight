#pragma once

#include "Math/Ray.h"

class Accelerator;
class Scene;

class VisibilityTester
{
public:
	// ���ù����߶�
	void SetSegment( const Point3f& p1 , double eps1 , const Point3f& p2 , double eps2 );

	bool Unoccluded( const Scene* scene , Accelerator* pAccelerator ) const;

public:
	mutable Ray r;
};