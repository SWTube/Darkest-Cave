module;
#include <fstream>
#include <filesystem>
#include <vector>
#include <CoreGlobals.h>
#include <GraphicsApiPch.h>
#include "Debug/Log.h"

export module cave.Graphics.TileMap.TileMap;

import cave.Core.Types.Float;
import cave.Core.Types.Vertex;
import Renderable;
import cave.Graphics.TileMap.Tile;
import cave.Graphics.TileMap.TileSet;
import Texture;
import MultiTexture;
import TextureManager;
import cave.Graphics.TileMap.TileManager;

namespace cave
{

	export class TileMap : public Renderable
	{
	public:
		TileMap() = delete;
		TileMap(uint16_t mapSizeX, uint16_t mapSizeY, uint16_t cellSize = 32u);// 정사각형이라고 가정.
		~TileMap();

		void SetCell(uint16_t i, uint16_t j, uint16_t tileId);
		void LoadMap(const std::filesystem::path& filePath);
		void ResetMap();
		constexpr uint32_t GetMapSize();
		Texture* GetTileTexture();

	protected:
		friend class Renderer;
		void init(DeviceResources* deviceResource);
		bool initBuffer(ID3D11Device* device);
		void render(ID3D11DeviceContext* deviceContext);
		void updateBuffer(ID3D11DeviceContext* deviceContext);
		void renderBuffer(ID3D11DeviceContext* deviceContext);

		virtual void update(){};
		virtual void creatRenderCommand() {};
		virtual void makeRenderCommand() {};

	private:
		uint16_t mCellSize = 0u;
		uint16_t mMapSizeX = 0u;
		uint16_t mMapSizeY = 0u;
		uint16_t** mTileMap = nullptr;

		static constexpr uint32_t VERTICES_COUNT = 4u;
		static constexpr uint32_t INDICES_COUNT = 6u;

		std::vector<VertexTC> mVertices;

		ID3D11Buffer* mVertexBuffer = nullptr;
		ID3D11Buffer* mIndexBuffer = nullptr;

		bool mbNeedUpdate = false;
	};

	constexpr uint32_t TileMap::GetMapSize()
	{
		return mMapSizeX * mMapSizeY;
	}
	Texture* TileMap::GetTileTexture()
	{
		Tile* t = TileManager::GetInstance().GetTile(1);
		if (t) return t->texture;
		else return nullptr;
	}
	TileMap::TileMap(uint16_t mapSizeX, uint16_t mapSizeY, uint16_t cellSize)
		:mCellSize(cellSize),
		mMapSizeX(mapSizeX),
		mMapSizeY(mapSizeY)
	{

		/*
		(0,0) , (0,1) , ...
		(1,0) , (1,1) , ...
		...
		...             (n,n)
		*/
		mTileMap = reinterpret_cast<uint16_t**>(gCoreMemoryPool.Allocate(sizeof(uint16_t*) * mMapSizeY));
		new(mTileMap) uint16_t*[mapSizeY];

		for (size_t i = 0; i < mMapSizeY; i++)
		{
			mTileMap[i] = reinterpret_cast<uint16_t*>(gCoreMemoryPool.Allocate(sizeof(uint16_t) * mMapSizeX));
			new(mTileMap) uint16_t[mMapSizeX];
		}

		for (size_t i = 0; i < mMapSizeY; i++)
		{
			for (int j = 0; j < mMapSizeX; j++)
			{
				mTileMap[i][j] = 0u;
			}
		}


	}

	TileMap::~TileMap()
	{
		for (size_t i = 0; i < mMapSizeY; i++)
		{
			gCoreMemoryPool.Deallocate(mTileMap[i],sizeof(uint16_t) * mMapSizeX);
		}

		gCoreMemoryPool.Deallocate(mTileMap, sizeof(uint16_t*) * mMapSizeY);
		
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
	}


	void TileMap::SetCell(uint16_t i, uint16_t j, uint16_t tileId)
	{
		assert( (i < mMapSizeX) && (j < mMapSizeY) );
		mTileMap[i][j] = tileId;

		Tile* tile = TileManager::GetInstance().GetTile(tileId);

		float posX = mPosition.X + j * mCellSize;
		float posY = mPosition.Y - i * mCellSize;
		float left = posX;
		float right = left + mCellSize;
		float top = posY;
		float bottom = top - mCellSize;
		Float4 mColor = { 1.0f,1.0f,1.0f,1.0f};
		uint16_t index = i * mMapSizeX*4 + j*4;
		mVertices[index] = std::move(VertexTC(Float3(left, top, mPosition.Z),
			tile->startTexCoords,
			mColor));		// top left

		mVertices[index+1u] = std::move(VertexTC(Float3(right, top, mPosition.Z),
			Float2(tile->endTexCoords.X, tile->startTexCoords.Y),
			mColor));	// top right

		mVertices[index +2u] = std::move(VertexTC(Float3(right, bottom, mPosition.Z),
			tile->endTexCoords,
			mColor));		// bottom right

		mVertices[index+3u] = std::move(VertexTC(Float3(left, bottom, mPosition.Z),
			Float2(tile->startTexCoords.X, tile->endTexCoords.Y),
			mColor));		// bottom left
	
		mbNeedUpdate = true;
	}

