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
//#include "Texture/Texture.h"

export module AnimatedSprite;

import cave.Core.Types.Vertex;
import Sprite;
//import Texture;
import TextureManager;
//import MultiTexture;


namespace cave {

	export struct Animation {
		MultiTexture* texture;
		uint32_t startFrame; // 시작 프레임
		uint32_t endFrame; // 끝 프레임
		uint32_t curFrames; // 현재 프레임
		bool bIsLoof;
		float duration;

		Animation() {
			texture = nullptr;
			startFrame = 0;
			endFrame = 0;
			curFrames = 0;
			bIsLoof = false;
			duration = 0.0f;

		}
		Animation(MultiTexture* texture, uint32_t start, uint32_t end, float duration, bool isLoof)
			: texture(texture),
			startFrame(start),
			endFrame(end),
			curFrames(0),
			bIsLoof(isLoof),
			duration(duration)
		{

		}
		constexpr uint32_t GetFrameCount()
		{
			return endFrame - startFrame + 1;
		}

		constexpr float GetInterval()
		{
			return duration / static_cast<float>(endFrame-startFrame+1);
		}

		~Animation() {
			texture = nullptr;
		}


	};

	export class AnimatedSprite : public Sprite 
	{
	public:
		AnimatedSprite() = default;
		AnimatedSprite(std::string name, Animation animation);
		AnimatedSprite(std::string name, const std::filesystem::path& filename, uint32_t column, uint32_t row, float duration, bool isLoof = true);
		AnimatedSprite(std::string name, MultiTexture* texture, uint32_t frame, const float duration, bool isLoof);
		AnimatedSprite(const AnimatedSprite& other);
		AnimatedSprite(AnimatedSprite&& other);
		AnimatedSprite& operator=(const AnimatedSprite& other);
		AnimatedSprite& operator=(AnimatedSprite&& other);
		virtual ~AnimatedSprite();

		void Destroy() override;


	public:
		void AddAnim(std::string name, Animation animation);
		void AddAnimByMultiTexture(std::string name, const std::filesystem::path& filename, uint32_t column, uint32_t row, float duration, bool isLoof = true);

		/*
		이미 존재하는 애니메이션의 시작 프레임과, 끝 프레임, 재생속도를 변경하여 복사한 새로운 애니메이션을 추가. 
		*/
		void AddAnimWithExistAnim(std::string animName, std::string existAnimName, uint32_t start, uint32_t end, float duration, bool isLoof = true);


		void SetAnimFrame(std::string animName, uint32_t start, uint32_t end);

		void SetCurAnim(std::string animName);
		
		constexpr void SetIsPlaying(bool isPlaying);
		
		const std::string& GetCurAnim() const;
	
	protected:
		void update() override;

	private:
		bool mbIsPlaying = false;
		float mTotalElapsed = 0.0f;
		float tempElapsed = 0.016f; // (임시)업데이트 간 간격
		std::string mAnimName = "";
		std::unordered_map<std::string, Animation> mAnimations;

	};

	AnimatedSprite::AnimatedSprite(std::string name, Animation animation) 
		:Sprite(animation.texture)
		, mAnimName(name)
	{
		AddAnim(name, animation);
		mAnimations[name].texture->GetUVCoordsByFrame(mAnimations[name].curFrames, mStartTextureCoord, mEndTextureCoord);
	}

	AnimatedSprite::AnimatedSprite(std::string name, MultiTexture* texture, uint32_t frame, const float duration, bool isLoof) 
		:Sprite(texture)
		, mAnimName(name)
	{
		mbIsPlaying = true;
		Animation newAnim(texture, 0,frame, duration, isLoof);
		AddAnim(name, newAnim);
		mAnimations[name].texture->GetUVCoordsByFrame(mAnimations[name].curFrames, mStartTextureCoord, mEndTextureCoord);
	}

	AnimatedSprite::AnimatedSprite(std::string name, const std::filesystem::path& filename, uint32_t column, uint32_t row, float duration, bool isLoof)
		:Sprite(TextureManager::GetInstance().GetOrAddMultiTexture(filename, column,row))
		, mAnimName(name)
	{
		mbIsPlaying = true;
		Animation newAnim(reinterpret_cast<MultiTexture*>(mTexture), 0, column * row -1, duration, isLoof);
		AddAnim(name, newAnim);
		mAnimations[name].texture->GetUVCoordsByFrame(mAnimations[name].curFrames, mStartTextureCoord, mEndTextureCoord);
	}

