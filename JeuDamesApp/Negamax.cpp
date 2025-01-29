#include "Negamax.h"
#include <chrono>


std::vector<int> Negamax::GetBestMove(Board board, unsigned int depth)
{	
	// If early game
	if (board.getMoveNumber() == 0)
		return GetBestMoveEarlyGame(board);

	std::vector<int> pieces;
	std::vector<std::vector<int>> allPositionsMove;
	std::vector<std::vector<int>> allPositionsEat;
	int canEat = 0;

	// Look all possible moves of robot pieces
	for (int i = 0; i < BOARDSIZE; i++)
	{
		for (int j = 0; j < BOARDSIZE; j++)
		{
			if (board.getPiece(j, i) % 2 == 0)
			{
				std::vector<std::vector<int>> positions = board.canMoveEat(j, i);
				pieces.push_back(j + i * BOARDSIZE);
				allPositionsMove.push_back(positions[0]);
				allPositionsEat.push_back(positions[1]);
				// keep in mind that a piece can eat
				if (positions[1].size() > 0)
					canEat = 1;
			}
		}
	}

	//One thread for each ally piece possible position
	std::thread pieceThreads[64];

	//Array to store the results of the threads
	int* results = new int[64];

	//Array to store the positions move of the threads
	std::vector<int*> movePositions;
	
	//Initialize the results array
	for (int i = 0; i < 64; i++)
	{
		int* pos = new int[12];
		for (int j = 0; j < 12; j++)
		{
			pos[j] = -1;
		}
		movePositions.push_back(pos);
		results[i] = -1000;
	}

	int ind = 0;
	std::vector<int> canSweep;

	//Force to eat if one piece can
	if (canEat)
	{
		for (size_t p = 0;p < allPositionsEat.size(); p++)
		{
			for (size_t e = 0; e < allPositionsEat[p].size(); e++)
			{
				Board newBoard = board.copy();
				movePositions[ind][0] = pieces[p];
				movePositions[ind][1] = allPositionsEat[p][e];
				canSweep = newBoard.Play(pieces[p], allPositionsEat[p][e]);
				bool upgraded = newBoard.newKing();
				// Can't continue to move if the piece become a king
				if (upgraded)
					pieceThreads[ind] = std::thread(NegamaxThread, newBoard, &results[ind], nullptr, -1, 1, depth - 1);
				else
				{
					int* ptr = movePositions[ind];
					ptr += 2;
					pieceThreads[ind] = std::thread(NegamaxThread, newBoard, &results[ind], ptr, allPositionsEat[p][e], 0, depth);
				}
				ind += 1;
			}
		}
	}
	else
	{
		for (size_t p = 0; p < allPositionsMove.size(); p++)
		{
			for (size_t e = 0; e < allPositionsMove[p].size(); e++)
			{
				Board newBoard = board.copy();
				newBoard.Play(pieces[p], allPositionsMove[p][e]);
				movePositions[ind][0] = pieces[p];
				movePositions[ind][1] = allPositionsMove[p][e];
				pieceThreads[ind] = std::thread(NegamaxThread, newBoard, &results[ind], nullptr, -1, 1, depth);
				ind += 1;
				//std::this_thread::sleep_for(std::chrono::seconds(10));
			}
		}
	}

	//Join all the threads to wait for them to finish
	for (int i = 0; i < ind; i++)
	{
		if (pieceThreads[i].joinable())
		{
			pieceThreads[i].join();
		}
	}

	//Print the results and list of positions of each move
	for (int i = 0; i < ind; i++)
	{
		std::cout << "Results: " << results[i] << " -> [";
		int j = 0;
		while (movePositions[i][j] != -1)
		{
			std::cout << movePositions[i][j] << " ";
			j++;
		}

		std::cout << "]" << std::endl;
	}

	std::vector<int> bestMove;
	int bestValue = -1000;

	//Find the best move with the highest value
	for (int i = 0; i < ind; i++)
	{
		if (results[i] > bestValue)
		{
			bestMove.clear();
			bestValue = results[i];
			int j = 0;
			while (movePositions[i][j] != -1)
			{
				bestMove.push_back(movePositions[i][j]);
				j++;
			}
		}
	}
	return bestMove;
}

