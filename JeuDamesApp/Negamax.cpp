#include "Negamax.h"

int columnOrder[7] = { 2, 3, 4, 1, 5, 0, 6 };

int Negamax::GetBestMove(Board board, TranspositionTable* transpositionTable, unsigned int depth)
{
	std::cout << "NegaMax::GetBestMove" << std::endl;
	return 0;

	/*
	//Avoid instant loose
	if (board.getMoveNumber() == 1)
	{
		return Negamax::GetBestMoveEarlyGame(board);
	}

	//One thread for each column
	std::thread columnThreads[7];

	//Array to store the results of the threads
	int* results = new int[7];

	//Initialize the results array
	for (int i = 0; i < 7; i++)
	{
		results[i] = -1000;
	}

	//For each column, play the move inside it, and create a new thread to calculate the value of the move
	for (int i = 0; i < 7; i++)
	{
		//Check if the move can be played in the column
		if (board.isValidMove(i))
		{
			Board newBoard = board.copy();
			newBoard.Play(i);
			columnThreads[i] = std::thread(NegamaxThread, newBoard, &results[i], transpositionTable, depth);
		}
		else
		{
			columnThreads[i] = std::thread();
		}
	}

	//Join all the threads to wait for them to finish
	for (int i = 0; i < 7; i++)
	{
		if (columnThreads[i].joinable())
		{
			columnThreads[i].join();
		}
	}

	//Print the results of each column
	std::cout << "Results: ";
	for (int i = 0; i < 7; i++)
	{
		std::cout << results[i] << " ";
	}
	std::cout << std::endl;

	int bestMove = 0;
	int bestValue = -1000;

	//Find the best move with the highest value
	for (int i = 0; i < 7; i++)
	{
		if (results[i] == bestValue)
		{
			bestMove = Negamax::compareColumnOrder(i, bestMove);
		}
		else if (results[i] > bestValue)
		{
			bestValue = results[i];
			bestMove = i;
		}
	}
	return bestMove;
	*/
}

int Negamax::GetBestMove_noThreads(Board board, TranspositionTable* transpositionTable, unsigned int depth)
{
	std::cout << "NegaMax::GetBestMove_noThreads" << std::endl;
	return 0;

	/*
	int bestMove = 0;
	int bestValue = -1000;

	for (int i = 0; i < 7; i++)
	{
		if (board.isValidMove(i))
		{
			Board newBoard = board.copy();
			newBoard.Play(i);
			int value = Negamax::Negamax(newBoard, -100000, 100000, transpositionTable, depth - 1);
			std::cout << "Move " << i << " value: " << value << std::endl;
			if (value > bestValue)
			{
				bestValue = value;
				bestMove = i;
			}
		}
	}
	return bestMove;
}

int Negamax::Evaluate(Board terminalBoard)
{
	if (terminalBoard.playerWins())
	{
		return 43 - terminalBoard.getMoveNumber();
	}
	else if (terminalBoard.robotWins())
	{
		return 43 - terminalBoard.getMoveNumber();
	}
	else
	{
		return 0;
	}
	*/
}

int Negamax::Negamax(Board board, int alpha, int beta, TranspositionTable* transpositionTable, unsigned int depth)
{
	std::cout << "NegaMax::Negamax" << std::endl;
	return 0;

	//The transposition table is not working properly, so it is commented out
	//It is supposed to store the values of the boards that have already been evaluated
	//and return the value if the board is already in the table, instead of evaluating it again
	//This is supposed to speed up the algorithm, but it is not
	/*
	if (transpositionTable->contains(board))
	{
		return transpositionTable->get(board);
	}
	*/
	/*
	if (depth == 0 || board.isTerminal())
	{
		int value = Negamax::Evaluate(board);
		return value;
	}
	else
	{
		for (int i = 0; i < 7; i++)
		{
			if (board.isValidMove(i) && board.moveIsWinning(i))
			{
				if (board.getMoveNumber() % 2 == 0)
				{
					return -43 + board.getMoveNumber();
				}
				else
				{
					return 43 - board.getMoveNumber();
				}
			}
		}

		int value = -1000;
		for (int i = 0; i < 7; i++)
		{
			if (board.isValidMove(i))
			{
				Board boardCopy = board.copy();
				boardCopy.Play(i);
				value = std::max(value, -Negamax::Negamax(boardCopy, -beta, -alpha, transpositionTable, depth - 1));
				alpha = std::max(alpha, value);
				if (alpha >= beta)
				{
					continue;
				}
			}
		}*/
		/*
		if (board.isTerminal())
		{
			transpositionTable->put(board, value);
		}*/
		
		//return value;
	//}
}

void Negamax::NegamaxThread(Board board, int* result, TranspositionTable* transpositionTable, unsigned int depth)
{
	*result = Negamax::Negamax(board, -100000, 100000, transpositionTable, depth);
}

int Negamax::compareColumnOrder(int a, int b)
{
	int aIndex = -1;
	int bIndex = -1;
	for (int i = 0; i < 7; i++)
	{
		if (columnOrder[i] == a)
		{
			aIndex = i;
		}
		if (columnOrder[i] == b)
		{
			bIndex = i;
		}
	}
	if (aIndex < bIndex)
	{
		return columnOrder[aIndex];
	}
	else
	{
		return columnOrder[bIndex];
	}
}

int Negamax::GetBestMoveEarlyGame(Board board)
{
	if (board.getPiece(3, 0) == 1)
	{
		return 2;
	}
	else
	{
		return 3;
	}
}