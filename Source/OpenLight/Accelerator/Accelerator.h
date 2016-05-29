#pragma once

class Ray;
class Scene;

// base class
class Accelerator
{
public:
	virtual void Setup( const Scene* scene ) = 0;
	virtual bool Intersect( Ray& ray , const Scene* scene , IntersectRecord* record ) = 0;

	virtual void Reset() = 0;
};