std::vector<int> Negamax::GetBestMove_noThreads(Board board, unsigned int depth)
{
	std::vector<int> pieces;
	std::vector<std::vector<int>> allPositionsMove;
	std::vector<std::vector<int>> allPositionsEat;
	int canEat = 0;

	int alpha = -100000;
	int beta = 100000;

	// If early game
	if (board.getMoveNumber() == 0)
		return GetBestMoveEarlyGame(board);

	// Look all possible moves of robot pieces
	for (int i = 0; i < BOARDSIZE; i++)
	{
		for (int j = 0; j < BOARDSIZE; j++)
		{
			if (board.getPiece(j, i) % 2 == 0)
			{
				std::vector<std::vector<int>> positions = board.canMoveEat(j, i);
				pieces.push_back(j + i * BOARDSIZE);
				allPositionsMove.push_back(positions[0]);
				allPositionsEat.push_back(positions[1]);
				// keep in mind that a piece can eat
				if (positions[1].size() > 0)
					canEat = 1;
			}
		}
	}

	int ind = 0;
	std::vector<int> canSweep;

	std::vector<int> bestMove;
	int bestValue = -1000;

	//Force to eat if one piece can
	if (canEat)
	{
		for (size_t p = 0; p < allPositionsEat.size(); p++)
		{
			for (size_t e = 0; e < allPositionsEat[p].size(); e++)
			{
				Board newBoard = board.copy();
				int movePositions[12];
				for (int i = 0; i < 12; i++)
					*(movePositions + i) = -1;
				movePositions[0] = pieces[p];
				movePositions[1] = allPositionsEat[p][e];
				canSweep = newBoard.Play(pieces[p], allPositionsEat[p][e]);
				bool upgraded = newBoard.newKing();
				int value;
				// Can't continue to move if the piece become a king
				if (upgraded)
					value = Negamax(newBoard, alpha, beta, nullptr, -1, 1, depth - 1);
				else
				{
					int* ptr = movePositions;
					ptr += 2;
					value = -Negamax(newBoard, alpha, beta, ptr, allPositionsEat[p][e], 0, depth);
				}
				ind += 1;

				std::cout << "Result : " << value << " -> [";
				int j = 0;
				while (movePositions[j] != -1)
				{
					std::cout << movePositions[j] << " ";
					j++;
				}
				std::cout << "]" << std::endl;

				if (value >= bestValue)
				{
					bestMove.clear();
					bestValue = value;
					int j = 0;
					while (movePositions[j] != -1)
					{
						bestMove.push_back(movePositions[j]);
						j++;
					}
				}
			}
		}
	}
	else
	{
		for (size_t p = 0; p < allPositionsMove.size(); p++)
		{
			for (size_t e = 0; e < allPositionsMove[p].size(); e++)
			{
				Board newBoard = board.copy();
				newBoard.Play(pieces[p], allPositionsMove[p][e]);
				newBoard.newKing();
				int movePositions[12];
				for (int i = 0; i < 12; i++)
					*(movePositions + i) = -1;
				movePositions[0] = pieces[p];
				movePositions[1] = allPositionsMove[p][e];
				int value = Negamax(newBoard, alpha, beta, nullptr, -1, 1, depth - 1);

				std::cout << "Result " << value << " ->[";
				int j = 0;
				while (movePositions[j] != -1)
				{
					std::cout << movePositions[j] << " ";
					j++;
				}
				std::cout << "]" << std::endl;

				if (value >= bestValue)
				{
					bestMove.clear();
					bestValue = value;
					int j = 0;
					while (movePositions[j] != -1)
					{
						bestMove.push_back(movePositions[j]);
						j++;
					}
				}
			}
		}
	}

	return bestMove;
}

int Negamax::Evaluate(Board board)
{
	int capped = board.numCaptured(0);
	int potential = board.possibleMoves(0) - board.possibleMoves(1);
	int men = board.numMen(0) - board.numMen(1);
	int kings = board.numKings(0) - board.numKings(1);
	int caps = board.capturables(0) - board.capturables(1);
	int semicaps = 12 - board.uncapturables(0) - board.capturables(1) - board.numCaptured(1);
	int uncaps = board.uncapturables(0) - board.uncapturables(1);
	int mid = board.atMiddle(0) - board.atMiddle(1);
	int far = board.atEnemy(0) - board.atEnemy(1);
	int won = board.robotWins();

	int score = 4 * capped + potential + men + 3 * kings + caps + 2 * semicaps + 3 * uncaps + 2 * mid + 3 * far + 100 * won;

	return score;
}

