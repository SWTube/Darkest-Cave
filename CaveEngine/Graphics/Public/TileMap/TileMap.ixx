module;
#include <fstream>
#include <filesystem>
#include <vector>
#include <unordered_map>
#include <CoreGlobals.h>
#include <GraphicsApiPch.h>
#include "Debug/Log.h"

export module cave.Graphics.TileMap.TileMap;

import cave.Core.Types.Float;
import cave.Core.Types.Vertex;
import cave.Core.Containers.HashTable;
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
		struct UsedTextureInfo
		{
			uint32_t count = 0u; //몇 개가 사용하고 있는지
			Texture* texture = nullptr;
		};

	public:
		TileMap() = delete;
		TileMap(uint16_t mapSizeX, uint16_t mapSizeY, uint16_t cellSize = 32u);// 정사각형이라고 가정.
		~TileMap();

		void SetTile(uint16_t i, uint16_t j, uint16_t tileId);

		void SetTiles(uint16_t i, uint16_t j, TileGroup tiles);
		/*
		맵 전체를 주어진 타일로 채운다.
		*/
		void FillMap(uint16_t tileId);
		/*
		* 주어진 범위를 주어진 타일로 채운다.
		*/
		void FillMap(uint16_t tileId, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom);

		
		void FillMapWithTileGroup(TileGroup tiles, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom,uint16_t spacingX = 0u, uint16_t spacingY =0u);

		void LoadMap(const std::filesystem::path& filePath);
		void ResetMap();
		constexpr uint16_t GetMapSizeX();
		constexpr uint16_t GetMapSizeY();
		constexpr uint32_t GetMapSize();
		Texture* GetTileTexture(uint16_t i, uint16_t j);

	protected:
		friend class Renderer;
		void init(DeviceResources* deviceResource);
		bool initBuffer(ID3D11Device* device);
		void render(ID3D11DeviceContext* deviceContext);
		void updateBuffer(ID3D11DeviceContext* deviceContext);
		void renderBuffer(ID3D11DeviceContext* deviceContext);

		const std::vector<TileMap::UsedTextureInfo> GetUsedTexture() const;

		virtual void update() {};
		virtual void creatRenderCommand() {};
		virtual void makeRenderCommand() {};

	private:
		uint16_t mCellSize = 0u;
		uint16_t mMapSizeX = 0u;
		uint16_t mMapSizeY = 0u;
		uint16_t** mTileMap = nullptr;

		static constexpr uint32_t VERTICES_COUNT = 4u;
		static constexpr uint32_t INDICES_COUNT = 6u;

		ID3D11Buffer* mVertexBuffer = nullptr;
		ID3D11Buffer* mIndexBuffer = nullptr;
		std::vector<TileMap::UsedTextureInfo> mUsedTextures;

		bool mbNeedUpdate = false;
	};

	constexpr uint16_t TileMap::GetMapSizeX()
	{
		return mMapSizeX;
	}
	constexpr uint16_t TileMap::GetMapSizeY()
	{
		return mMapSizeY;
	}

	constexpr uint32_t TileMap::GetMapSize()
	{
		return mMapSizeX * mMapSizeY;
	}
	const std::vector<TileMap::UsedTextureInfo> TileMap::GetUsedTexture() const
	{
		return mUsedTextures;
	}

	Texture* TileMap::GetTileTexture(uint16_t i, uint16_t j)
	{
		Tile* t = TileManager::GetInstance().GetTile(mTileMap[i][j]);
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
		new(mTileMap) uint16_t* [mapSizeY];

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
			gCoreMemoryPool.Deallocate(mTileMap[i], sizeof(uint16_t) * mMapSizeX);
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


	void TileMap::SetTile(uint16_t i, uint16_t j, uint16_t tileId)
	{
		assert((j < mMapSizeX) && (i < mMapSizeY));
		mTileMap[i][j] = tileId;

		mbNeedUpdate = true;
	}

	void TileMap::SetTiles(uint16_t i, uint16_t j, TileGroup tiles)
	{
		uint16_t width = tiles.GetWidth();
		uint16_t height = tiles.GetHeight();
		for (size_t h = 0; h < height; h++)
		{
			for (size_t w = 0; w < width; w++)
			{
				SetTile(i + h, j + w, tiles.GetTiles()[h * width + w]);
			}
		}
	}


	void TileMap::FillMap(uint16_t tileId)
	{
		for (size_t i = 0; i < mMapSizeY; i++)
		{
			for (size_t j = 0; j < mMapSizeX; j++)
			{
				SetTile(i, j, tileId);
			}
		}

	}
	void TileMap::FillMap(uint16_t tileId, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom)
	{
		for (size_t i = top; i < bottom; i++)
		{
			for (size_t j = left; j < right; j++)
			{
				SetTile(i, j, tileId);
			}
		}
	}
	void TileMap::FillMapWithTileGroup(TileGroup tiles, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom, uint16_t spacingX, uint16_t spacingY)
	{
		uint16_t width = tiles.GetWidth();
		uint16_t height = tiles.GetHeight();
		for (size_t i = top; i < bottom; i += (height+ spacingY))
		{
			for (size_t j = left; j < right; j += (width+ spacingX))
			{
				SetTiles(i, j, tiles);
			}
		}
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
					//j++;
					temp = 1;
				}

				if (temp > 0)
				{
					SetTile(i,j,static_cast<uint16_t>(temp));
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
		uint32_t buffersize = mMapSizeX * mMapSizeY ;

		D3D11_BUFFER_DESC vertexBufferDesc;
		vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		vertexBufferDesc.ByteWidth = sizeof(VertexTC) * VERTICES_COUNT * buffersize;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		vertexBufferDesc.MiscFlags = 0;
		vertexBufferDesc.StructureByteStride = 0;

		// subresource 구조에 정점 데이터에 대한 포인터를 제공합니다.
		D3D11_SUBRESOURCE_DATA vertexData;
		vertexData.pSysMem = nullptr;
		vertexData.SysMemPitch = 0;
		vertexData.SysMemSlicePitch = 0;

		// 이제 정점 버퍼를 만듭니다.
		if (FAILED(device->CreateBuffer(&vertexBufferDesc, nullptr, &mVertexBuffer)))
		{
			return false;
		}

		D3D11_BUFFER_DESC indexBufferDesc;
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = sizeof(uint32_t) * INDICES_COUNT * buffersize;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.MiscFlags = 0;
		indexBufferDesc.StructureByteStride = 0;
		
		std::vector<uint32_t> indices;
		indices.reserve(INDICES_COUNT * buffersize);

		for (size_t j = 0; j < buffersize * 4; j += 4)
		{
			uint32_t i = static_cast<uint32_t>(j);

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

		mUsedTextures.clear();
		//HashTable textureHash(sizeof(uint16_t));
		std::unordered_map<Texture*, uint16_t> textureHash;
		uint16_t textureCount = 0;
		std::vector<std::vector<VertexTC>> vertices;
		for (size_t i = 0; i < mMapSizeY; i++)
		{
			for (size_t j = 0; j < mMapSizeX; j++)
			{
				//texture 에따라 나누기 위해
				Tile* tile = TileManager::GetInstance().GetTile(mTileMap[i][j]);
				if (!tile) continue;

				if (!textureHash.contains(tile->texture))
				{
					TileMap::UsedTextureInfo temp =
					{
						.count = 0u,
						.texture = tile->texture
					};

					mUsedTextures.push_back(temp);
					textureHash[tile->texture] = textureCount;
					textureCount++;
					vertices.resize(textureCount);
				}
				uint16_t texIndex = textureHash[tile->texture];
				mUsedTextures[texIndex].count++;

				float posX = mPosition.X + j * mCellSize;
				float posY = mPosition.Y - i * mCellSize;
				float left = posX;
				float right = left + mCellSize;
				float top = posY;
				float bottom = top - mCellSize;
				Float4 mColor = { 1.0,1.0f,1.0f,1.0f };

				VertexTC vertex1 = std::move(VertexTC(Float3(left, top, mPosition.Z),
					tile->startTexCoords,
					mColor));

				VertexTC vertex2 = std::move(VertexTC(Float3(right, top, mPosition.Z),
					Float2(tile->endTexCoords.X, tile->startTexCoords.Y),
					mColor));	// top right

				VertexTC vertex3 = std::move(VertexTC(Float3(right, bottom, mPosition.Z),
					tile->endTexCoords,
					mColor));		// bottom right


				VertexTC vertex4 = std::move(VertexTC(Float3(left, bottom, mPosition.Z),
					Float2(tile->startTexCoords.X, tile->endTexCoords.Y),
					mColor));

				vertices[texIndex].push_back(std::move(vertex1));
				vertices[texIndex].push_back(std::move(vertex2));
				vertices[texIndex].push_back(std::move(vertex3));
				vertices[texIndex].push_back(std::move(vertex4));
			}
		}
		std::vector<VertexTC> combinedData;
		//combinedData.resize(mMapSizeX * mMapSizeY * 4);
		for (size_t i = 0; i < vertices.size(); i++)
		{
			combinedData.insert(combinedData.end(), vertices[i].begin(), vertices[i].end());
		}

		deviceContext->Map(mVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		verticesPtr = reinterpret_cast<VertexTC*>(mappedResource.pData);
		memcpy(verticesPtr, reinterpret_cast<void*>(combinedData.data()), (sizeof(VertexTC) * combinedData.size()));
		deviceContext->Unmap(mVertexBuffer, 0);

		mbNeedUpdate = false;
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
		deviceContext->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		// 정점 버퍼로 그릴 기본형을 설정합니다. 여기서는 삼각형으로 설정합니다.
		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
}