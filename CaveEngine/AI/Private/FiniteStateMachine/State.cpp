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
	void State::setAnimation(int animation)
	{
		mAnimation = animation;
	}
	void State::setCurrentState()
	{
		mIsCurrent = true;
	}
	void State::cancelCurrentState()
	{
		mIsCurrent = false;
	}
	State* State::searchNewCurrentState(char trigger)
	{
		for (int i = 0; i < mNeighborState.size(); ++i)
		{
			if (mNeighborState[i]->getTrigger() == trigger)
			{
				return mNeighborState[i];
			}
		}
		return nullptr;
	}
	void State::updateState(State* newCurrentState)
	{
		if (newCurrentState == nullptr)
		{
			return;
		}
		mIsCurrent = false;
		newCurrentState->setBool(true);
	}
	std::string State::getStateName() 
	{
		return mStateName;
	}
	char State::getTrigger()
	{
		return mTrigger;
	}
	void State::setBool(bool boolState)
	{
		mIsCurrent = boolState;
	}
	int State::showAnimation()
	{
		return mAnimation;
	}
}