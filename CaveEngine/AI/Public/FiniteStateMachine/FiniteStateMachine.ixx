/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include <iostream>
#include <string>
#include <vector>

#include "State.h"

export module FiniteStateMachine;

export namespace cave
{
	class FiniteStateMachine
	{
	public:
		FiniteStateMachine()
		{
			mCurrentState = nullptr;
			mNode.clear();
			mCheckList.clear();
		}
		FiniteStateMachine(State* currentState)
		{
			mCurrentState = currentState;
			mNode.clear();
			mCheckList.clear();
		}
		~FiniteStateMachine()
		{
			delete mCurrentState;
		}
		void AddState(State* state)
		{
			mNode.push_back(state);
			mCheckList.push_back(std::pair<std::string, bool>(state->GetStateName(), false));
		}
		void UpdateCurrentState(char trigger)
		{
			State* nextState = mCurrentState->SearchNewCurrentState(trigger);
			if (nextState == nullptr)
			{
				return;
			}
			mCurrentState->UpdateState(nextState);
			mCurrentState = nextState;
		}
		State* ReturnCurrentState()
		{
			return mCurrentState;
		}

	private:
		State* mCurrentState;
		std::vector<State*> mNode;
		std::vector<std::pair<std::string, bool>> mCheckList;
	};
}

