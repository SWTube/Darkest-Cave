/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
module;

#include "GraphicsApiPch.h"
#include <vector>
#include "CoreTypes.h"
#include "Memory/MemoryPool.h"

export module BufferManager;

import cave.Core.Types.Vertex;
import DeviceResources;

namespace cave {
	export class BufferManager 
	{
	public:
		BufferManager() = default;
		BufferManager(const BufferManager& other) = delete;
		BufferManager& operator=(const BufferManager&) = delete;
		BufferManager& operator=(const BufferManager&&) = delete;
		eResult Init(DeviceResources* deviceResources, uint32_t vertexPoolSize);
		void UpdateVertexBuffer(VertexT* vertexData, WORD spriteCount);
		virtual ~BufferManager();
		void Destroy();

	private:
	
		uint32_t mPoolSize = 0;

		ID3D11Buffer* mVertexBufferPool = nullptr;
		ID3D11Buffer* mIndexBufferPool = nullptr;
		
		DeviceResources* mDeviceResources = nullptr;
	};

	eResult BufferManager::Init(DeviceResources* deviceResources, uint32_t poolSize)
	{
		mDeviceResources = deviceResources;
		mPoolSize = poolSize;
		int32_t result;
		
		//vertex buffer pool 持失.
		D3D11_BUFFER_DESC vertexBufferDesc;
		vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		vertexBufferDesc.ByteWidth = sizeof(VertexT) * mPoolSize * 4;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		vertexBufferDesc.MiscFlags = 0;
		vertexBufferDesc.StructureByteStride = 0;

		result = deviceResources->GetDevice()->CreateBuffer(&vertexBufferDesc, nullptr, &mVertexBufferPool);

		if (FAILED(result)) {
			return eResult::CAVE_FAIL;
		}

		//index buffer pool 持失.
		D3D11_BUFFER_DESC indexBufferDesc;
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = sizeof(WORD) * mPoolSize * 6;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.MiscFlags = 0;
		indexBufferDesc.StructureByteStride = 0;
		
		std::vector<WORD> indexData;
		indexData.reserve(mPoolSize * 6);
		
		for (size_t j = 0; j < mPoolSize * 4; j += 4)
		{
			WORD i = static_cast<WORD>(j);

			indexData.push_back(i);
			indexData.push_back(i + 1);
			indexData.push_back(i + 2);

			indexData.push_back(i + 2);
			indexData.push_back(i + 3);
			indexData.push_back(i);
		}

		D3D11_SUBRESOURCE_DATA indexDataDesc;

		indexDataDesc.pSysMem = indexData.data();
		indexDataDesc.SysMemPitch = 0;
		indexDataDesc.SysMemSlicePitch = 0;

		result = deviceResources->GetDevice()->CreateBuffer(&indexBufferDesc,&indexDataDesc, &mIndexBufferPool);

		if (FAILED(result)) {
			return eResult::CAVE_FAIL;
		}

		return eResult::CAVE_OK;
	}
	BufferManager::~BufferManager()
	{
		Destroy();
	}

	void BufferManager::Destroy()
	{
		if (mVertexBufferPool != nullptr)
		{
			mVertexBufferPool->Release();
			mVertexBufferPool = nullptr;
		}
		if (mIndexBufferPool != nullptr)
		{
			mIndexBufferPool->Release();
			mIndexBufferPool = nullptr;
		}
		
	}

	void BufferManager::UpdateVertexBuffer(VertexT* vertexData, WORD spriteCount) 
	{
		VertexT* verticesPtr = nullptr;
		
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		HRESULT hResult = mDeviceResources->GetDeviceContext()->Map(mVertexBufferPool, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

		verticesPtr = reinterpret_cast<VertexT*>(mappedResource.pData);
		memcpy(verticesPtr, reinterpret_cast<void*>(vertexData), (sizeof(VertexT) * 4 * spriteCount));
		mDeviceResources->GetDeviceContext()->Unmap(mVertexBufferPool, 0);

		uint32_t stride = sizeof(VertexT);
		uint32_t offset = 0;
		mDeviceResources->GetDeviceContext()->IASetVertexBuffers(0, 1, &mVertexBufferPool, &stride, &offset);
		mDeviceResources->GetDeviceContext()->IASetIndexBuffer(mIndexBufferPool, DXGI_FORMAT_R16_UINT, 0);
		mDeviceResources->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	}

}