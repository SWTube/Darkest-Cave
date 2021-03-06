﻿/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#ifdef __WIN32__
import DdsTextureLoader;

#include "Sprite/WindowsSprite.h"

namespace cave
{
	WindowsSprite::WindowsSprite(Texture* texture)
		: GenericSprite(texture)
	{
	}
	
	//WindowsSprite::WindowsSprite(const Texture& texture, MemoryPool& pool)
	//	: GenericSprite(texture, pool)
	//{
	//}

	//WindowsSprite::WindowsSprite(Texture&& texture, MemoryPool& pool)
	//	: GenericSprite(std::move(texture), pool)
	//{
	//}

	WindowsSprite::WindowsSprite(const WindowsSprite& other)
		: GenericSprite(other)
		, mVertexBuffer(other.mVertexBuffer)
		, mIndexBuffer(other.mIndexBuffer)
		, mVertexLayout(other.mVertexLayout)
		, mTextureRv(other.mTextureRv)
	{
	}

	WindowsSprite::WindowsSprite(WindowsSprite&& other)
		: GenericSprite(std::move(other))
	{
		mVertexBuffer = other.mVertexBuffer;
		mIndexBuffer = other.mIndexBuffer;
		mVertexLayout = other.mVertexLayout;
		mTextureRv = other.mTextureRv;

		other.Destroy();
	}

	WindowsSprite& WindowsSprite::operator=(const WindowsSprite& other)
	{
		if (this != &other)
		{
			GenericSprite::operator=(other);
			mVertexBuffer = other.mVertexBuffer;
			mIndexBuffer = other.mIndexBuffer;
			mVertexLayout = other.mVertexLayout;
			mTextureRv = other.mTextureRv;
		}

		return *this;
	}

	WindowsSprite& WindowsSprite::operator=(WindowsSprite&& other)
	{
		if (this != &other)
		{
			GenericSprite::operator=(std::move(other));
			mVertexBuffer = other.mVertexBuffer;
			mIndexBuffer = other.mIndexBuffer;
			mVertexLayout = other.mVertexLayout;
			mTextureRv = other.mTextureRv;

			other.Destroy();
		}

		return *this;
	}

	WindowsSprite::~WindowsSprite()
	{
		Destroy();
	}

	eResult WindowsSprite::initializeBuffers(ID3D11Device* device, ID3D11DeviceContext* context)
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
		if(FAILED(result))
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
		if(FAILED(result))
		{
			return eResult::CAVE_FAIL;
		}

		mWorld = DirectX::XMMatrixIdentity();

		return eResult::CAVE_OK;
	}

	void WindowsSprite::Destroy()
	{
		GenericSprite::Destroy();
		
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

	void WindowsSprite::Update()
	{

	}

	void WindowsSprite::Render(ID3D11DeviceContext* context)
	{
		//
		// Update variables for the first cube
		//
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

		mVertices[0] = std::move(VertexT(Float3( left,    top, mPosition.Z), Float2(mTexture->GetStartUV().X, mTexture->GetStartUV().Y)));		// top left
		mVertices[1] = std::move(VertexT(Float3( right,    top, mPosition.Z), Float2(mTexture->GetEndUV().X, mTexture->GetStartUV().Y)));	// top right
		mVertices[2] = std::move(VertexT(Float3(right, bottom, mPosition.Z), Float2(mTexture->GetEndUV().X, mTexture->GetEndUV().Y)));		// bottom right
		mVertices[3] = std::move(VertexT(Float3( left, bottom, mPosition.Z), Float2(mTexture->GetStartUV().X, mTexture->GetEndUV().Y)));		// bottom left

		//float textureStart = mFrame * mDividedTexture;
		//mVertices[0].position = DirectX::XMFLOAT3(left, top, 0.0f);  // Top left.
		//mVertices[0].texture = DirectX::XMFLOAT2(mTexture->GetStartUV().X, mTexture->GetStartUV().Y);

		//mVertices[1].position = DirectX::XMFLOAT3(right, top, 0.0f);  // Top right.
		//mVertices[1].texture = DirectX::XMFLOAT2(mTexture->GetEndUV().X, mTexture->GetStartUV().Y);

		//mVertices[2].position = DirectX::XMFLOAT3(right, bottom, 0.0f);  // bottom right.
		//mVertices[2].texture = DirectX::XMFLOAT2(mTexture->GetEndUV().X, mTexture->GetEndUV().Y);

		//mVertices[3].position = DirectX::XMFLOAT3(left, bottom, 0.0f);  // bottom left.
		//mVertices[3].texture = DirectX::XMFLOAT2(mTexture->GetStartUV().X, mTexture->GetEndUV().Y);

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
	void WindowsSprite::SetMultiSprite(int frameCount, int framesPerSecond)
	{
		//mbIsMultiSprite = true;
		//mFrameCount = frameCount;
		//mTimePerFrame = 1.0f / float(framesPerSecond);
		//mDividedTexture = 1.0f / float(mFrameCount);
		//tempElapsed = 0.01f;
	}
} // namespace cave

#endif