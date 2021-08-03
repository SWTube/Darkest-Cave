#pragma once
#include "WindowsSprite.h"
#include <unordered_map>
#include <string>
namespace cave {
	struct Animation {
		bool bIsLoof;
		uint32_t frames;
		uint32_t curFrames;
		float duration;
		float interval;
		MultiTexture* texture;
		
		Animation() {
			bIsLoof = false;
			frames = 0;
			curFrames = 0;
			duration = 0.0f;
			interval = 0.0f;
			texture = nullptr;
		}
		Animation(MultiTexture* texture, uint32_t frame, float duration, bool isLoof)
			:bIsLoof(isLoof),
			frames(frame),
			curFrames(0),
			duration(duration),
			texture(texture)
		{
			assert(frame > 0);
			interval = duration / static_cast<float>(frames);
		}

		~Animation() {
			texture = nullptr;
		}


	};

	class AnimatedSprite : public WindowsSprite {
	public:
		AnimatedSprite() = delete;
		AnimatedSprite(std::string name, Animation* animation, MemoryPool* pool);
		AnimatedSprite(std::string name, MultiTexture* texture, uint32_t frame, const float duration, bool isLoof,MemoryPool* pool);
		AnimatedSprite(const AnimatedSprite& other);
		
		virtual ~AnimatedSprite();

		void Destroy() override;
		void Update() override;
	
	public:
		void AddAniamtion(std::string name, Animation* animation);
		void SetState(std::string state);

	private:
		MemoryPool* mPool = nullptr;
		bool mbIsPlaying = false;
		std::string mState = "";
		std::unordered_map<std::string, Animation*> mAnimations;
		
		float mTotalElapsed = 0.0f;
		float tempElapsed = 0.01f; // (임시)업데이트 간 간격

	};

}