	void TileMap::LoadMap(const std::filesystem::path& filePath)
	{
		std::ifstream mapFile(filePath);
		//mapFile.open(filePath.string());
		size_t i = 0;
		size_t j = 0;

		if (mapFile.is_open())
		{
			int temp;
			while (!mapFile.eof())
			{
				mapFile >> temp;
				if (temp == -2)
				{
					i++;
					j = 0;
					continue;
				}
				if (temp == -1)
				{
					temp = 1;
				}

				if (temp > 0)
				{
					SetCell(i,j,static_cast<uint16_t>(temp));
					j++;
				}
				
			}
		}

		mapFile.close();
		mbNeedUpdate = true;
	}
	void TileMap::ResetMap()
	{

	}

	void TileMap::init(DeviceResources* deviceResource)
	{
		initBuffer(deviceResource->GetDevice());
	}

	bool TileMap::initBuffer(ID3D11Device* device)
	{
		mVertices.resize(mMapSizeX * mMapSizeY * 4);

		uint32_t buffersize = mMapSizeX * mMapSizeY;

		D3D11_BUFFER_DESC vertexBufferDesc;
		vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		vertexBufferDesc.ByteWidth = sizeof(VertexTC) * VERTICES_COUNT * buffersize;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		vertexBufferDesc.MiscFlags = 0;
		vertexBufferDesc.StructureByteStride = 0;

		// subresource 구조에 정점 데이터에 대한 포인터를 제공합니다.
		D3D11_SUBRESOURCE_DATA vertexData;
		vertexData.pSysMem = mVertices.data();
		vertexData.SysMemPitch = 0;
		vertexData.SysMemSlicePitch = 0;

		// 이제 정점 버퍼를 만듭니다.
		if (FAILED(device->CreateBuffer(&vertexBufferDesc, &vertexData, &mVertexBuffer)))
		{
			return false;
		}

		D3D11_BUFFER_DESC indexBufferDesc;
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = sizeof(WORD) * INDICES_COUNT * buffersize;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.MiscFlags = 0;
		indexBufferDesc.StructureByteStride = 0;
		
		std::vector<WORD> indices;
		indices.reserve(INDICES_COUNT * buffersize);

		for (size_t j = 0; j < buffersize * 4; j += 4)
		{
			WORD i = static_cast<WORD>(j);

			indices.push_back(i);
			indices.push_back(i + 1);
			indices.push_back(i + 2);

			indices.push_back(i + 2);
			indices.push_back(i + 3);
			indices.push_back(i);
		}

		// 인덱스 데이터를 가리키는 보조 리소스 구조체를 작성합니다.
		D3D11_SUBRESOURCE_DATA indexData;
		indexData.pSysMem = indices.data();
		indexData.SysMemPitch = 0;
		indexData.SysMemSlicePitch = 0;

		// 인덱스 버퍼를 생성합니다.
		if (FAILED(device->CreateBuffer(&indexBufferDesc, &indexData, &mIndexBuffer)))
		{
			return false;
		}
	}

	void TileMap::updateBuffer(ID3D11DeviceContext* deviceContext)
	{
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		VertexTC* verticesPtr;

		deviceContext->Map(mVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		verticesPtr = reinterpret_cast<VertexTC*>(mappedResource.pData);
		memcpy(verticesPtr, reinterpret_cast<void*>(mVertices.data()), (sizeof(VertexTC) * VERTICES_COUNT * mMapSizeX * mMapSizeY));
		deviceContext->Unmap(mVertexBuffer, 0);
	}

	void TileMap::render(ID3D11DeviceContext* deviceContext)
	{
		if (mbNeedUpdate)
		{
			updateBuffer(deviceContext);
		}
		renderBuffer(deviceContext);
	}

	void TileMap::renderBuffer(ID3D11DeviceContext* deviceContext)
	{
		// 정점 버퍼의 단위와 오프셋을 설정합니다.
		UINT stride = sizeof(VertexTC);
		UINT offset = 0;

		// 렌더링 할 수 있도록 입력 어셈블러에서 정점 버퍼를 활성으로 설정합니다.
		deviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);

		// 렌더링 할 수 있도록 입력 어셈블러에서 인덱스 버퍼를 활성으로 설정합니다.
		deviceContext->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

		// 정점 버퍼로 그릴 기본형을 설정합니다. 여기서는 삼각형으로 설정합니다.
		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
}