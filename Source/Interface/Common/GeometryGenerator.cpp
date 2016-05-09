#include "GeometryGenerator.h"
#include "MathHelper.h"



void GeometryGenerator::CreateBox(float width, float height, float depth, MeshData& meshData)
{
	//Create the vertices , the number of triangle is six
	Vertex v[24];

	float w2 = 0.5f * width;
	float h2 = 0.5f * height;
	float d2 = 0.5f * depth;

	
	//Fill in the front face vertex data
	v[0] = Vertex(-w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[1] = Vertex(-w2, h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[2] = Vertex(w2, h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	v[3] = Vertex(w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	//Fill in the back face  vertex data
	v[4] = Vertex( w2 , -h2 , d2 , 0.0f , 0.0f , 1.0f , -1.0f , 0.0f , 0.0f , 0.0f , 1.0f );
	v[5] = Vertex( w2 , h2 , d2 , 0.0f , 0.0f , 1.0f , -1.0f , 0.0f , 0.0f , 0.0f , 0.0f );
	v[6] = Vertex( -w2 , h2 , d2 , 0.0f , 0.0f , 1.0f , -1.0f , 0.0f , 0.0f , 1.0f , 0.0f );
	v[7] = Vertex( -w2 , -h2 , d2 , 0.0f , 0.0f , 1.0f , -1.0f , 0.0f , 0.0f , 1.0f , 1.0f );

	//Fill in the top face vertex data
	v[8] = Vertex(-w2, h2, -d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[9] = Vertex(-w2, h2, d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[10] = Vertex(w2, h2, d2, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	v[11] = Vertex(w2, h2, -d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	//Fill in the bottom face vertex data
	v[12] = Vertex( w2 , -h2 , -d2 , 0.0f , -1.0f , 0.0 , -1.0f , 0.0f , 0.0f , 0.0f , 1.0f );
	v[13] = Vertex( w2 , -h2 , d2 , 0.0f , -1.0f , 0.0f , -1.0f , 0.0f , 0.0f , 0.0f , 0.0f );
	v[14] = Vertex( -w2 , -h2 , d2 , 0.0f , -1.0f , 0.0f , -1.0f , 0.0f , 0.0f , 1.0f , 0.0f );
	v[15] = Vertex( -w2 , -h2 , -d2 , 0.0f , -1.0f , 0.0f , -1.0f , 0.0f , 0.0f , 1.0f , 1.0f );

	//Fill in the left face vertex data
	v[16] = Vertex(-w2, -h2, d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[17] = Vertex(-w2, h2, d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[18] = Vertex(-w2, h2, -d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	v[19] = Vertex(-w2, -h2, -d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	//Fill in the right face vertex data
	v[20] = Vertex(w2, -h2, -d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	v[21] = Vertex(w2, h2, -d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	v[22] = Vertex(w2, h2, d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	v[23] = Vertex(w2, -h2, d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);

	meshData.Vertices.assign(&v[0], &v[24]);

	

	//Create tgeh indices
	UINT i[36];

	//Fill in the font face index data
	i[0] = 0; i[1] = 1; i[2] = 2;
	i[3] = 0; i[4] = 2; i[5] = 3;

	//Fill in the bottom face index data
	i[6] = 4; i[7] = 5; i[8] = 6;
	i[9] = 4; i[10] = 6; i[11] = 7;

	//Fill in the top face index data
	i[12] = 8; i[13] = 9; i[14] = 10;
	i[15] = 8; i[16] = 10; i[17] = 11;

	//Fill in the bottom face index data
	i[18] = 12; i[19] = 13; i[20] = 14;
	i[21] = 12; i[22] = 14; i[23] = 15;

	//Fill in the left face index data
	i[24] = 16; i[25] = 17; i[26] = 18;
	i[27] = 16; i[28] = 18; i[29] = 19;

	//Fill in the right face index data
	i[30] = 20; i[31] = 21; i[32] = 22;
	i[33] = 20; i[34] = 22; i[35] = 23;

	meshData.Indices.assign(&i[0], &i[36]);
}



void GeometryGenerator::CreateSphere(float radius, UINT sliceCount, UINT stackCount, MeshData& meshData)
{
	meshData.Vertices.clear();
	meshData.Indices.clear();

	
	Vertex topVertex(0.0f, radius, 0.0f,	0.0f, 1.0f,	0.0f,	1.0f, 0.0f,	0.0f,	0.0f, 0.0f);
	Vertex bottomVertex(0.0f, -radius,0.0f,	0.0f, -1.0f, 0.0f,	-1.0f, 0.0f, 0.0f,	0.0f, 1.0f);
	


	//������ϵ��º��г�stackCountƬ
	//ÿ�����涼��һ��Բ
	//Ȼ�����ǽ����Բ��ΪsliceCount��
	//Ȼ�����ÿ���������
	//ͨ����������������
	//ʹ����������Ҫ֪���뾶������ֱ�������ļн�
	//�ڵ����ͶӰ��x�ļн�
	meshData.Vertices.push_back(topVertex);

	float phiStep = DirectX::XM_PI / stackCount;
	float thetaStep = 2.0f * DirectX::XM_PI / sliceCount;

	for (UINT i = 1; i <= stackCount - 1; ++i)
	{
		float phi = i * phiStep;			//����ֱ�������ļнǣ���������y������ļн�
		
		for (UINT j = 0; j <= sliceCount; j++)
		{
			float theta = j * thetaStep;	//�ڵ����ͶӰ��x��ļн�
			Vertex v;

			v.Position.x = radius * sinf(phi) * cosf(theta);
			v.Position.y = radius * cosf(phi);
			v.Position.z = radius * sinf(phi) * sinf(theta);


			/*
				����ͨ���ɸ������ޱƽ����ߣ����ҽ�ϼ��ޣ��������Ƶ������ϵ�һ�����������
				�ɲμ���http://netedu.xauat.edu.cn/jpkc/netedu/jpkc/gdsx/homepage/5jxsd/51/513/5308/530806.htm
				��ˣ�Position����theta��ƫ������Ϊ��������
			*/
			v.TangentU.x = -radius * sinf(phi) * sinf(theta);
			v.TangentU.y = 0.0f;
			v.TangentU.z = radius * sinf(phi) * cosf(theta);

			DirectX::XMVECTOR T = DirectX::XMLoadFloat3(&v.TangentU);
			DirectX::XMStoreFloat3(&v.TangentU, DirectX::XMVector3Normalize(T));


			//���߼�ΪԲ��ָ��õ����������˸պõ��ڵ��λ�������ֵ
			DirectX::XMVECTOR p = DirectX::XMLoadFloat3(&v.Position);
			DirectX::XMStoreFloat3(&v.Normal, DirectX::XMVector3Normalize(p));

			v.TexCoord.x = theta / DirectX::XM_2PI;
			v.TexCoord.y = phi / DirectX::XM_PI;

			meshData.Vertices.push_back(v);
		}
	}

	meshData.Vertices.push_back(bottomVertex);




	//compute indices for top stack . The top Stack was written first to the vertex buffer
	//and connects the top pole to the first ring
	//������Ǹ�Բ�������ڵ�����������ߵĶ����������������
	for (UINT i = 1; i <= sliceCount; i++)
	{
		//ע�ⷽ������i+1�ĵ����x������ƫ��ĽǶȱȵ�i����ƫ��ĽǶȸ�����˰���˳ʱ���ԭ��Ӧ����0��i+1��i
		meshData.Indices.push_back(0);
		meshData.Indices.push_back( i + 1 );
		meshData.Indices.push_back(i);
		
	}


	//�����ڲ��Ļ������������һ��������Ϊ���һ�����ϵĵ��Ǻ���ײ��Ķ������������
	UINT baseIndex = 1;
	UINT ringVertexCount = sliceCount + 1;

	for (UINT i = 0; i < stackCount - 2; i++)		//�����м��stackCount-2����
	{
		for (UINT j = 0; j < sliceCount; j++)
		{
			//���ڵ�ǰ��������ֵΪj,j+1�����������һ����������ֵ��ͬ��������
			//������������������Σ�������ߵ������ֵΪ0�����Դӵ�һ������ʼ
			//��i��������ʼ����ֵΪ��i - 1��*(sliceCount + 1)��
			//ע���ǵ�i���������Ժ������i-1��ѭ����ʱ���0��ʼ��
			//���Լ����ʱ����Ҫ��һ
			meshData.Indices.push_back(baseIndex + i * ringVertexCount + j);
			meshData.Indices.push_back(baseIndex + i * ringVertexCount + j + 1);
			meshData.Indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);

			meshData.Indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);
			meshData.Indices.push_back(baseIndex + i * ringVertexCount + j + 1);
			meshData.Indices.push_back(baseIndex + (i + 1) * ringVertexCount + j + 1);
		}
	}


	//���һ����
	UINT southPoleIndex = (UINT)meshData.Vertices.size() - 1;

	//�����һ�����е�һ�����������ƫ��ֵ
	baseIndex = southPoleIndex - ringVertexCount;

	for (UINT i = 0; i < sliceCount; i++)
	{
		meshData.Indices.push_back(southPoleIndex);
		meshData.Indices.push_back(baseIndex + i);
		meshData.Indices.push_back(baseIndex + i + 1);
	}
}



void GeometryGenerator::Subdivide(MeshData& meshData)
{
	//����һ������ͼԪ
	MeshData inputCopy = meshData;

	meshData.Vertices.resize(0);
	meshData.Indices.resize(0);

	//       v1
	//       *
	//      / \
	//     /   \
	//  m0*-----*m1
	//   / \   / \
	//  /   \ /   \
	// *-----*-----*
	// v0    m2     v2

	UINT numTris = inputCopy.Indices.size() / 3;	//ÿ�����������һ��������

	for (UINT i = 0; i < numTris; i++)
	{
		Vertex v0 = inputCopy.Vertices[inputCopy.Indices[i * 3 + 0]];
		Vertex v1 = inputCopy.Vertices[inputCopy.Indices[i * 3 + 1]];
		Vertex v2 = inputCopy.Vertices[inputCopy.Indices[i * 3 + 2]];


		//������������
		Vertex m0, m1, m2;

		//����ֻ����λ������
		m0.Position = DirectX::XMFLOAT3((v0.Position.x + v1.Position.x) * 0.5f,
								(v0.Position.y + v1.Position.y) * 0.5f,
								(v0.Position.z + v1.Position.z) * 0.5f);

		m1.Position = DirectX::XMFLOAT3((v1.Position.x + v2.Position.x) * 0.5f,
								(v1.Position.y + v2.Position.y) * 0.5f,
								(v1.Position.z + v2.Position.z) * 0.5f);

		m2.Position = DirectX::XMFLOAT3((v2.Position.x + v0.Position.x) * 0.5f,
								(v2.Position.y + v0.Position.y) * 0.5f,
								(v2.Position.z + v0.Position.z) * 0.5f);


		meshData.Vertices.push_back(v0);
		meshData.Vertices.push_back(v1);
		meshData.Vertices.push_back(v2);
		meshData.Vertices.push_back(m0);
		meshData.Vertices.push_back(m1);
		meshData.Vertices.push_back(m2);


		meshData.Indices.push_back(6 * i + 0);
		meshData.Indices.push_back(6 * i + 3);
		meshData.Indices.push_back(6 * i + 5);

		meshData.Indices.push_back(6 * i + 3);
		meshData.Indices.push_back(6 * i + 4);
		meshData.Indices.push_back(6 * i + 5);
		
		meshData.Indices.push_back(6 * i + 5);
		meshData.Indices.push_back(6 * i + 4);
		meshData.Indices.push_back(6 * i + 2);

		meshData.Indices.push_back(6 * i + 3);
		meshData.Indices.push_back(6 * i + 1);
		meshData.Indices.push_back(6 * i + 4);
	}
}



//��һ����ʮ����ϸ�֣�ʹ��ƽ���
//����ɶ�ʮ�����ÿ�������ν���ϸ��
//ϸ�ֺ�Ľ����ͨ��������Ϊ��λ��
//���������������Ƶ��������꣬�������꣬���������
void GeometryGenerator::CreateGeoSphere(float radius, UINT numSubdivisions, MeshData& meshData)
{
	numSubdivisions = MathHelper::Min(numSubdivisions , 5u);	//����ϸ������

	const float X = 0.525731f;
	const float Z = 0.850651f;


	//����һ��20���壬20�����ܹ�12������
	//����ֵΪ60��
	DirectX::XMFLOAT3 pos[12] = 
	{
		DirectX::XMFLOAT3(-X, 0.0f, Z),  DirectX::XMFLOAT3(X, 0.0f, Z),  
		DirectX::XMFLOAT3(-X, 0.0f, -Z), DirectX::XMFLOAT3(X, 0.0f, -Z),    
		DirectX::XMFLOAT3(0.0f, Z, X),   DirectX::XMFLOAT3(0.0f, Z, -X), 
		DirectX::XMFLOAT3(0.0f, -Z, X),  DirectX::XMFLOAT3(0.0f, -Z, -X),    
		DirectX::XMFLOAT3(Z, X, 0.0f),   DirectX::XMFLOAT3(-Z, X, 0.0f), 
		DirectX::XMFLOAT3(Z, -X, 0.0f),  DirectX::XMFLOAT3(-Z, -X, 0.0f)
	};

	DWORD k[60] = 
	{
		1,4,0,  4,9,0,  4,5,9,  8,5,4,  1,8,4,    
		1,10,8, 10,3,8, 8,3,5,  3,2,5,  3,7,2,    
		3,10,7, 10,6,7, 6,11,7, 6,0,11, 6,1,0, 
		10,1,6, 11,0,9, 2,11,9, 5,2,9,  11,2,7 
	};

	meshData.Vertices.resize(12);
	meshData.Vertices.resize(60);


	for(UINT i = 0; i < 12; i++)
	{
		meshData.Vertices[i].Position = pos[i];
	}

	for(UINT i = 0; i < 60; i++)
	{
		meshData.Indices[i] = k[i];
	}

	//ϸ�ֶ�ʮ����
	for(UINT i = 0; i < numSubdivisions; i++)
	{
		Subdivide(meshData);
	}

	//Ϊϸ�ֺ�ıƽ��������������λ�ã����ߣ����ߣ���������
	for(UINT i = 0; i < meshData.Vertices.size(); i++)
	{
		//������Ϊ��λ��
		DirectX::XMVECTOR n = DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&meshData.Vertices[i].Position));

		DirectX::XMVECTOR p = DirectX::XMVectorScale( n , radius );		//������İ뾶Ϊradius����nΪ��λ����������ֱ����˾͵õ���

		DirectX::XMStoreFloat3(&meshData.Vertices[i].Position , p);


		//����
		DirectX::XMStoreFloat3(&meshData.Vertices[i].Normal , n);


		//�����������Ƶ��������꼰��������
		//���������������Ƕ�
		float theta = MathHelper::AngleFromXY(meshData.Vertices[i].Position.x , meshData.Vertices[i].Position.z);

		float phi = acosf(meshData.Vertices[i].Position.y / radius);


		//��������
		meshData.Vertices[i].TexCoord.x = theta / DirectX::XM_2PI;
		meshData.Vertices[i].TexCoord.y = phi / DirectX::XM_PI;


		//�������꣬λ�ù���theta��ƫ����
		meshData.Vertices[i].TangentU.x = -radius * sinf(phi) * sinf(theta);
		meshData.Vertices[i].TangentU.y = 0.0f;
		meshData.Vertices[i].TangentU.z = radius * sinf(phi) * cosf(theta);

		DirectX::XMVECTOR T = DirectX::XMLoadFloat3(&meshData.Vertices[i].TangentU);
		DirectX::XMStoreFloat3(&meshData.Vertices[i].TangentU , DirectX::XMVector3Normalize(T));
	}
}



void GeometryGenerator::CreateCylinder(float bottomRadius, float topRadius, float height, UINT sliceCount, UINT stackCount, MeshData& meshData)
{
	meshData.Vertices.clear();
	meshData.Indices.clear();


	//��Բ������ϵ��·�stackCount�ݣ�ÿһ���������ķ�sliceCount
	float stackHeight = height / stackCount;	//y�������

	double radiusStep = (topRadius - bottomRadius) / stackCount;	//�뾶����

	UINT ringCount = stackCount + 1;
	for(UINT  i = 0; i < ringCount; i++)
	{
		float y = -0.5f * height + i * stackHeight;
		float r = bottomRadius + i * radiusStep;

		//Բ���ָ��Ƕȵ�����
		float dTheta = 2.0f * DirectX::XM_PI / sliceCount;

		for(UINT j = 0; j <= sliceCount; j++)		//Բ���Ϸָ��sliceCount��
		{
			Vertex vertex;

			float c = cosf(j * dTheta);
			float s = sinf(j * dTheta);

			vertex.Position = DirectX::XMFLOAT3(r * c , y , r * s);

			vertex.TexCoord.x = (float)j / sliceCount;
			vertex.TexCoord.y = 1.0f - (float)i / stackCount;	//�����Ǵ������Ϸָ��

			

			//�������������
			// y(v) = h - hv for v in [0,1]
			// r(v) = r1 + (r0 - r1) * v
			//
			// x(t , v) = r(v) * cos(t)
			// y(t , v) = h - hv;
			// z(t , v) = r(v) * sin(t)
			//
			// dx/dt = -r(v)*sin(t);
			// dy/dt = 0;
			// dz/dt = r(v)*cos(t)
			//
			// dx/dv = (r0 - r1)*cos(t)
			// dy/dv = -h;
			// dz/dv = (r0 - r1)*sin(t);

			vertex.TangentU = DirectX::XMFLOAT3(-s , 0.0f , c);

			float dr = topRadius - bottomRadius;
			DirectX::XMFLOAT3 bitTangent(-dr * c , -height , -dr * s);

			DirectX::XMVECTOR T = DirectX::XMLoadFloat3(&vertex.TangentU);
			DirectX::XMVECTOR B = DirectX::XMLoadFloat3(&bitTangent);
			DirectX::XMVECTOR N = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(T , B));

			DirectX::XMStoreFloat3(&vertex.Normal , N);

			meshData.Vertices.push_back(vertex);
		}
	}


	//Index
	UINT ringVertexCount = sliceCount + 1;
	for(UINT i = 0; i < stackCount; i++)
	{
		for(UINT j = 0; j < sliceCount; j++)
		{
			meshData.Indices.push_back(i * ringVertexCount + j);
			meshData.Indices.push_back((i + 1) * ringVertexCount + j);
			meshData.Indices.push_back((i + 1) * ringVertexCount + j + 1);

			meshData.Indices.push_back(i * ringVertexCount + j);
			meshData.Indices.push_back((i + 1) * ringVertexCount + j + 1);
			meshData.Indices.push_back(i * ringVertexCount + j + 1);
		}
	}


	BuildCylinderTopCap(bottomRadius , topRadius , height , sliceCount , stackCount , meshData);
	BuildCylinderBottomCap(bottomRadius , topRadius , height , sliceCount , stackCount , meshData);
}


void GeometryGenerator::BuildCylinderTopCap(float bottomRadius, float topRadius, float height, UINT sliceCount, UINT stackCount, MeshData& meshData)
{
	UINT baseIndex = (UINT)meshData.Vertices.size();

	float y = 0.5f * height;
	float dTheta = DirectX::XM_2PI / sliceCount;

	for(UINT i = 0; i <= sliceCount; i++)
	{
		float x = topRadius * cosf(i * dTheta);
		float z = topRadius * sinf(i * dTheta);

		float u = x / height + 0.5f;
		float v = z / height + 0.5f;

		meshData.Vertices.push_back(Vertex(x , y , z , 0.0f , 1.0f , 0.0f , 1.0f , 0.0f , 0.0f , u , v));
	}

	//�϶�������ĵ�
	meshData.Vertices.push_back(Vertex(0.0f , y , 0.0f , 0.0f , 1.0f , 0.0f , 1.0f , 0.0f , 0.0f , 0.0f , 0.0f));


	//�϶������ĵ������ֵ
	UINT centerIndex = (UINT)meshData.Vertices.size() - 1;

	for(UINT i = 0; i < sliceCount; i++)
	{
		meshData.Indices.push_back(centerIndex);
		meshData.Indices.push_back(baseIndex + i);
		meshData.Indices.push_back(baseIndex + i + 1);
	}
}


void GeometryGenerator::BuildCylinderBottomCap(float bottomRadius, float topRadius, float height, UINT sliceCount, UINT stackCount, MeshData& meshData)
{
	UINT baseIndex = meshData.Vertices.size();

	float y = -0.5f * height;
	float dTheta = DirectX::XM_2PI / sliceCount;

	for(UINT i = 0; i <= sliceCount; i++)
	{
		float x = bottomRadius * cosf(i * dTheta);
		float z = bottomRadius * sinf(i * dTheta);

		float u = x / height + 0.5f;
		float v = z / height + 0.5f;

		meshData.Vertices.push_back(Vertex(x , y , z , 0.0f , -1.0f , 0.0f , 1.0f , 0.0f , 0.0f , u , v));
	}

	meshData.Vertices.push_back(Vertex(0.0f , -0.5f * height , 0.0f , 0.0f , -1.0f , 0.0f , 1.0f , 0.0f , 0.0f , 0.5f , 0.5f));

	UINT centerIndex = (UINT)meshData.Vertices.size() - 1;

	for(UINT i = 0; i < sliceCount; i++)
	{
		meshData.Indices.push_back(centerIndex);
		meshData.Indices.push_back(baseIndex + i);
		meshData.Indices.push_back(baseIndex + i + 1);
	}
}


void GeometryGenerator::CreateGrid(float width, float depth, UINT m, UINT n, MeshData& meshData)
{
	UINT vertexCount = m * n;		//m��n�е�����
	UINT faceCount = (m - 1) * (n - 1) * 2;

	float halfWidth = width * 0.5f;
	float halfDepth = depth * 0.5f;

	float xStep = width / (n - 1);
	float zStep = depth / (m - 1);

	meshData.Vertices.resize(vertexCount);
	meshData.Indices.resize(faceCount * 3);

	float du = 1.0f / (n -1);
	float dv = 1.0f / (m - 1);

	for(UINT i = 0; i < m; i++)
	{
		float z = halfDepth - i * zStep;

		for(UINT j = 0; j < n; j++)
		{
			float x = -halfWidth + j * xStep;

			meshData.Vertices[i * n + j].Position = DirectX::XMFLOAT3(x , 0.0f , z);
			meshData.Vertices[i * n + j].Normal = DirectX::XMFLOAT3(0.0f , 1.0f , 0.0f);
			meshData.Vertices[i * n + j].TangentU = DirectX::XMFLOAT3(1.0f , 0.0f , 0.0f);
			meshData.Vertices[i * n + j].TexCoord = DirectX::XMFLOAT2(j * du , i * dv);
		}
	}


	UINT k = 0;
	for(UINT i = 0; i < m - 1; i++)
	{
		for(UINT j = 0; j < n - 1; j++)
		{
			meshData.Indices[k] = i * n + j;
			meshData.Indices[k + 1] = i * n + j + 1;
			meshData.Indices[k + 2] = (i + 1) * n + j;

			meshData.Indices[k + 3] = (i + 1) * n + j;
			meshData.Indices[k + 4] = i * n + j + 1;
			meshData.Indices[k + 5] = (i + 1) * n + j + 1;

			k += 6;
		}
	}
}



void GeometryGenerator::CreateFullscreenQuad(MeshData& meshData)
{
	meshData.Vertices.resize(4);
	meshData.Indices.resize(6);

	meshData.Vertices[0] = Vertex(-1.0f, -1.0f, 0.5f, 
                                   0.0f, 0.0f, -1.0f, 
                                   1.0f, 0.0f, 0.0f, 
                                   0.0f, 1.0f);
	meshData.Vertices[1] = Vertex(-1.0f, 1.0f, 0.5f, 
                                   0.0f, 0.0f, -1.0f, 
                                   1.0f, 0.0f, 0.0f, 
                                   0.0f, 0.0f);
	meshData.Vertices[2] = Vertex(1.0f, 1.0f, 0.5f, 
                                   0.0f, 0.0f, -1.0f, 
                                   1.0f, 0.0f, 0.0f, 
                                   1.0f, 0.0f);
	meshData.Vertices[3] = Vertex(1.0f, -1.0f, 0.5f, 
                                   0.0f, 0.0f, -1.0f, 
                                   1.0f, 0.0f, 0.0f, 
                                   1.0f, 1.0f);


	meshData.Indices[0] = 0;
	meshData.Indices[1] = 1;
	meshData.Indices[2] = 2;

	meshData.Indices[3] = 0;
	meshData.Indices[4] = 2;
	meshData.Indices[5] = 3;
}