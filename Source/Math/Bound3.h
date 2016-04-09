#pragma once

#ifndef BOUND3_H
#define BOUND3_H

class Ray;
class Vector3f;

#include "Point3.h"

class Bound3f
{
public:
	Bound3f();

	Bound3f( const Point3f& p );

	Bound3f( const Point3f& p1 , const Point3f& p2 );

	const Point3f& operator[]( int i ) const;

	Point3f& operator[]( int i );

	Point3f Corner( int corner ) const;

	/// \brief �Խ���
	Vector3f Diagonal() const;

	// ��Χ�еı����
	float SurfaceArea() const;

	Vector3f Offset( const Point3f& p ) const;

	void BoundingSphere( Point3f* center , float* radius ) const;

	void ExpendToInclude( const Point3f& p );

	bool IntersectP( const Ray& ray , float* hitt0 = nullptr , float* hitt1 = nullptr ) const;

	inline bool IntersectP( const Ray& ray , const Vector3f& invDir , const int DirectionIsNegative[3] );

public:
	friend bool Inside( const Point3f& pt , const Bound3f& b );

public:
	Point3f pMin , pMax;
};

#endif