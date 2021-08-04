
#include <cmath>

#include "BehaviorTreeScriptTest.h"
#include "Object/Transform.h"

namespace cave
{
	BehaviorTreeTestScript::BehaviorTreeTestScript(const char* name, uint32_t spriteIndex, uint32_t textureIndex, float speed)
		: Script(name)
		, mSpriteIndex(spriteIndex)
		, mTextureIndex(textureIndex)
		, mNextTextureIndex(mTextureIndex + 1)
		, mSpeed(speed)
	{

	}

	BehaviorTreeTestScript::~BehaviorTreeTestScript()
	{
		mRoot->Clear();
	}

	void BehaviorTreeTestScript::Init(GameObject& gameObject)
	{
		gameObject.GetTransform()->GetPosition()->X = 100.0f;
		gameObject.GetTransform()->GetPosition()->Y = 200.0f;
		gameObject.GetRenderer()->SetSpritePosition(mSpriteIndex, *gameObject.GetTransform()->GetPosition());

		mRoot = new RootNode("Root");

		mSetDirection = new ActionNode("SetDirection", std::bind(&BehaviorTreeTestScript::ActionSetDirection, this, std::placeholders::_1));
		mRight = new ActionNode("Right", std::bind(&BehaviorTreeTestScript::ActionMoveRight, this, std::placeholders::_1));
		mLeft = new ActionNode("Left", std::bind(&BehaviorTreeTestScript::ActionMoveLeft, this, std::placeholders::_1));
		mJump = new ActionNode("Jump", std::bind(&BehaviorTreeTestScript::ActionJump, this, std::placeholders::_1));

		mIsDirectionRight = new IfDecorator("IsDirectionRight", std::bind(&BehaviorTreeTestScript::IsDirectionRight, this, std::placeholders::_1));
		mIsDirectionLeft = new IfDecorator("IsDirectionLeft", std::bind(&BehaviorTreeTestScript::IsDirectionLeft, this, std::placeholders::_1));
		mIsJumpTime = new IfDecorator("IsDirectionLeft", std::bind(&BehaviorTreeTestScript::IsJumpTime, this, std::placeholders::_1));
		
		mRoot->AddChild(mSetDirection);			// ActionNode
		mRoot->AddChild(mIsDirectionRight);		// IfDecorator
		mRoot->AddChild(mIsDirectionLeft);		// IfDecorator
		mRoot->AddChild(mIsJumpTime);			// IfDecorator

		mIsDirectionRight->SetChild(mRight);	// ActionNode
		mIsDirectionLeft->SetChild(mLeft);		// ActionNode
		mIsJumpTime->SetChild(mJump);			// ActionNode
	}

	void BehaviorTreeTestScript::FixedUpdate(GameObject& gameObject)
	{
		mRoot->Run(gameObject);
	}

	void BehaviorTreeTestScript::Update(GameObject& gameObject)
	{

	}

	uint32_t BehaviorTreeTestScript::GetTextureIndex() const
	{
		return mTextureIndex;
	}

	bool BehaviorTreeTestScript::ActionMoveRight(GameObject& gameObject)
	{
		gameObject.GetTransform()->GetPosition()->X += mSpeed;
		gameObject.GetRenderer()->SetSpritePosition(mSpriteIndex, *gameObject.GetTransform()->GetPosition());

		return true;
	}

	bool BehaviorTreeTestScript::ActionMoveLeft(GameObject& gameObject)
	{
		gameObject.GetTransform()->GetPosition()->X -= mSpeed;
		gameObject.GetRenderer()->SetSpritePosition(mSpriteIndex, *gameObject.GetTransform()->GetPosition());

		return true;
	}

	bool BehaviorTreeTestScript::ActionSetDirection(GameObject& gameObject)
	{
		if (gameObject.GetTransform()->GetPosition()->X > 500.f)
		{
			gameObject.GetRenderer()->SetSpriteTexture(mSpriteIndex, 1);
			mDirection = false;
		}
		else if (gameObject.GetTransform()->GetPosition()->X < 100.f)
		{
			gameObject.GetRenderer()->SetSpriteTexture(mSpriteIndex, 0);
			mDirection = true;
		}

		return true;
	}

	bool BehaviorTreeTestScript::ActionJump(GameObject& gameObject)
	{
		mSinX += 0.00095f;

		gameObject.GetTransform()->GetPosition()->Y = -abs(sin(mSinX) * 100) + 200;
		gameObject.GetRenderer()->SetSpritePosition(mSpriteIndex, *gameObject.GetTransform()->GetPosition());

		return true;
	}

	bool BehaviorTreeTestScript::IsDirectionRight(GameObject& gameObject)
	{
		return mDirection;
	}

	bool BehaviorTreeTestScript::IsDirectionLeft(GameObject& gameObject)
	{
		return !mDirection;
	}

	bool BehaviorTreeTestScript::IsJumpTime(GameObject& gameObject)
	{
		return gameObject.GetTransform()->GetPosition()->X > 200.f && gameObject.GetTransform()->GetPosition()->X < 300.f;
	}
}


// action node 의 반환값 bool 타입으로 변경
// if decorator 외의 다른 decorator의 condition 값을 함수로 변경