/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "FiniteStateMachine/State.h"

namespace cave
{
	State::State()
	{
		mStateName = "";
		mIsCurrent = false;
		mTrigger = NULL;
		mAnimation = 0;
		mNeighborState.clear();
	}
	State::State(std::string stateName)
	{
		mStateName = stateName;
		mIsCurrent = false;
		mTrigger = NULL;
		mAnimation = 0;
		mNeighborState.clear();
	}
	State::State(std::string stateName, char trigger)
	{
		mStateName = stateName;
		mIsCurrent = false;
		mTrigger = trigger;
		mAnimation = 0;
		mNeighborState.clear();
	}
	State::State(std::string stateName, char trigger, int Animation)
	{
		mStateName = stateName;
		mIsCurrent = false;
		mTrigger = trigger;
		mAnimation = Animation;
		mNeighborState.clear();
	}
	State::~State()
	{
		// delete ;
	}
	void State::LinkState(State* state) 
	{
		mNeighborState.push_back(state);
		state->mNeighborState.push_back(this);
	}
	void State::SetAnimation(int animation)
	{
		mAnimation = animation;
	}
	void State::SetCurrentState()
	{
		mIsCurrent = true;
	}
	void State::CancelCurrentState()
	{
		mIsCurrent = false;
	}
	State* State::SearchNewCurrentState(char trigger)
	{
		for (int i = 0; i < mNeighborState.size(); ++i)
		{
			if (mNeighborState[i]->GetTrigger() == trigger)
			{
				return mNeighborState[i];
			}
		}
		return nullptr;
	}
	void State::UpdateState(State* newCurrentState)
	{
		if (newCurrentState == nullptr)
		{
			return;
		}
		mIsCurrent = false;
		newCurrentState->SetBool(true);
	}
	std::string State::GetStateName() 
	{
		return mStateName;
	}
	char State::GetTrigger()
	{
		return mTrigger;
	}
	void State::SetBool(bool boolState)
	{
		mIsCurrent = boolState;
	}
	int State::ShowAnimation()
	{
		return mAnimation;
	}
}