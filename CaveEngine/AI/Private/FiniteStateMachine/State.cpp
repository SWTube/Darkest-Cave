/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "FiniteStateMachine/State.h"

namespace cave
{
	State::State()
	{
		mAnimation = true;
		mNeighborState.clear();
	}
	State::State(bool Animation)
	{
		mAnimation = Animation;
		mNeighborState.clear();
	}
	State::~State() 
	{
		// delete ;
	}
}