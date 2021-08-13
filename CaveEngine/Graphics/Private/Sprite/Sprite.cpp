/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Sprite/Sprite.h"

namespace cave
{
	Sprite::Sprite(Texture* texture)
		: mTexture(texture)
	{
		mWidth = mTexture->GetWidth();
		mHeight = mTexture->GetHeight();
		mTextureIndex = mTexture->GetIndex();
	}


	Sprite::Sprite(const Sprite& other)
		: mWorld(other.mWorld)
		, mTextureIndex(other.mTextureIndex)
		, mWidth(other.mWidth)
		, mHeight(other.mHeight)
		, mPosition(other.mPosition)
	{
		mTexture = other.mTexture;
		/*if (other.mTexture != nullptr)
		{
			mTexture = reinterpret_cast<Texture*>(mPool->Allocate(sizeof(Texture)));
			new(mTexture) Texture(*other.mTexture);
		}*/
	}

	Sprite::Sprite(Sprite&& other)
		: mWorld(other.mWorld)
		, mTextureIndex(other.mTextureIndex)
		, mTexture(other.mTexture)
		, mPosition(other.mPosition)
		, mWidth(other.mWidth)
		, mHeight(other.mHeight)
	{
		other.mTexture = nullptr;
	}

	Sprite& Sprite::operator=(const Sprite& other)
	{
		if (this != &other)
		{
			mWorld = other.mWorld;
			mTextureIndex = other.mTextureIndex;

			//mTexture->~Texture();
			//if (other.mTexture != nullptr)
			//{
			//	new(mTexture) Texture(*other.mTexture);
			//}
			//else
			//{
			//	mPool->Deallocate(mTexture, sizeof(Texture));
			//	mTexture = nullptr;
			//}
			mTexture = other.mTexture;

			mPosition = other.mPosition;
			mWidth = other.mWidth;
			mHeight = other.mHeight;
		}

		return *this;
	}

	Sprite& Sprite::operator=(Sprite&& other)
	{
		if (this != &other)
		{
			mWorld = other.mWorld;
			mTextureIndex = other.mTextureIndex;

			mTexture = other.mTexture;

			mPosition = other.mPosition;

			mWidth = other.mWidth;
			mHeight = other.mHeight;
			other.mTexture = nullptr;
		}

		return *this;
	}

	Sprite::~Sprite()
	{
		Destroy();
	}

	eResult Sprite::Init(ID3D11Device* device, ID3D11DeviceContext* context, uint32_t screenWidth, uint32_t screenHeight)
	{
		mScreenWidth = screenWidth;
		mScreenHeight = screenHeight;

		mPreviousPosition = Float3(-1.0f, -1.0f, 1.0f);
		//mPosition = Float3(0.0f, 0.0f, 1.0f);

		eResult result = initializeBuffers(device, context);

		return result;
	}

	void Sprite::Destroy()
	{
		if (mTexture != nullptr)
		{
			mTexture->~Texture(); //
			mTexture = nullptr;
		}

		if (mTextureRv != nullptr)
		{
			mTextureRv->Release();
			mTextureRv = nullptr;
		}
		if (mVertexBuffer != nullptr)
		{
			mVertexBuffer->Release();
			mVertexBuffer = nullptr;
		}
		if (mIndexBuffer != nullptr)
		{
			mIndexBuffer->Release();
			mIndexBuffer = nullptr;
		}
		if (mVertexLayout != nullptr)
		{
			mVertexLayout->Release();
			mVertexLayout = nullptr;
		}

	}
	void Sprite::Update()
	{
	}

	void Sprite::SetTexture(const Texture& texture)
	{
		if (mTexture != nullptr)
		{
			mTexture->~Texture();
			mTexture = nullptr;
		}
		*mTexture = texture;
	}
	void Sprite::SetTextureIndex(Texture* texture, uint32_t index)
	{
		mWidth = texture->GetWidth();
		mHeight = texture->GetHeight();
		mTexture = texture;
		mTextureIndex = index;
	}

