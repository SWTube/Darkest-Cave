#pragma once
#include "Sprite.h"
#include <unordered_map>
#include <string>

//import Sprite;

namespace cave {
	struct Animation {
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

	class AnimatedSprite : public Sprite {
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
		float mTotalElapsed = 0.0f;
		float tempElapsed = 0.01f; // (임시)업데이트 간 간격
		std::string mState = "";
		std::unordered_map<std::string, Animation*> mAnimations;

	};

}
