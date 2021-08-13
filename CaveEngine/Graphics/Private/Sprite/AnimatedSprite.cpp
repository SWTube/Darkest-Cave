#include "Sprite\AnimatedSprite.h"
#include <iostream>
namespace cave {

	AnimatedSprite::AnimatedSprite(std::string name, Animation* animation, MemoryPool* pool) :
		Sprite(animation->texture)
		,mPool(pool)
		,mState(name)
	{
		AddAniamtion(name, animation);
	}

	AnimatedSprite::AnimatedSprite(std::string name, MultiTexture* texture, uint32_t frame, const float duration,bool isLoof, MemoryPool* pool) :
		Sprite(texture)
		,mPool(pool)
		,mState(name)
	{
		mbIsPlaying = true;
		Animation* newAnim = reinterpret_cast<Animation*>(mPool->Allocate(sizeof(Animation)));
		new(newAnim) Animation(texture,frame, duration, isLoof);
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
			new(newAnim) Animation(it->second->texture,it->second->frames,it->second->duration,it->second->bIsLoof);
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

		for(auto it = mAnimations.begin(); it != mAnimations.end();)
		{
			it->second->~Animation();
			mPool->Deallocate(it->second, sizeof(Animation));
			it->second = nullptr;
			mAnimations.erase(it++);

		}
		mAnimations.clear();
		
	}

	void AnimatedSprite::Update()
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
