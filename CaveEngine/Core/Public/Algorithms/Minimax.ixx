/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include "CoreTypes.h"
#include "Containers/Array.h"

export module Minimax;

import TreeNode;

namespace cave
{
	class IMove
	{
	};

	class IBoard
	{
	public:
		virtual ~IBoard() = default;
		virtual void MakeMove(const IMove& move) = 0;
		virtual void UnmakeMove(const IMove& move) = 0;
		virtual int32_t Evaluate() const = 0;
	};

	class IPlayer
	{
	public:
		virtual ~IPlayer() = default;
		virtual TArray<IMove>& GetPossibleMoves(const IBoard& board) const = 0;
		virtual bool HasWon(const IBoard& board) const = 0;
	};

	export class Minimax
	{
	public:
		static int32_t GetMax(uint32_t maxDepth, uint32_t depth, IBoard& currentBoard, const IPlayer& player, const IPlayer& opponent);
		static int32_t GetMin(uint32_t maxDepth, uint32_t depth, IBoard& currentBoard, const IPlayer& player, const IPlayer& opponent);
		static int32_t GetAlphaBetaMax(uint32_t maxDepth, uint32_t depth, int32_t alpha, int32_t beta, IBoard& currentBoard, const IPlayer& player, const IPlayer& opponent);
		static int32_t GetAlphaBetaMin(uint32_t maxDepth, uint32_t depth, int32_t alpha, int32_t beta, IBoard& currentBoard, const IPlayer& player, const IPlayer& opponent);
		static IMove& GetBestMove();
	protected:
		static IMove msBestMove;
	};

	IMove Minimax::msBestMove = IMove();

	int32_t Minimax::GetMax(uint32_t maxDepth, uint32_t depth, IBoard& currentBoard, const IPlayer& player, const IPlayer& opponent)
	{
		if (depth == 0)
		{
			return currentBoard.Evaluate();
		}

		int32_t max = -INT32_MAX;

		TArray<IMove> moves = player.GetPossibleMoves(currentBoard);

		for (size_t i = 0; i < moves.GetSize(); ++i)
		{
			currentBoard.MakeMove(moves[i]);

			if (player.HasWon(currentBoard))
			{
				max = currentBoard.Evaluate();
				currentBoard.UnmakeMove(moves[i]);

				if (maxDepth == depth)
				{
					msBestMove = moves[i];
				}

				return max;
			}

			int32_t score = GetMin(maxDepth, depth - 1, currentBoard, opponent, player);

			if (score > max)
			{
				max = score;

				if (maxDepth == depth)
				{
					msBestMove = moves[i];
				}
			}

			currentBoard.UnmakeMove(moves[i]);
		}

		return max;
	}

	int32_t Minimax::GetMin(uint32_t maxDepth, uint32_t depth, IBoard& currentBoard, const IPlayer& player, const IPlayer& opponent)
	{
		if (depth == 0)
		{
			return -currentBoard.Evaluate();
		}

		int32_t min = INT32_MAX;

		TArray<IMove> moves = player.GetPossibleMoves(currentBoard);

		for (size_t i = 0; i < moves.GetSize(); ++i)
		{
			currentBoard.MakeMove(moves[i]);

			if (player.HasWon(currentBoard))
			{
				min = currentBoard.Evaluate();
				currentBoard.UnmakeMove(moves[i]);

				if (maxDepth == depth)
				{
					msBestMove = moves[i];
				}

				return min;
			}

			int32_t score = GetMax(maxDepth, depth - 1, currentBoard, opponent, player);

			if (score < min)
			{
				min = score;

				if (maxDepth == depth)
				{
					msBestMove = moves[i];
				}
			}

			currentBoard.UnmakeMove(moves[i]);
		}

		return min;
	}

	int32_t Minimax::GetAlphaBetaMax(uint32_t maxDepth, uint32_t depth, int32_t alpha, int32_t beta, IBoard& currentBoard, const IPlayer& player, const IPlayer& opponent)
	{
		if (depth == 0)
		{
			return currentBoard.Evaluate();
		}

		TArray<IMove> moves = player.GetPossibleMoves(currentBoard);

		for (size_t i = 0; i < moves.GetSize(); ++i)
		{
			if (maxDepth == depth && i == 0)
			{
				msBestMove = moves[i];
			}

			currentBoard.MakeMove(moves[i]);

			if (player.HasWon(currentBoard))
			{
				int32_t evaluate = currentBoard.Evaluate();
				currentBoard.UnmakeMove(moves[i]);

				if (maxDepth == depth)
				{
					msBestMove = moves[i];
				}

				return evaluate;
			}

			int32_t score = GetAlphaBetaMin(maxDepth, depth - 1, alpha, beta, currentBoard, opponent, player);

			if (score >= beta)
			{
				currentBoard.UnmakeMove(moves[i]);
				return beta;
			}

			if (score > alpha)
			{
				alpha = score;

				if (maxDepth == depth)
				{
					msBestMove = moves[i];
				}
			}

			currentBoard.UnmakeMove(moves[i]);
		}

		return alpha;
	}

	int32_t Minimax::GetAlphaBetaMin(uint32_t maxDepth, uint32_t depth, int32_t alpha, int32_t beta, IBoard& currentBoard, const IPlayer& player, const IPlayer& opponent)
	{
		if (depth == 0)
		{
			return -currentBoard.Evaluate();
		}

		TArray<IMove> moves = player.GetPossibleMoves(currentBoard);

		for (size_t i = 0; i < moves.GetSize(); ++i)
		{
			if (maxDepth == depth && i == 0)
			{
				msBestMove = moves[i];
			}

			currentBoard.MakeMove(moves[i]);

			if (player.HasWon(currentBoard))
			{
				int32_t evaluate = currentBoard.Evaluate();
				currentBoard.UnmakeMove(moves[i]);

				if (maxDepth == depth)
				{
					msBestMove = moves[i];
				}

				return evaluate;
			}

			int32_t score = GetAlphaBetaMax(maxDepth, depth - 1, alpha, beta, currentBoard, opponent, player);

			if (score <= alpha)
			{
				currentBoard.UnmakeMove(moves[i]);
				return alpha;
			}

			if (score < beta)
			{
				beta = score;

				if (maxDepth == depth)
				{
					msBestMove = moves[i];
				}
			}

			currentBoard.UnmakeMove(moves[i]);
		}

		return beta;
	}

	IMove& Minimax::GetBestMove()
	{
		return msBestMove;
	}
}