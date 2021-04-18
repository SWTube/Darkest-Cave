#include "pch.h"
#include "framework.h"
#include "modelclass.h"


ModelClass::ModelClass()
{
}


ModelClass::ModelClass(const ModelClass& other)
{
}


ModelClass::~ModelClass()
{
}


bool ModelClass::Initialize(ID3D11Device* device)
{
	// 정점 및 인덱스 버퍼를 초기화합니다.
	return InitializeBuffers(device);
}


void ModelClass::Shutdown()
{
	// 버텍스 및 인덱스 버퍼를 종료합니다.
	ShutdownBuffers();
}


void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	// 그리기를 준비하기 위해 그래픽 파이프 라인에 꼭지점과 인덱스 버퍼를 놓습니다.
	RenderBuffers(deviceContext);
}

void ModelClass::SetColor(XMFLOAT4 color)
{
	m_color = color;
}

void ModelClass::SetMoveX(int x)
{
	moveX = x;
}


int ModelClass::GetIndexCount()
{
	return m_indexCount;
}


bool ModelClass::InitializeBuffers(ID3D11Device* device)
{	
	int div = 63;

	// 정점 배열의 정점 수를 설정합니다.
	m_vertexCount = div + 1;

	// 인덱스 배열의 인덱스 수를 설정합니다.
	m_indexCount = div * 3;

	// 정점 배열을 만듭니다.
	VertexType* vertices = new VertexType[m_vertexCount];
	if(!vertices)
	{
		return false;
	}

	// 인덱스 배열을 만듭니다.
	unsigned long* indices = new unsigned long[m_indexCount];
	if(!indices)
	{
		return false;
	}

	vertices[0].position = XMFLOAT3(0, 0, 0);
	vertices[0].color = m_color;
	double pi = acos(-1);

	for (int i = 1; i < m_vertexCount; i++) {
		double angle = (2*pi / div) * i;
		vertices[i].position = XMFLOAT3(cos(-angle), sin(-angle), 0);
		vertices[i].color = m_color;

		indices[(i-1)*3] = 0;
		indices[(i-1)*3 + 1] = i;
		indices[(i-1)*3 + 2] = i + 1;
	}
	indices[m_indexCount - 1] = 1;
	
	/*

	// 정점 배열에 데이터를 설정합니다.
	vertices[0].position = XMFLOAT3(-1.0f+moveX, -1.0f, 0.0f);  // Bottom left.
	vertices[0].color = m_color;

	vertices[1].position = XMFLOAT3(0.0f+moveX, 1.0f, 0.0f);  // Top middle.
	vertices[1].color = m_color;

	vertices[2].position = XMFLOAT3(1.0f+moveX, -1.0f, 0.0f);  // Bottom right.
	vertices[2].color = m_color;

	// 인덱스 배열의 값을 설정합니다.
	indices[0] = 0;  // Bottom left.
	indices[1] = 1;  // Top middle.
	indices[2] = 2;  // Bottom right.
	*/


	// 정적 정점 버퍼의 구조체를 설정합니다.
	D3D11_BUFFER_DESC vertexBufferDesc;
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// subresource 구조에 정점 데이터에 대한 포인터를 제공합니다.
	D3D11_SUBRESOURCE_DATA vertexData;
    vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// 이제 정점 버퍼를 만듭니다.
	if(FAILED(device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer)))
	{
		return false;
	}

	// 정적 인덱스 버퍼의 구조체를 설정합니다.
	D3D11_BUFFER_DESC indexBufferDesc;
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// 인덱스 데이터를 가리키는 보조 리소스 구조체를 작성합니다.
	D3D11_SUBRESOURCE_DATA indexData;
    indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// 인덱스 버퍼를 생성합니다.
	if(FAILED(device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer)))
	{
		return false;
	}

	// 생성되고 값이 할당된 정점 버퍼와 인덱스 버퍼를 해제합니다.
	delete [] vertices;
	vertices = 0;

	delete [] indices;
	indices = 0;

	return true;
}


void ModelClass::ShutdownBuffers()
{
	// 인덱스 버퍼를 해제합니다.
	if(m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// 정점 버퍼를 해제합니다.
	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}
}


void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	// 정점 버퍼의 단위와 오프셋을 설정합니다.
	unsigned int stride = sizeof(VertexType); 
	unsigned int offset = 0;
    
	// 렌더링 할 수 있도록 입력 어셈블러에서 정점 버퍼를 활성으로 설정합니다.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

    // 렌더링 할 수 있도록 입력 어셈블러에서 인덱스 버퍼를 활성으로 설정합니다.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // 정점 버퍼로 그릴 기본형을 설정합니다. 여기서는 삼각형으로 설정합니다.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}