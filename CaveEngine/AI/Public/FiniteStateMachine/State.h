/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

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

// fsm 이 가지는 변수들을 가질 것, trigger 햇반 (int, float, bool 다양)
// map 형식으로 isJump == true, false
// root node 하나 필요, 그래프의 시작점 기본상태 아님
// root ==> idle (가만히 서있는 상태)
// idle -> jump, idle -> jump 
// 인접한 노드 탐색, 맞는게 없으면 넘어가지 않음
// such as bfs