	eResult Sprite::initializeBuffers(ID3D11Device* device, ID3D11DeviceContext* context)
	{
		assert(device != nullptr && context != nullptr);

		int32_t result = S_OK;

		// create static vertex buffer
	// 정적 정점 버퍼의 구조체를 설정합니다.
		D3D11_BUFFER_DESC vertexBufferDesc;
		vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		vertexBufferDesc.ByteWidth = sizeof(VertexT) * VERTICES_COUNT;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		vertexBufferDesc.MiscFlags = 0;
		vertexBufferDesc.StructureByteStride = 0;

		// subresource 구조에 정점 데이터에 대한 포인터를 제공합니다.
		D3D11_SUBRESOURCE_DATA vertexData;
		vertexData.pSysMem = mVertices;
		vertexData.SysMemPitch = 0;
		vertexData.SysMemSlicePitch = 0;
		result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &mVertexBuffer);
		if (FAILED(result))
		{
			return eResult::CAVE_FAIL;
		}


		// 정적 인덱스 버퍼의 구조체를 설정합니다.
		D3D11_BUFFER_DESC indexBufferDesc;
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = sizeof(WORD) * INDICES_COUNT;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.MiscFlags = 0;
		indexBufferDesc.StructureByteStride = 0;

		// 인덱스 데이터를 가리키는 보조 리소스 구조체를 작성합니다.
		D3D11_SUBRESOURCE_DATA indexData;
		indexData.pSysMem = INDICES;
		indexData.SysMemPitch = 0;
		indexData.SysMemSlicePitch = 0;

		result = device->CreateBuffer(&indexBufferDesc, &indexData, &mIndexBuffer);
		if (FAILED(result))
		{
			return eResult::CAVE_FAIL;
		}

		mWorld = DirectX::XMMatrixIdentity();

		return eResult::CAVE_OK;
	}

	void Sprite::Render(ID3D11DeviceContext* context)
	{

		float left = 0.0f;
		float right = 0.0f;
		float top = 0.0f;
		float bottom = 0.0f;
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		VertexT* verticesPtr = nullptr;
		eResult result = eResult::CAVE_OK;

		if (!mbNeedsUpdate && (mPosition == mPreviousPosition))
		{
			return;
		}

		mPreviousPosition = mPosition;

		left = static_cast<float>(mScreenWidth / 2) * -1 + mPosition.X - static_cast<float>(mWidth) / 2.0f;
		right = left + static_cast<float>(mWidth);
		top = static_cast<float>(mScreenHeight / 2) - mPosition.Y + static_cast<float>(mHeight) / 2.0f;
		bottom = top - static_cast<float>(mHeight);

		mVertices[0] = std::move(VertexT(Float3(left, top, mPosition.Z), Float2(mTexture->GetStartUV().X, mTexture->GetStartUV().Y)));		// top left
		mVertices[1] = std::move(VertexT(Float3(right, top, mPosition.Z), Float2(mTexture->GetEndUV().X, mTexture->GetStartUV().Y)));	// top right
		mVertices[2] = std::move(VertexT(Float3(right, bottom, mPosition.Z), Float2(mTexture->GetEndUV().X, mTexture->GetEndUV().Y)));		// bottom right
		mVertices[3] = std::move(VertexT(Float3(left, bottom, mPosition.Z), Float2(mTexture->GetStartUV().X, mTexture->GetEndUV().Y)));		// bottom left


		//flipX 
		//mVertices[0] = std::move(VertexT(Float3(left, top, mPosition.Z), Float2(mTexture->GetEndUV().X, mTexture->GetStartUV().Y)));		// top left
		//mVertices[1] = std::move(VertexT(Float3(right, top, mPosition.Z), Float2(mTexture->GetStartUV().X, mTexture->GetStartUV().Y)));	// top right
		//mVertices[2] = std::move(VertexT(Float3(right, bottom, mPosition.Z), Float2(mTexture->GetStartUV().X, mTexture->GetEndUV().Y)));		// bottom right
		//mVertices[3] = std::move(VertexT(Float3(left, bottom, mPosition.Z), Float2(mTexture->GetEndUV().X, mTexture->GetEndUV().Y)));		// bottom left

		HRESULT hResult = context->Map(mVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if (FAILED(result)) {
			return;
		}
		verticesPtr = reinterpret_cast<VertexT*>(mappedResource.pData);

		memcpy(verticesPtr, reinterpret_cast<void*>(mVertices), (sizeof(VertexT) * VERTICES_COUNT));

		context->Unmap(mVertexBuffer, 0);

		// ���� context�� �����ֱ�
		// Set vertex buffer
		uint32_t stride = sizeof(VertexT);
		uint32_t offset = 0;
		context->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);

		// Set index buffer
		context->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R16_UINT, 0); // WORD -> 16

		// Set primitive topology
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
} // namespace cave
