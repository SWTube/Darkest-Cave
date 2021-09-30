/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <iostream>
#include "FiniteStateMachine/FiniteStateMachine.h"

#ifdef __UNIX__

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
	void FiniteStateMachine::LinkState(State* state1, State* state2)
	{
		hashT.insert(state1, state2);
		hashT.insert(state2, state1);
	}
	void FiniteStateMachine::LinkStateOneway(State* state1, State* state2)
	{
		hashT.insert(state1, state2);
	}
	FiniteStateMachine::~FiniteStateMachine()
	{
		// delete
	}
	void FiniteStateMachine::AddState(State* state)
	{
		mNode.push_back(state);
		mCheckList.push_back(std::pair<std::string, bool>(state->GetStateName(), false));
	}
	void FiniteStateMachine::UpdateCurrentState(char trigger)
	{
		State isFind = hashT.Find(mCurrentState);
		if (hashT.Find(mCurrentState).GetTrigger() == trigger)
		{
			State* nextState = hashT.Find(mCurretnState);
		}
		if (nextState == nullptr)
		{
			return;
		}
		mCurrentState->UpdateState(nextState);
		mCurrentState = nextState;
	}
	State* FiniteStateMachine::ReturnCurrentState()
	{
		return mCurrentState;
	}
	HashTable* FiniteStateMachine::ReturnHash()
	{
		return hashT;
	}
}
#endif