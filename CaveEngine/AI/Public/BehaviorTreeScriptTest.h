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
	class BehaviorTreeTestScript : public Script
	{
	public:
		BehaviorTreeTestScript(const char* name, uint32_t spriteIndex, uint32_t textureIndex, float speed);

		virtual ~BehaviorTreeTestScript();

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
		void ActionSetDirection(GameObject&);
		void ActionMoveRight(GameObject&);
		void ActionMoveLeft(GameObject&);
		void ActionJump(GameObject&);

		bool IsDirectionRight(GameObject&);
		bool IsDirectionLeft(GameObject&);
		bool IsJumpTime(GameObject&);

	private:
		RootNode* mRoot;

		ActionNode* mSetDirection;
		ActionNode* mRight;
		ActionNode* mLeft;
		ActionNode* mJump;

		IfDecorator* mIsDirectionRight;
		IfDecorator* mIsDirectionLeft;
		IfDecorator* mIsJumpTime;

		bool mDirection = true;
		bool mIsJump = false;
		double mSinX = 0;
	};
}