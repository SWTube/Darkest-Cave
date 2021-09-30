/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include <iostream>
#include <vector>
#include<unordered_map>
#include<string>
export module FiniteStateMachine;


import State;
import cave.Core.String;
import cave.Core.Containers.Hash;
import cave.Core.Containers.HashTable;
export namespace cave
{
	typedef std::unordered_map<char, State* > hmap;
	typedef std::unordered_map<State*, State*> lmap;
	class FiniteStateMachine
	{
	public:
		FiniteStateMachine()
		{
			mCurrentState = nullptr;
			hm.clear();
			lm.clear();
		}
		FiniteStateMachine(State* currentState)
		{
			mCurrentState = currentState;
			hm.clear();
			lm.clear();
		}
		~FiniteStateMachine()
		{
			delete mCurrentState;
		}
		void AddState(State* state)
		{
			char c = state->GetTrigger();
			hm.insert(hmap::value_type(c, state));	
		}
		void UpdateCurrentState(char trigger)
		{
			State* nextState = hm.find(trigger)->second;
			if (nextState == nullptr||mCurrentState->IsLink(nextState)==false)
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
		hmap hm;
		lmap lm;
		State* mCurrentState;
		std::vector<State*> mNode;
	};
}

