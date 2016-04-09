#include "PCH.h"
#include "IO/Log.h"
#include "Math/Normal.h"
#include "Math/Point3.h"
#include "Math/Ray.h"
#include "Math/Transform.h"
#include "Math/Vector3.h"
#include "Shape.h"

Shape::Shape( const Transform* _ObjectToWorld , const Transform* _WorldToObject )
{
	// ����ʹ��memcpy��ԭ����
	// �����Transform�п�������ĳ�������д����ģ�Ȼ�����������֮��ͱ�������
	// ����ĳ��Paser��������������Ȼ�󴴽���Transform����
	// Ȼ����Shape(&_ObjectToWorld , &_WorldToObject)
	// ���ǳ���������֮�󣬸��ڴ�ᱻ���٣���Ȼ�����new�����ģ��򲻻�
	// ����û���ֱ�ӽ����ݿ�������
	// Ȼ���������������ͷ�һ��
	ObjectToWorld = new Transform;
	memcpy( ObjectToWorld , _ObjectToWorld , sizeof( Transform ) );

	WorldToObject = new Transform;
	memcpy( WorldToObject , _WorldToObject , sizeof( Transform ) );
}

Shape::~Shape()
{
	SAFE_DELETE( ObjectToWorld );
	SAFE_DELETE( WorldToObject );
}

Bound3f Shape::WorldBound() const
{
	return ( *ObjectToWorld )( ObjectBound() );
}

bool Shape::Intersect( const Ray& ray , IntersectRecord* record ) const
{
	Assert( "Called Unimplemented Shape::Intersect()" );

	return false;
}

bool Shape::IntersectP( const Ray& ray ) const
{
	Assert( "Called Unimplemented Shape::IntersectP()" );

	return false;
}