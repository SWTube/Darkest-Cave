/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once
#ifdef __WIN32__
import State;
#else
#include <iostream>
#include <vector>

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
		void LinkState(State* state);
		void LinkStateOneway(State* state);
		void SetAnimation(int animation);
		void SetCurrentState();
		void CancelCurrentState();
		State* SearchNewCurrentState(char trigger);
		void UpdateState(State* newCurrentState);
		std::string GetStateName();
		char GetTrigger();
		void SetBool(bool boolState);
		int ShowAnimation();
		
	private:
		int mAnimation;
		bool mIsCurrent;
		char mTrigger;
		std::string mStateName;
		std::vector<State*> mNeighborState;

	};
}
#endif