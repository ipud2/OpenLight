#include "Utilities/PCH.h"
#include "tinyxml2.h"
#include "Scene.h"

Scene::Scene()
{

}

void Scene::AddObject( Primitive& prim )
{
	Objects.push_back( prim );

	BBoxLocal.ExpendToInclude( prim.GetObjectBoundingBox() );
	BBoxWorld.ExpendToInclude( prim.GetWorldBoundingBox() );
}

void Scene::AddLight( Light* light )
{
	if( light == nullptr )
	{
		return;
	}

	lights.push_back( light );
}

bool Scene::Intersect( const Ray& ray , IntersectRecord* record ) const
{
	bool bHit = false;

	Ray r( ray.Origin , ray.Direction , ray.MinT , ray.MaxT , ray.time , ray.depth );

	for( unsigned int i = 0; i < Objects.size(); i++ )
	{
		if( Objects[i].Intersect( r , record ) )
		{
			bHit = true;
		}
	}

	return bHit;
}

const std::vector<Light*>& Scene::GetLights() const
{
	return lights;
}

void Scene::Deserialization( tinyxml2::XMLElement* RootElement )
{
	tinyxml2::XMLElement* PrimitiveElement = RootElement->FirstChildElement( "primitive" );
	while( PrimitiveElement )
	{
		Primitive* primitive = new Primitive;
		Assert( primitive != nullptr );
		primitive->Deserialization( PrimitiveElement );
		AddObject( *primitive );
		AddLight( primitive->GetAreaLight() );
		PrimitiveElement = PrimitiveElement->NextSiblingElement( "primitive" );
	}
}

void Scene::Serialization( tinyxml2::XMLDocument& xmlDoc , tinyxml2::XMLElement* pRootElement )
{
	for( auto& object : Objects )
	{
		tinyxml2::XMLElement* pElement = xmlDoc.NewElement( "primitive" );

		pRootElement->InsertEndChild( pElement );

		object.Serialization( xmlDoc , pElement );
	}

	for( auto& light : lights )
	{
		if( !strcmp( light->GetName() , "AreaLight" ) )
		{
			// AreaLightֻ��ҽ���Primitive�£���Primitive���л�
			continue;
		}

		tinyxml2::XMLElement* pElement = xmlDoc.NewElement( "light" );

		pRootElement->InsertEndChild( pElement );

		light->Serialization( xmlDoc , pElement );
	}
}

int Scene::GetObjectCount() const
{
	return Objects.size();
}

const Primitive& Scene::GetPrimitive( int index ) const
{
	return Objects[index];
}

Light* Scene::GetLight( int index ) const
{
	return lights[index];
}