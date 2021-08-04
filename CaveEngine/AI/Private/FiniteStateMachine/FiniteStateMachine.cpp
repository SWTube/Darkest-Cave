/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <iostream>
#include "FiniteStateMachine/FiniteStateMachine.h"

namespace cave
{
	FiniteStateMachine::FiniteStateMachine() 
	{
		mCurrentState = nullptr;
		mNode.clear();
		mCheckList.clear();
	}
	FiniteStateMachine::FiniteStateMachine(State* currentState)
	{
		mCurrentState = currentState;
		mNode.clear();
		mCheckList.clear();
	}
	FiniteStateMachine::~FiniteStateMachine()
	{
		// delete
	}
	void FiniteStateMachine::addState(State* state)
	{
		mNode.push_back(state);
		mCheckList.push_back(std::pair<std::string, bool>(state->getStateName(), false));
	}
	void FiniteStateMachine::updateCurrentState(char trigger)
	{
		State* newCurrentState = mCurrentState->searchNewCurrentState(trigger);
		if (newCurrentState == nullptr)
		{
			return;
		}
		mCurrentState->updateState(newCurrentState);
		mCurrentState = newCurrentState;
	}
	State* FiniteStateMachine::returnCurrentState()
	{
		return mCurrentState;
	}
}
