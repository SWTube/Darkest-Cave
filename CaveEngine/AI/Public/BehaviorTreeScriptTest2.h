/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <string>
#include "BehaviorTree.h"
#include "Object/Script.h"

namespace cave
{
	class BehaviorTreeTestScript2 : public Script
	{
	public:
		BehaviorTreeTestScript2(const char* name, uint32_t spriteIndex, uint32_t textureIndex, float speed);

		virtual ~BehaviorTreeTestScript2();

		virtual void Init(GameObject& gameObject) override;
		virtual void FixedUpdate(GameObject& gameObject) override;
		virtual void Update(GameObject& gameObject) override;

		uint32_t GetTextureIndex() const;


	private:
		uint32_t mSpriteIndex;
		uint32_t mTextureIndex;
		uint32_t mNextTextureIndex;
		float mSpeed;

	public:
		bool IsOverDistatnce(GameObject&);

		bool ActionMove(GameObject&);

		bool ActionSetRight(GameObject&);
		bool ActionSetLeft(GameObject&);
		bool ActionSetUp(GameObject&);
		bool ActionSetDown(GameObject&);

	private:
		RootNode* mRoot;

		ActionNode* mMove;

		IfDecorator* mIsOverDistance;

		RandomNode* mSelectRandomDirection;

		ActionNode* mSetRight;
		ActionNode* mSetLeft;
		ActionNode* mSetUp;
		ActionNode* mSetDown;


		int mDirectionX = 0;
		int mDirectionY = 0;
		float mMoveDistance = 0;
	};
}