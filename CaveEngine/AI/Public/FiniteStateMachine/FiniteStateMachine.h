/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#ifdef __WIN32__
import FiniteStateMachine;
import cave.Core.Containers.HashTable;
#else
struct MAXHASH = 100;
#include <iostream>
#include <string>
#include <vector>
#include "State.h"
namespace cave
{
	class FiniteStateMachine
	{
	public:
		FiniteStateMachine();
		FiniteStateMachine(State* currentState);
		virtual ~FiniteStateMachine();
		void AddState(State* state);
		void UpdateCurrentState(char trigger);
		void LinkState(State* state1, State* state2);
		void LinkStateOneway(State* state1, State* state2);
		State* ReturnCurrentState();
		HshTable* ReturnHash();
	private:
		HashTable hashT(MAXHASH, 2);
		State* mCurrentState;
		std::vector<State*> mNode;
		std::vector<std::pair<std::string, bool>> mCheckList;
	};
}
#endif