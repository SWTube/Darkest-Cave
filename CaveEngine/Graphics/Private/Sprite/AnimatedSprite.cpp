#include "Sprite\AnimatedSprite.h"
#include <iostream>
namespace cave {

	AnimatedSprite::AnimatedSprite(std::string name, Animation* animation, MemoryPool* pool) :
		WindowsSprite(animation->mTexture)
		,mPool(pool)
		,mState(name)
	{
		AddAniamtion(name, animation);
	}

	AnimatedSprite::AnimatedSprite(std::string name, MultiTexture* texture, uint32_t frame, const float duration,bool isLoof, MemoryPool* pool) :
		WindowsSprite(texture)
		,mPool(pool)
		,mState(name)
	{
		mbIsPlaying = true;
		Animation* newAnim = reinterpret_cast<Animation*>(mPool->Allocate(sizeof(Animation)));
		new(newAnim) Animation(texture,frame, duration, isLoof);
		AddAniamtion(name, newAnim);
	}

	AnimatedSprite::~AnimatedSprite()
	{
	}

	void AnimatedSprite::Destroy()
	{
		WindowsSprite::Destroy();

		//mPool->Deallocate(mDeviceResources, sizeof(DeviceResources))
		for(auto it = mAnimations.begin(); it != mAnimations.end(); it++)
		{
			it->second->~Animation();
			mPool->Deallocate(it->second, sizeof(Animation));
			it->second = nullptr;
			mAnimations.erase(it);

		}
		mAnimations.clear();
		
	}

	void AnimatedSprite::Update()
	{
		if (!mbIsPlaying) return;

		mTotalElapsed += tempElapsed;
		Animation* curAnimation = mAnimations[mState];
		if (mTotalElapsed >= curAnimation->mInterval) {
			mTotalElapsed -= curAnimation->mInterval;
			curAnimation->mCurFrames++;
			if (curAnimation->mCurFrames > curAnimation->mFrames) {
				if (mAnimations[mState]->mIsLoof) curAnimation->mCurFrames = 0;
				else
				{
					mbIsPlaying = false;
					return;
				}
			}

			mAnimations[mState]->mTexture->SetFrame(mAnimations[mState]->mCurFrames);

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
		mTexture = mAnimations[mState]->mTexture;
		mAnimations[mState]->mCurFrames = 0;
	}
}
