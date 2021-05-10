/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Sprite/WindowsSprite.h"

#ifdef __WIN32__
import DdsTextureLoader;

namespace cave
{
	WindowsSprite::WindowsSprite(Texture* texture, MemoryPool& pool)
		: GenericSprite(texture, pool)
	{
	}

	WindowsSprite::WindowsSprite(const Texture& texture, MemoryPool& pool)
		: GenericSprite(texture, pool)
	{
	}

	WindowsSprite::WindowsSprite(Texture&& texture, MemoryPool& pool)
		: GenericSprite(std::move(texture), pool)
	{
	}

	WindowsSprite::WindowsSprite(const WindowsSprite& other)
		: GenericSprite(other)
		, mDevice(other.mDevice)
		, mContext(other.mContext)
		, mVertexBuffer(other.mVertexBuffer)
		, mIndexBuffer(other.mIndexBuffer)
		, mVertexLayout(other.mVertexLayout)
		, mConstantBuffer(other.mConstantBuffer)
		, mTextureRv(other.mTextureRv)
		, mSamplerLinear(other.mSamplerLinear)
	{
	}

	WindowsSprite::WindowsSprite(WindowsSprite&& other)
		: GenericSprite(std::move(other))
	{
		mDevice = other.mDevice;
		mContext = other.mContext;
		mVertexBuffer = other.mVertexBuffer;
		mIndexBuffer = other.mIndexBuffer;
		mVertexLayout = other.mVertexLayout;
		mConstantBuffer = other.mConstantBuffer;
		mTextureRv = other.mTextureRv;
		mSamplerLinear = other.mSamplerLinear;

		other.Destroy();
	}

	WindowsSprite& WindowsSprite::operator=(const WindowsSprite& other)
	{
		if (this != &other)
		{
			GenericSprite::operator=(other);
			mDevice = other.mDevice;
			mContext = other.mContext;
			mVertexBuffer = other.mVertexBuffer;
			mIndexBuffer = other.mIndexBuffer;
			mVertexLayout = other.mVertexLayout;
			mConstantBuffer = other.mConstantBuffer;
			mTextureRv = other.mTextureRv;
			mSamplerLinear = other.mSamplerLinear;
		}

		return *this;
	}

	WindowsSprite& WindowsSprite::operator=(WindowsSprite&& other)
	{
		if (this != &other)
		{
			GenericSprite::operator=(std::move(other));
			mDevice = other.mDevice;
			mContext = other.mContext;
			mVertexBuffer = other.mVertexBuffer;
			mIndexBuffer = other.mIndexBuffer;
			mVertexLayout = other.mVertexLayout;
			mConstantBuffer = other.mConstantBuffer;
			mTextureRv = other.mTextureRv;
			mSamplerLinear = other.mSamplerLinear;

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
		mDevice = device;
		mContext = context;
		int32_t result = S_OK;

		D3D11_BUFFER_DESC bd = {};
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTICES);
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData = {};
		InitData.pSysMem = VERTICES;
		result = device->CreateBuffer(&bd, &InitData, &mVertexBuffer);
		if(FAILED(result))
		{
			return eResult::CAVE_FAIL;
		}

		// ���� context�� �����ֱ�
		// Set vertex buffer
		uint32_t stride = sizeof(VertexT);
		uint32_t offset = 0;
		mContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);

		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(INDICES);
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		InitData.pSysMem = INDICES;
		result = device->CreateBuffer(&bd, &InitData, &mIndexBuffer);
		if(FAILED(result))
		{
			return eResult::CAVE_FAIL;
		}

		// Set index buffer
		mContext->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

		// Set primitive topology
		mContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// 12. Define, create, set the input layout ---------------------------------------------------------------------------------------------

		// Preparing to Send Data to OpenGL
		// All data must be stored in buffer objects (chunks of memory managed by OpenGL)
		// Common way is to specify the data at the same time as you specify the buffer's size

