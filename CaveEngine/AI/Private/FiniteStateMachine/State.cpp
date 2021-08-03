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
	void State::setAnimation()
	{

	}
	void State::setCurrentState()
	{
		mIsCurrent = true;
	}
	void State::cancelCurrentState()
	{
		mIsCurrent = false;
	}
	std::string State::getStateName() 
	{
		return mStateName;
	}
}