	AnimatedSprite::AnimatedSprite(const AnimatedSprite& other)
		:Sprite(other),
		mbIsPlaying(other.mbIsPlaying),
		mAnimName(other.mAnimName)
	{

		mAnimations = other.mAnimations;

	}
	AnimatedSprite::AnimatedSprite(AnimatedSprite&& other)
		:Sprite(other),
		mbIsPlaying(other.mbIsPlaying),
		mAnimName(other.mAnimName)
	{
		mAnimations = other.mAnimations;
	}

	AnimatedSprite& AnimatedSprite::operator=(const AnimatedSprite& other)
	{
		if (this != &other) 
		{
			mTexture = other.mTexture;

			mPosition = other.mPosition;
			mWidth = other.mWidth;
			mHeight = other.mHeight;
			mStartTextureCoord = other.mStartTextureCoord;
			mEndTextureCoord = other.mEndTextureCoord;
			mbIsPlaying = other.mbIsPlaying;
			mAnimName = other.mAnimName;

			mAnimations = other.mAnimations;

		}
		return *this;
	}
	AnimatedSprite& AnimatedSprite::operator=(AnimatedSprite&& other)
	{
		if (this != &other)
		{
			mTexture = other.mTexture;
			mPosition = other.mPosition;
			mWidth = other.mWidth;
			mHeight = other.mHeight;
			mStartTextureCoord = other.mStartTextureCoord;
			mEndTextureCoord = other.mEndTextureCoord;
			mbIsPlaying = other.mbIsPlaying;
			mAnimName = other.mAnimName;

			other.mTexture = nullptr;

			mAnimations = other.mAnimations;
		}
		return *this;
	}

	const std::string& AnimatedSprite::GetCurAnim() const
	{
		return mAnimName;
	}
	constexpr void AnimatedSprite::SetIsPlaying(bool isPlaying)
	{
		mbIsPlaying = isPlaying;
	}
	AnimatedSprite::~AnimatedSprite()
	{
		Destroy();
	}

	void AnimatedSprite::Destroy()
	{
		Sprite::Destroy();
	}


	void AnimatedSprite::update()
	{
		if (!mbIsPlaying) return;

		mTotalElapsed += tempElapsed;
		Animation& curAnimation = mAnimations[mAnimName];
		float interval = curAnimation.GetInterval();
		if (mTotalElapsed >= interval) 
		{
			mTotalElapsed -= interval;
			curAnimation.curFrames++;
			if (curAnimation.curFrames > curAnimation.endFrame) 
			{
				if (mAnimations[mAnimName].bIsLoof) curAnimation.curFrames = curAnimation.startFrame;
				else
				{
					return;
				}
			} 
			mAnimations[mAnimName].texture->GetUVCoordsByFrame(mAnimations[mAnimName].curFrames, mStartTextureCoord, mEndTextureCoord);

		}
	}


	void AnimatedSprite::AddAnim(std::string name, Animation animation)
	{
		mAnimations[name] = animation;
	}

	void AnimatedSprite::AddAnimByMultiTexture(std::string name, const std::filesystem::path& filename, uint32_t column, uint32_t row, float duration, bool isLoof)
	{
		MultiTexture* tex = TextureManager::GetInstance().GetOrAddMultiTexture(filename, column, row);
		Animation anim(tex, 0, column * row -1, duration, isLoof);
		mAnimations[name] = anim;
	}
	void AnimatedSprite::AddAnimWithExistAnim(std::string animName, std::string existAnimName, uint32_t start, uint32_t end, float duration, bool isLoof)
	{

		if (!mAnimations.contains(existAnimName)) {
			//존재 하지 않음.
			return;
		}
		Animation anim(mAnimations[existAnimName].texture, start, end, duration, isLoof);

		AddAnim(animName, anim);
	}

	void AnimatedSprite::SetAnimFrame(std::string animName, uint32_t start, uint32_t end)
	{
		if (!mAnimations.contains(animName)) {
			return;
		}
		mAnimations[animName].startFrame = start;
		mAnimations[animName].endFrame = end;

	}

	void AnimatedSprite::SetCurAnim(std::string animName)
	{

		if (!mAnimations.contains(animName)) {
			return;
		}

		mTotalElapsed = 0.0f;
		mAnimName = animName;
		SetTexture(mAnimations[mAnimName].texture);
		mAnimations[mAnimName].curFrames = mAnimations[mAnimName].startFrame;
		mAnimations[mAnimName].texture->GetUVCoordsByFrame(mAnimations[mAnimName].curFrames, mStartTextureCoord, mEndTextureCoord);
	}

}