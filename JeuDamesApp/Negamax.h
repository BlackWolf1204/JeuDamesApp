#pragma once

#include <thread>
#include <iostream>
#include "Board.h"

namespace Negamax
{
	/// <summary>
	/// Get the best move for the current player, using the negamax algorithm.
	/// </summary>
	/// <param name="board">Board to evaluate</param>
	/// <param name="depth">Depth of the search</param>
	/// <returns>The positions where to move the piece (piece at the first position given in the vector)</returns>
	std::vector<int> GetBestMove(Board board, unsigned int depth);


	std::vector<int> GetBestMove_noThreads(Board board, unsigned int depth);

	/// <summary>
	/// Evaluate a board by giving it a score corresponding to the state of the board
	/// </summary>
	/// <param name="board">Board to evaluate</param>
	/// <returns>Score of the board</returns>
	int Evaluate(Board terminalBoard);

	/// <summary>
	/// Recursive function to find the best move for the current player.
	/// </summary>
	/// <param name="board">Board to evaluate</param>
	/// <param name="alpha">Alpha-beta pruning parameter</param>
	/// <param name="beta">Alpha-beta pruning parameter</param>
	/// <param name="ptr">Next empty position pointer of the array storing the positions sweep of the first move search</param>
	/// <param name="posSweep">Actual position of the piece doing the sweep, -1 if no current sweep</param>
	/// <param name="playing">Indicate if it's the robot (0) or the player (1) that will do the move</param>
	/// <param name="depth">Depth of the search</param>
	/// <returns>The score of the board</returns>
	int Negamax(Board board, int alpha, int beta, int* ptr, int posSweep, int playing, unsigned int depth);

	/// <summary>
	/// Launche the threads running the negamax function. One thread is created for each column
	/// </summary>
	/// <param name="board">Board to evaluate</param>
	/// <param name="result">Int array to store each column result from each thread</param>
	/// <param name="ptr">Next empty position pointer of the array storing the positions sweep of the first move search</param>
	/// <param name="posSweep">Actual position of the piece doing the sweep, -1 if no current sweep</param>
	/// <param name="playing">Indicate if it's the robot (0) or the player that will do the mmove</param>
	/// <param name="depth"></param>
	void NegamaxThread(Board board, int* result, int* ptr, int posSweep, int playing, unsigned int depth);

	std::vector<int> GetBestMoveEarlyGame(Board board);
}