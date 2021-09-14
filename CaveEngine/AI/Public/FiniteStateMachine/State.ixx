/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include <iostream>
#include <vector>

export module State;

export namespace cave
{
	class State
	{
	public:
		State()
		{
			mStateName = "";
			mIsCurrent = false;
			mTrigger = NULL;
			mAnimation = 0;
			mNeighborState.clear();
		}
		State(std::string stateName)
		{
			mStateName = stateName;
			mIsCurrent = false;
			mTrigger = NULL;
			mAnimation = 0;
			mNeighborState.clear();
		}
		State(std::string stateName, char trigger)
		{
			mStateName = stateName;
			mIsCurrent = false;
			mTrigger = trigger;
			mAnimation = 0;
			mNeighborState.clear();
		}
		State(std::string stateName, char trigger, int Animation)
		{
			mStateName = stateName;
			mIsCurrent = false;
			mTrigger = trigger;
			mAnimation = Animation;
			mNeighborState.clear();
		}
		~State()
		{
			// delete ;
		}
		void LinkState(State* state)
		{
			mNeighborState.push_back(state);
			state->mNeighborState.push_back(this);
		}
		void SetAnimation(int animation)
		{
			mAnimation = animation;
		}
		void SetCurrentState()
		{
			mIsCurrent = true;
		}
		void CancelCurrentState()
		{
			mIsCurrent = false;
		}
		State* SearchNewCurrentState(char trigger)
		{
			for (int i = 0; i < mNeighborState.size(); ++i)
			{
				if (mNeighborState[i]->GetTrigger() == trigger)
				{
					return mNeighborState[i];
				}
			}
			return nullptr;
		}
		void UpdateState(State* newCurrentState)
		{
			if (newCurrentState == nullptr)
			{
				return;
			}
			mIsCurrent = false;
			newCurrentState->SetBool(true);
		}
		void LinkStateOneway(State* state)
		{
			mNeighborState.push_back(state);
		}
		std::string GetStateName()
		{
			return mStateName;
		}
		char GetTrigger()
		{
			return mTrigger;
		}
		void SetBool(bool boolState)
		{
			mIsCurrent = boolState;
		}
		int ShowAnimation()
		{
			return mAnimation;
		}

	private:
		int mAnimation;
		bool mIsCurrent;
		char mTrigger;
		std::string mStateName;
		std::vector<State*> mNeighborState;

	};
}