		// 16. Load Textures ---------------------------------------------------------------------------------------------
		/*uint32_t error = lodepng_decode24_file(&mTextureData, &mTextureWidth, &mTextureHeight, mTextureFilePath);
		if (error != 0)
		{
			LOGEF(eLogChannel::GRAPHICS, "The png file %s cannot be loaded. Error Code: %u", mTextureFilePath, error);
			return eResult::CAVE_FAIL;
		}

		free(mTextureData);
		mTextureData = nullptr;*/


		// Create the constant buffers
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(ConstantBuffer);
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;
		result = mDevice->CreateBuffer(&bd, nullptr, &mConstantBuffer);
		if (FAILED(result))
		{
			return static_cast<eResult>(result);
		}

		// Load the Texture
		result = DdsTextureLoader::CreateDDSTextureFromFile(device, L"Graphics/Resource/seafloor.dds", nullptr, &mTextureRv);
		if (FAILED(result))
		{
			return static_cast<eResult>(result);
		}

		// Create the sample state
		D3D11_SAMPLER_DESC sampDesc = {};
		sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		sampDesc.MinLOD = 0;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
		result = mDevice->CreateSamplerState(&sampDesc, &mSamplerLinear);
		if (FAILED(result))
		{
			return static_cast<eResult>(result);
		}

		mWorld = DirectX::XMMatrixIdentity();

		return eResult::CAVE_OK;
	}

	eResult WindowsSprite::SetInputLayout(ID3DBlob* vsBlob)
	{
		// Define the input layout
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(Float3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		UINT numElements = ARRAYSIZE(layout);

		// Create the input layout
		int32_t result = mDevice->CreateInputLayout(layout, numElements, vsBlob->GetBufferPointer(),
			vsBlob->GetBufferSize(), &mVertexLayout);
		vsBlob->Release();
		if (FAILED(result))
		{
			return eResult::CAVE_FAIL;
		}

		// Set the input layout
		mContext->IASetInputLayout(mVertexLayout);
	}

	void WindowsSprite::Destroy()
	{
		GeneralSprite::Destroy();
		
		if (mSamplerLinear != nullptr)
		{
			mSamplerLinear->Release();
			mSamplerLinear = nullptr;
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
		if (mConstantBuffer)
		{
			mConstantBuffer->Release();
			mConstantBuffer = nullptr;
		}
		if (mContext != nullptr)
		{
			mContext->Release();
			mContext = nullptr;
		}
		if (mDevice != nullptr)
		{
			mDevice->Release();
			mDevice = nullptr;
		}
	}

	void WindowsSprite::Update()
	{
	}

	void WindowsSprite::Render()
	{
		//
		// Update variables for the first cube
		//
		ConstantBuffer constantBuffer;
		constantBuffer.mWorld = DirectX::XMMatrixTranspose(mWorld);
		mContext->UpdateSubresource(mConstantBuffer, 0, nullptr, &constantBuffer, 0, 0);

		// ���� context�� �����ֱ�
		// Set vertex buffer
		uint32_t stride = sizeof(VertexT);
		uint32_t offset = 0;
		mContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);

		// Set index buffer
		mContext->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

		// Set primitive topology
		mContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// IA. Input Assembly
		// Set the input layout
		mContext->IASetInputLayout(mVertexLayout);

		//
		// Render the first cube
		//
		mContext->VSSetConstantBuffers(0, 1, &mConstantBuffer);
		mContext->PSSetConstantBuffers(0, 1, &mConstantBuffer);
		mContext->PSSetShaderResources(0, 1, &mTextureRv);
		mContext->PSSetSamplers(0, 1, &mSamplerLinear);

		// ���� production level���� Draw���ٴ� DrawIndexed�� �� ���� ���
		// ù��°�� ���ؽ� ����. 3
		// back buffer�� �׸���
		//context->Draw(3, 0);
		mContext->DrawIndexed(INDICES_COUNT, 0, 0);        // 36 vertices needed for 12 triangles in a triangle list
	}
} // namespace cave

#endif