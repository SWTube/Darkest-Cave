/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once
#ifdef __WIN32__
import State;
import cave.Core.Containers.HashTable;
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
		State(std::string stateName);
		State(std::string stateName, char trigger);
		State(std::string stateName, char trigger, int Animation);
		virtual ~State();
		void LinkState(State* state, FiniteStateMachine* hash);
		void LinkStateOneway(State* state, FiniteStateMachine* hash);
		void SetAnimation(int animation);
		void SetCurrentState();
		void CancelCurrentState();
		State* SearchNewCurrentState(char trigger, FiniteStateMachine hash);
		void UpdateState(State* newCurrentState);
		std::string GetStateName();
		char GetTrigger();
		void SetBool(bool boolState);
		int ShowAnimation();
		
	private:
		HashTable hashT(HASHMAX, 2);
		int mAnimation;
		bool mIsCurrent;
		char mTrigger;
		std::string mStateName;
		std::vector<State*> mNeighborState;

	};
}
#endif