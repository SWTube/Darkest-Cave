#pragma once
#include "WindowsSprite.h"
#include <unordered_map>
#include <string>
namespace cave {
	struct Animation {
		bool mIsLoof;
		uint32_t mFrames;
		uint32_t mCurFrames;
		float mDuration;
		float mInterval;
		MultiTexture* mTexture;
		
		Animation() {
			mIsLoof = false;
			mFrames = 0;
			mCurFrames = 0;
			mDuration = 0.0f;
			mInterval = 0.0f;
			mTexture = nullptr;
		}
		Animation(MultiTexture* texture, uint32_t frame, float duration, bool isLoof)
			:mFrames(frame),
			mDuration(duration),
			mTexture(texture),
			mIsLoof(isLoof)
		{
			mCurFrames = 0;
			assert(frame > 0);
			mInterval = mDuration / mFrames;
		}
		~Animation() {
			mTexture = nullptr;
		}


	};

	class AnimatedSprite : public WindowsSprite {
	public:
		AnimatedSprite() = delete;
		AnimatedSprite(std::string name, Animation* animation, MemoryPool* pool);
		AnimatedSprite(std::string name, MultiTexture* texture, uint32_t frame, const float duration, bool isLoof,MemoryPool* pool);
		virtual ~AnimatedSprite();

		void Destroy() override;
		void Update() override;
	
	public:
		void AddAniamtion(std::string name, Animation* animation);
		void SetState(std::string state);

	private:
		bool mbIsPlaying = false;
		MemoryPool* mPool = nullptr;
		std::string mState = "";
		std::unordered_map<std::string, Animation*> mAnimations;
		
		float mTotalElapsed = 0.0f;
		float tempElapsed = 0.01f; // (임시)업데이트 간 간격

	};

}
