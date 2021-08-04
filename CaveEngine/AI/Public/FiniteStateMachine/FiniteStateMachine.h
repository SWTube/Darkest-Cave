/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

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
		void addState(State state);
		void updateCurrentState(char trigger);
		State* checkCurrentState();

	private:
		State* mCurrentState;
		std::vector<State> mNode;
		std::vector<std::pair<std::string, bool>> mCheckList;
	};
}
