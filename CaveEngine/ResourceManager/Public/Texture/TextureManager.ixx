/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
module;

#include <unordered_map>
#include "GraphicsApiPch.h"
#include "CoreGlobals.h"
#include "CoreTypes.h"
//#include "Texture/Texture.h"
#include "Debug/Log.h"
//#include "Texture/MultiTexture.h"

export module TextureManager;

export import Texture;
export import MultiTexture;

namespace cave
{
	export class TextureManager final
	{
	public:
		static TextureManager& GetInstance() 
		{
			static TextureManager msInstance;
			return msInstance;
		}
		/*
		* filename에 해당하는 texture를 생성한 후 반환.
		* texture 생성에 실패하거나, 이미 해당 texture가 존재 시 nullptr 반환.
		*/
		Texture* AddTexture(const std::filesystem::path& filename);
		/*
		* filename에 해당하는 Multitexture를 생성한 후 반환.
		* Multitexture 생성에 실패하거나, 이미 해당 texture가 존재 시 nullptr 반환.
		*/
		MultiTexture* AddMultiTexture(const std::filesystem::path& filename, uint32_t column, uint32_t row = 1);
		
		//있으면 바로 주고 없으면 만들어서 줌.
		Texture* GetOrAddTexture(const std::filesystem::path& filename);
		MultiTexture* GetOrAddMultiTexture(const std::filesystem::path& filename, uint32_t column, uint32_t row = 1);
		Texture* GetTexture(const std::string& key);
		void RemoveTexture(const std::string& key);
		void SetDevice(ID3D11Device* device);

	private:
		TextureManager() = default;
		TextureManager(const TextureManager& other) = delete;
		TextureManager& operator=(const TextureManager& other) = delete;
		~TextureManager();

		std::unordered_map<std::string, Texture*> mTextures;
		ID3D11Device* mDevice = nullptr;

	};
	
	TextureManager::~TextureManager()
	{
		for (auto it = mTextures.begin(); it != mTextures.end();) {
			it->second->~Texture();
			gCoreMemoryPool.Deallocate(it->second, sizeof(Texture));
			it->second = nullptr;
			mTextures.erase(it++);
		}
		mTextures.clear();
	}

	Texture* TextureManager::AddTexture(const std::filesystem::path& filename)
	{
		if (mTextures.contains(filename.generic_string())) {
			LOGEF(eLogChannel::GRAPHICS, "%s file already exist.", filename.string().c_str());
			return nullptr;
		}

		Texture* newTexture = reinterpret_cast<Texture*>(gCoreMemoryPool.Allocate(sizeof(Texture)));
		new(newTexture) cave::Texture(mDevice, filename);

		if(newTexture->GetTexture() == nullptr)
		{
			newTexture->~Texture();
			gCoreMemoryPool.Deallocate(newTexture, sizeof(Texture));
			return nullptr;
		}

		mTextures[filename.generic_string()] = newTexture;

		return newTexture;
	}

	MultiTexture* TextureManager::AddMultiTexture(const std::filesystem::path& filename, uint32_t column, uint32_t row)
	{
		if (mTextures.contains(filename.generic_string())) {
			LOGEF(eLogChannel::GRAPHICS, "%s file already exist.", filename.string().c_str());
			return nullptr;
		}

		MultiTexture* newTexture = reinterpret_cast<MultiTexture*>(gCoreMemoryPool.Allocate(sizeof(MultiTexture)));
		new(newTexture) cave::MultiTexture(mDevice, filename, column,row);

		if (newTexture->GetTexture() == nullptr)
		{
			newTexture->~MultiTexture();
			gCoreMemoryPool.Deallocate(newTexture, sizeof(Texture));
			return nullptr;
		}

		mTextures[filename.generic_string()] = newTexture;

		return newTexture;
	}

	Texture* TextureManager::GetTexture(const std::string& key)
	{
		if (mTextures.contains(key)) 
		{
			return mTextures[key];
		}
		return nullptr;
	}

	Texture* TextureManager::GetOrAddTexture(const std::filesystem::path& filename)
	{
		Texture* tex;
		
		if (mTextures.contains(filename.generic_string()))
			tex = mTextures[filename.generic_string()];
		else 
			tex = AddTexture(filename);

		return tex;
		
	}
	MultiTexture* TextureManager::GetOrAddMultiTexture(const std::filesystem::path& filename, uint32_t column, uint32_t row)
	{
		MultiTexture* tex;

		if (mTextures.contains(filename.generic_string()))
			tex = reinterpret_cast<MultiTexture*>(mTextures[filename.generic_string()]);
		else
			tex = AddMultiTexture(filename, column, row);

		return tex;
	}

	void TextureManager::RemoveTexture(const std::string& key)
	{
		if (mTextures.contains(key))
		{
			mTextures[key]->~Texture();
			gCoreMemoryPool.Deallocate(mTextures[key], sizeof(Texture));
			mTextures[key] = nullptr;
			mTextures.erase(key);
		}
		else 
		{
			LOGEF(eLogChannel::GRAPHICS, "%s file does not exist.", key.c_str());
		}

	}

	void TextureManager::SetDevice(ID3D11Device* device)
	{
		mDevice = device;
	}



}