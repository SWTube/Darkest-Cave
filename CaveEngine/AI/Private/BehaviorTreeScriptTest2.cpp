
#include <cmath>

#include "BehaviorTreeScriptTest2.h"
#include "Object/Transform.h"

namespace cave
{
	BehaviorTreeTestScript2::BehaviorTreeTestScript2(const char* name, uint32_t spriteIndex, uint32_t textureIndex, float speed)
		: Script(name)
		, mSpriteIndex(spriteIndex)
		, mTextureIndex(textureIndex)
		, mNextTextureIndex(mTextureIndex + 1)
		, mSpeed(speed)
	{

	}

	BehaviorTreeTestScript2::~BehaviorTreeTestScript2()
	{
		mRoot->Clear();
	}

	void BehaviorTreeTestScript2::Init(GameObject& gameObject)
	{
		gameObject.GetTransform()->GetPosition()->X = 250.0f;
		gameObject.GetTransform()->GetPosition()->Y = 250.0f;
		gameObject.GetRenderer()->SetSpritePosition(mSpriteIndex, *gameObject.GetTransform()->GetPosition());

		mRoot = new RootNode("Root");

		mIsOverDistance = new IfDecorator("IsOverDistance", std::bind(&BehaviorTreeTestScript2::IsOverDistatnce, this, std::placeholders::_1));

		mSelectRandomDirection = new RandomNode("SelectRandomDirection", 4);

		mSetRight = new ActionNode("SetRight", std::bind(&BehaviorTreeTestScript2::ActionSetRight, this, std::placeholders::_1));
		mSetLeft = new ActionNode("SetLeft", std::bind(&BehaviorTreeTestScript2::ActionSetLeft , this, std::placeholders::_1));
		mSetUp = new ActionNode("SetUp", std::bind(&BehaviorTreeTestScript2::ActionSetUp, this, std::placeholders::_1));
		mSetDown = new ActionNode("SetDown", std::bind(&BehaviorTreeTestScript2::ActionSetDown, this, std::placeholders::_1));

		mMove = new ActionNode("Move", std::bind(&BehaviorTreeTestScript2::ActionMove, this, std::placeholders::_1));

		mRoot->AddChild(mIsOverDistance);

		mIsOverDistance->SetChild(mSelectRandomDirection);

		mSelectRandomDirection->AddChild(mSetRight);
		mSelectRandomDirection->AddChild(mSetLeft);
		mSelectRandomDirection->AddChild(mSetUp);
		mSelectRandomDirection->AddChild(mSetDown);

		mRoot->AddChild(mMove);
	}

	void BehaviorTreeTestScript2::FixedUpdate(GameObject& gameObject)
	{
		mRoot->Run(gameObject);
	}

	void BehaviorTreeTestScript2::Update(GameObject& gameObject)
	{

	}

	uint32_t BehaviorTreeTestScript2::GetTextureIndex() const
	{
		return mTextureIndex;
	}


	bool BehaviorTreeTestScript2::IsOverDistatnce(GameObject& gameObject)
	{
		if (mMoveDistance > 100.0f) {
			mMoveDistance = 0;
			return true;
		}
		return false;
	}

	bool BehaviorTreeTestScript2::ActionSetRight(GameObject& gameObject)
	{
		mDirectionX = 1;
		mDirectionY = 0;
		return true;
	}
	bool BehaviorTreeTestScript2::ActionSetLeft(GameObject& gameObject)
	{
		mDirectionX = -1;
		mDirectionY = 0;
		return true;
	}
	bool BehaviorTreeTestScript2::ActionSetUp(GameObject& gameObject)
	{
		mDirectionX = 0;
		mDirectionY = 1;
		return true;
	}
	bool BehaviorTreeTestScript2::ActionSetDown(GameObject& gameObject)
	{
		mDirectionX = 0;
		mDirectionY = -1;
		return true;
	}

	bool BehaviorTreeTestScript2::ActionMove(GameObject& gameObject)
	{
		mMoveDistance += mSpeed;
		gameObject.GetTransform()->GetPosition()->X += mSpeed * mDirectionX;
		gameObject.GetTransform()->GetPosition()->Y += mSpeed * mDirectionY;

		gameObject.GetRenderer()->SetSpritePosition(mSpriteIndex, *gameObject.GetTransform()->GetPosition());
		return true;
	}
}


// action node 의 반환값 bool 타입으로 변경
// if decorator 외의 다른 decorator의 condition 값을 함수로 변경