int Negamax::Negamax(Board board, int alpha, int beta, int* ptr, int posSweep, int playing, unsigned int depth)
{
	int value = -1000;
	if (depth == 0 || board.isTerminal())
	{
		value = Negamax::Evaluate(board);
	}
	else
	{
		std::vector<int> pieces;
		std::vector<std::vector<int>> allPositionsMove;
		std::vector<std::vector<int>> allPositionsEat;
		int canEat = 0;

		// There is a sweep and still related to the first move made in the thread
		if (posSweep != -1 && ptr != nullptr)
		{
			std::vector<std::vector<int>> positions = board.canMoveEat(posSweep % BOARDSIZE, (int)(posSweep / BOARDSIZE));
			pieces.push_back(posSweep);
			allPositionsMove.push_back(positions[0]);
			allPositionsEat.push_back(positions[1]);
			// keep in mind that a piece can eat
			if (positions[1].size() > 0)
				canEat = 1;
		}
		else
		{
			// Look all possible moves of player pieces
			for (int i = 0; i < BOARDSIZE; i++)
			{
				for (int j = 0; j < BOARDSIZE; j++)
				{
					if (board.getPiece(j, i) % 2 == playing)
					{
						std::vector<std::vector<int>> positions = board.canMoveEat(j, i);
						pieces.push_back(j + i * BOARDSIZE);
						allPositionsMove.push_back(positions[0]);
						allPositionsEat.push_back(positions[1]);
						// keep in mind that a piece can eat
						canEat += positions[1].size();
					}
				}
			}
		}

		//Force to eat if one piece can
		if (canEat)
		{
			for (size_t p = 0; p < allPositionsEat.size(); p++)
			{
				for (size_t e = 0; e < allPositionsEat[p].size(); e++)
				{
					Board boardCopy = board.copy();
					boardCopy.Play(pieces[p], allPositionsEat[p][e]);

					// Keep in mind the sweep moves related to the first move of the thread
					if (ptr != nullptr)
					{
						*ptr = allPositionsEat[p][e];
						ptr++;
					}

					bool upgraded = boardCopy.newKing();
					// Can't continue to move if the piece become a king
					if (upgraded)
						// Change the current player doing the move
						value = std::max(value, -Negamax(boardCopy, -beta, alpha, nullptr, -1, std::abs(playing - 1), depth - 1));
					else
						value = std::max(value, Negamax(boardCopy, alpha, beta, ptr, allPositionsEat[p][e], playing, depth));
					alpha = std::max(alpha, value);
					if (alpha >= beta)
					{
						continue;
					}
				}
			}
		}
		else
		{
			// If there was a sweep but can't continue, look the possible moves of the other player
			if (posSweep != -1)
			{
				value = std::max(value, -Negamax(board, -beta, alpha, nullptr, -1, std::abs(playing - 1), depth));
				alpha = std::max(alpha, value);
			}
			// Else play the possible moves
			else
			{
				for (size_t p = 0; p < allPositionsMove.size(); p++)
				{
					for (size_t e = 0; e < allPositionsMove[p].size(); e++)
					{
						Board boardCopy = board.copy();
						boardCopy.Play(pieces[p], allPositionsMove[p][e]);
						value = std::max(value, -Negamax(boardCopy, -beta, alpha, nullptr, -1, std::abs(playing - 1), depth - 1));
						alpha = std::max(alpha, value);
						if (alpha >= beta)
						{
							continue;
						}
					}
				}
			}
		}
	}

	return value;
}

void Negamax::NegamaxThread(Board board, int* result, int* ptr, int posSweep, int playing, unsigned int depth)
{
	if (playing == 0)
		*result = -Negamax::Negamax(board, -100000, 100000, ptr, posSweep, playing, depth);
	else
		*result = Negamax::Negamax(board, -100000, 100000, ptr, posSweep, playing, depth);
}

std::vector<int> Negamax::GetBestMoveEarlyGame(Board board)
{
	std::vector<int> bestMove;
	if (board.getPiece(4, 4) == 1)
	{
		// Counter best player move
		if (board.getPiece(5, 5) == 0)
		{
			std::cout << "First best move" << std::endl;
			bestMove.push_back(2 + 2 * BOARDSIZE);
			bestMove.push_back(1 + 3 * BOARDSIZE);
		}
		// Counter fourth best player move
		else if (board.getPiece(3, 5) == 0)
		{
			std::cout << "Fourth best move" << std::endl;
			bestMove.push_back(0 + 2 * BOARDSIZE);
			bestMove.push_back(1 + 3 * BOARDSIZE);
		}
	}
	else if (board.getPiece(2, 4) == 1)
	{
		// Counter second best player move
		if (board.getPiece(1, 5) == 0)
		{
			std::cout << "Second best move" << std::endl;
			bestMove.push_back(2 + 2 * BOARDSIZE);
			bestMove.push_back(3 + 3 * BOARDSIZE);
		}
		// Counter fifth best player move
		else if (board.getPiece(3, 5) == 0)
		{
			std::cout << "Fifth best move" << std::endl;
			bestMove.push_back(6 + 2 * BOARDSIZE);
			bestMove.push_back(5 + 3 * BOARDSIZE);
		}
	}
	else if (board.getPiece(6, 4) == 1)
	{
		//Counter third best player move
		if (board.getPiece(5, 5) == 0)
		{
			std::cout << "Third best move" << std::endl;
			bestMove.push_back(4 + 2 * BOARDSIZE);
			bestMove.push_back(3 + 3 * BOARDSIZE);
		}
		// Counter sixth best player move
		else if (board.getPiece(7, 5) == 0)
		{
			std::cout << "Sixth best move" << std::endl;
			bestMove.push_back(6 + 2 * BOARDSIZE);
			bestMove.push_back(7 + 3 * BOARDSIZE);
		}
	}
	// Counter worst player move
	else if (board.getPiece(0, 4) == 1 && board.getPiece(1, 5) == 0)
	{
		bestMove.push_back(2 + 2 * BOARDSIZE);
		bestMove.push_back(3 + 3 * BOARDSIZE);
	}

	return bestMove;
}