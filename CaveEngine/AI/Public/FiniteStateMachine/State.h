/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once
#ifdef __WIN32__
import cave.Core.String;
#else
#include <iostream>
#include <vector>
#include"FiniteStateMachine.h"
struct HASHMAX = 100;
namespace cave
{
	class State
	{
	public:
		State();
		State(String stateName);
		State(String stateName, char trigger);
		State(String stateName, char trigger, int Animation);
		virtual ~State();
		//void LinkState(State* state, FiniteStateMachine* hash);
		//void LinkStateOneway(State* state, FiniteStateMachine* hash);
		void SetAnimation(int animation);
		void SetCurrentState();
		void CancelCurrentState();
		//State* SearchNewCurrentState(char trigger);
		void UpdateState(State* newCurrentState);
		String GetStateName();
		char GetTrigger();
		void SetBool(bool boolState);
		int ShowAnimation();
		
	private:
		int mAnimation;
		bool mIsCurrent;
		char mTrigger;
		String mStateName;
		//std::vector<State*> mNeighborState;

	};
}
#endif