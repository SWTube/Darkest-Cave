/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
module;
//#include "Sprite.h"
#include <unordered_map>
#include <string>
#include "GraphicsApiPch.h"

#include "CoreTypes.h"
#include "CoreGlobals.h"
#include "Containers/Vertex.h"
//#include "Texture/Texture.h"

export module AnimatedSprite;
import Sprite;
//import Texture;
import TextureManager;
//import MultiTexture;


namespace cave {

	export struct Animation {
		MultiTexture* texture;
		uint32_t frames;
		uint32_t curFrames;
		bool bIsLoof;
		float duration;
		float interval;

		Animation() {
			texture = nullptr;
			frames = 0;
			curFrames = 0;
			bIsLoof = false;
			duration = 0.0f;
			interval = 0.0f;

		}
		Animation(MultiTexture* texture, uint32_t frame, float duration, bool isLoof)
			: texture(texture),
			frames(frame),
			curFrames(0),
			bIsLoof(isLoof),
			duration(duration)

		{
			assert(frame > 0);
			interval = duration / static_cast<float>(frames);
		}

		~Animation() {
			texture = nullptr;
		}


	};

	export class AnimatedSprite : public Sprite 
	{
	public:
		AnimatedSprite() = delete;
		AnimatedSprite(std::string name, Animation* animation, MemoryPool* pool);
		AnimatedSprite(std::string name, const std::filesystem::path& filename, uint32_t frame, float duration, bool isLoof);
		AnimatedSprite(std::string name, MultiTexture* texture, uint32_t frame, const float duration, bool isLoof, MemoryPool* pool);
		AnimatedSprite(const AnimatedSprite& other);

		virtual ~AnimatedSprite();

		void Destroy() override;


	public:
		void AddAniamtion(std::string name, Animation* animation);
		void SetState(std::string state);
	
	protected:
		void update() override;

	private:
		MemoryPool* mPool = nullptr;
		bool mbIsPlaying = false;
		float mTotalElapsed = 0.0f;
		float tempElapsed = 0.01f; // (임시)업데이트 간 간격
		std::string mState = "";
		std::unordered_map<std::string, Animation*> mAnimations;

	};

	AnimatedSprite::AnimatedSprite(std::string name, Animation* animation, MemoryPool* pool) :
		Sprite(animation->texture)
		, mPool(pool)
		, mState(name)
	{
		AddAniamtion(name, animation);
	}

	AnimatedSprite::AnimatedSprite(std::string name, MultiTexture* texture, uint32_t frame, const float duration, bool isLoof, MemoryPool* pool) :
		Sprite(texture)
		, mPool(pool)
		, mState(name)
	{
		mbIsPlaying = true;
		Animation* newAnim = reinterpret_cast<Animation*>(mPool->Allocate(sizeof(Animation)));
		new(newAnim) Animation(texture, frame, duration, isLoof);
		AddAniamtion(name, newAnim);
	}

	//나중에 고쳐야해!!
	AnimatedSprite::AnimatedSprite(std::string name, const std::filesystem::path& filename, uint32_t frame, float duration, bool isLoof)
		:mState(name)
	{
		mTexture = TextureManager::GetInstance().GetTexture(filename.generic_string());
		if (mTexture == nullptr) mTexture = TextureManager::GetInstance().AddMultiTexture(filename,frame,1,frame);
		SetTexture(mTexture);
		mbIsPlaying = true;
		Animation* newAnim = reinterpret_cast<Animation*>(gCoreMemoryPool.Allocate(sizeof(Animation)));
		new(newAnim) Animation(reinterpret_cast<MultiTexture*>(mTexture), frame, duration, isLoof);
		AddAniamtion(name, newAnim);

	}

	AnimatedSprite::AnimatedSprite(const AnimatedSprite& other)
		:Sprite(other),
		mPool(other.mPool),
		mbIsPlaying(other.mbIsPlaying),
		mState(other.mState)
	{
		for (auto it = other.mAnimations.begin(); it != mAnimations.end(); it++) {
			Animation* newAnim = reinterpret_cast<Animation*>(mPool->Allocate(sizeof(Animation)));
			new(newAnim) Animation(it->second->texture, it->second->frames, it->second->duration, it->second->bIsLoof);
			AddAniamtion(it->first, newAnim);
		}

	}

	AnimatedSprite::~AnimatedSprite()
	{
		Destroy();
	}

	void AnimatedSprite::Destroy()
	{
		Sprite::Destroy();

		for (auto it = mAnimations.begin(); it != mAnimations.end();)
		{
			it->second->~Animation();
			mPool->Deallocate(it->second, sizeof(Animation));
			it->second = nullptr;
			mAnimations.erase(it++);

		}
		mAnimations.clear();

	}

	void AnimatedSprite::update()
	{
		if (!mbIsPlaying) return;

		mTotalElapsed += tempElapsed;
		Animation* curAnimation = mAnimations[mState];
		if (mTotalElapsed >= curAnimation->interval) {
			mTotalElapsed -= curAnimation->interval;
			curAnimation->curFrames++;
			if (curAnimation->curFrames > curAnimation->frames) {
				if (mAnimations[mState]->bIsLoof) curAnimation->curFrames = 0;
				else
				{
					mbIsPlaying = false;
					return;
				}
			}

			mAnimations[mState]->texture->SetFrame(mAnimations[mState]->curFrames);

		}
	}


	void AnimatedSprite::AddAniamtion(std::string name, Animation* animation)
	{
		mAnimations[name] = animation;
	}

	void AnimatedSprite::SetState(std::string state) {

		if (!mAnimations.contains(state)) {
			return;
		}

		mState = state;
		mTexture = mAnimations[mState]->texture;
		mAnimations[mState]->curFrames = 0;
	}

}