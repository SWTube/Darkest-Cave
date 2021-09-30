/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include <iostream>
#include <vector>
#include<unordered_map>
export module State;

import cave.Core.String;
export namespace cave
{
	
	class State
	{
	typedef std::unordered_map<State*,bool> hmap;
	public:
		State()
		{
			mStateName = "";
			mIsCurrent = false;
			mTrigger = NULL;
			mAnimation = 0;
			hm.clear();
		}
		State(String stateName)
		{
			mStateName = stateName;
			mIsCurrent = false;
			mTrigger = NULL;
			mAnimation = 0;
			hm.clear();
		}
		State(String stateName, char trigger)
		{
			mStateName = stateName;
			mIsCurrent = false;
			mTrigger = trigger;
			mAnimation = 0;
			hm.clear();
		}
		State(String stateName, char trigger, int Animation)
		{
			mStateName = stateName;
			mIsCurrent = false;
			mTrigger = trigger;
			mAnimation = Animation;
			hm.clear();
		}
		~State()
		{
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
		void LinkState(State* state,bool isSingle)
		{
			hm.insert(hmap::value_type(state,isSingle));
		}
		bool IsLink(State* state)
		{
			State* isFind = hm.find(state)->first;
			if (isFind == nullptr)
			{
				return false;
			}
			return true;
		}
		/*
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
		}*/
		void UpdateState(State* newCurrentState)
		{
			if (newCurrentState == nullptr)
			{
				return;
			}
			mIsCurrent = false;
			newCurrentState->SetBool(true);
		}
		/*void LinkStateOneway(State* state)
		{
			mNeighborState.push_back(state);
		}*/
		String GetStateName()
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
		hmap hm;
		int mAnimation;
		bool mIsCurrent;
		char mTrigger;
		String mStateName;

	};
}
