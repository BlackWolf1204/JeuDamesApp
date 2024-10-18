#include <cstdlib>
#include "Board.h"

Board::Board()
{
	playerBoard = 0;
	playerKingBoard = 0;
	robotBoard = 0;
	robotKingBoard = 0;
}

Board Board::copy()
{
	//Not Tested
	Board newBoard;
	newBoard.playerBoard = playerBoard;
	newBoard.playerKingBoard = playerKingBoard;
	newBoard.robotBoard = robotBoard;
	newBoard.robotKingBoard = robotKingBoard;
	return newBoard;
}

void Board::Play(int column, int row, int newColumn, int newRow)
{
	if (isValidMove(column, row, newColumn, newRow))
	{
		// move the piece/king
		int getpiece = getPiece(column, row);
		if (getpiece == 1)
		{
			setPiece(column, row, &playerBoard, false);
			setPiece(column, row, &playerBoard, true);
		}
		else if (getpiece == 3)
		{
			setPiece(column, row, &playerKingBoard, false);
			setPiece(column, row, &playerKingBoard, true);
		}
		else if (getpiece == 2)
		{
			setPiece(column, row, &robotBoard, false);
			setPiece(column, row, &robotBoard, true);
		}
		else if (getpiece == 4)
		{ 
			setPiece(column, row, &robotKingBoard, false);
			setPiece(column, row, &robotKingBoard, true);
		}
		return;
	}

	throw std::exception("Invalid move");

}

bool Board::isTerminal()
{
	if (playerWins() || robotWins() || draw())
	{
		return true;
	}
	return false;
}

bool Board::playerWins()
{
	return checkWin(playerBoard, robotBoard, robotKingBoard);
}

bool Board::robotWins()
{
	return checkWin(robotBoard, playerBoard, playerKingBoard);
}

bool Board::draw()
{
	// possibilty to add the really precise rules leading to a draw
	return false;
}

std::vector<int> Board::canEat(int column, int row)
{
	std::vector<int> positions;
	// king
	if (getPiece(column, row, playerKingBoard) || getPiece(column, row, robotKingBoard))
	{
		int col = 0;
		while (column - (col + 2) >= 0 && row - (col + 2) >= 0)
		{
			if (!getPiece(column - (col + 2), row - (col + 2)))
			{
				// eat opponent piece
				if (getPiece(column, row, playerBoard) && getPiece(column - (col + 1), row - (col + 1), robotBoard))
					positions.push_back((column - (col + 1)) + (row - (col + 1) * BOARDSIZE));
				if (getPiece(column, row, robotBoard) && getPiece(column - (col + 1), row - (col + 1), playerBoard))
					positions.push_back((column - (col + 1)) + (row - (col + 1) * BOARDSIZE));
			}
			col++;
		}
		col = 0;
		while (column - (col + 2) >= 0 && row + (col + 2) < BOARDSIZE)
		{
			if (!getPiece(column - (col + 2), row + (col + 2)))
			{
				// eat opponent piece
				if (getPiece(column, row, playerBoard) && getPiece(column - (col + 1), row + (col + 1), robotBoard))
					positions.push_back((column - (col + 1)) + (row + (col + 1) * BOARDSIZE));
				if (getPiece(column, row, robotBoard) && getPiece(column - (col + 1), row + (col + 1), playerBoard))
					positions.push_back((column - (col + 1)) + (row + (col + 1) * BOARDSIZE));
			}
			col++;
		}
		col = 0;
		while (column + (col + 2) < BOARDSIZE && row - (col + 2) >= 0)
		{
			if (!getPiece(column + (col + 2), row - (col + 2)))
			{
				// eat opponent piece
				if (getPiece(column, row, playerBoard) && getPiece(column + (col + 1), row - (col + 1), robotBoard))
					positions.push_back((column + (col + 1)) + (row - (col + 1) * BOARDSIZE));
				if (getPiece(column, row, robotBoard) && getPiece(column - (col + 1), row - (col + 1), playerBoard))
					positions.push_back((column + (col + 1)) + (row - (col + 1) * BOARDSIZE));
			}
			col++;
		}
		while (column + col < BOARDSIZE && row + col < BOARDSIZE)
		{
			if (!getPiece(column + (col + 2), row + (col + 2)))
			{
				// eat opponent piece
				if (getPiece(column, row, playerBoard) && getPiece(column + (col + 1), row + (col + 1), robotBoard))
					positions.push_back((column + (col + 1)) + (row + (col + 1) * BOARDSIZE));
				if (getPiece(column, row, robotBoard) && getPiece(column + (col + 1), row + (col + 1), playerBoard))
					positions.push_back((column + (col + 1)) + (row + (col + 1) * BOARDSIZE));
			}
			col++;
		}
	}
	else {
		// piece
		if (getPiece(column, row, playerBoard) && column > 1)
		{
			if (row > 1)
				if (!getPiece(column - 2, row - 2) && getPiece(column - 1, row - 1, robotBoard))
					positions.push_back((column - 1) + (row - 1) * BOARDSIZE);
			if (row < 6)
				if (!getPiece(column - 2, row + 2) && getPiece(column - 1, row + 1, robotBoard))
					positions.push_back((column - 1) + (row + 1) * BOARDSIZE);
		}
		if (getPiece(column, row, robotBoard) && column < 6)
		{
			if (row > 1)
				if (!getPiece(column + 2, row - 2) && getPiece(column + 1, row - 1, playerBoard))
					positions.push_back((column + 1) + (row - 1) * BOARDSIZE);
			if (row < 6)
				if (!getPiece(column + 2, row + 2) && getPiece(column + 1, row + 1, playerBoard))
					positions.push_back((column + 1) + (row + 1) * BOARDSIZE);
		}
	}
	return positions;
}

bool Board::isValidMove(int column, int row, int newColumn, int newRow)
{
	// in the board
	if (column < 0 || column > BOARDSIZE-1 || row < 0 || row > BOARDSIZE-1)
	{
		return false;
	}
	if (newColumn < 0 || newColumn > BOARDSIZE - 1 || newRow < 0 || newRow > BOARDSIZE - 1)
	{
		return false;
	}
	// there is a piece in the initial position
	if (getPiece(column, row, playerBoard) || getPiece(column, row, robotBoard))
	{
		return false;
	}
	// there are no pieces in the new position
	if (!getPiece(newColumn, newRow, playerBoard) && !getPiece(newColumn, newRow, robotBoard))
	{
		return false;
	}
	// movements allowed
	return (isValidMoveForward(column, row, newColumn, newRow) || isValidMoveDiagonal(column, row, newColumn, newRow));
}

bool Board::isValidMoveForward(int column, int row, int newColumn, int newRow)
{
	int side = 1;
	if (getPiece(column, row, playerBoard))
		side = -1;

	int diffC = newColumn - column;
	int diffR = newRow - row;

	// Don't move forward (or backward)
	if (diffR != 0)
		return false;

	int piece = getPiece(column, row);
	// piece
	if (piece == 1 || piece == 2)
	{
		// Don't move forward of 1 case
		if (diffC * side != 1)
			return false;
		// There is a piece in front
		if (getPiece(column + 1 * side, row))
			return false;
	}
	// king
	else
	{
		// There is a piece on the trajectory
		if (diffC < 0)
		{
			for (int i = 1; i <= -diffC; i++)
			{
				if (getPiece(column - i, row))
					return false;
			}
		}
		else 
		{
			for (int i = 1; i <= diffC; i++)
			{
				if (getPiece(column + i, row))
					return false;
			}
		}
	}	
	return true;
}

bool Board::isValidMoveDiagonal(int column, int row, int newColumn, int newRow)
{
	int side = 1;
	if (getPiece(column, row, playerBoard))
		side = -1;

	int diffC = newColumn - column;
	int dirCol = (diffC >= 0) - (diffC < 0);
	int diffR = newRow - row;
	int dirRow = (diffR >= 0) - (diffR < 0);

	// Don't move in diagonal
	if (diffR != diffC && diffR != -diffC)
		return false;

	int piece = getPiece(column, row);
	// piece
	if (piece == 1 || piece == 2)
	{
		// Don't move of 2 cases in diagonnal forward
		if (diffC * side != 2)
			return false;
		// Don't eat an opponent piece
		if (getPiece(column, row, playerBoard) && !getPiece(column + side, row + dirRow, robotBoard))
			return false;
		if (getPiece(column, row, robotBoard) && !getPiece(column + side, row + dirRow, playerBoard))
			return false;
	}
	// king
	else
	{
		int eatOpponent = 0;
		// Look at all the positions of the trajectory
		for (int i = 1; i < abs(diffC); i++)
		{
			// Eat a piece of his side
			if (getPiece(column, row, playerBoard) && getPiece(column + (i * dirCol), row + (i * dirRow), playerBoard))
				return false;
			if (getPiece(column, row, robotBoard) && getPiece(column + (i * dirCol), row + (i * dirRow), robotBoard))
				return false;

			// Count the number of opponent piece eaten
			if (getPiece(column, row, playerBoard) && getPiece(column + (i * dirCol), row + (i * dirRow), robotBoard))
				eatOpponent ++;
			if (getPiece(column, row, robotBoard) && getPiece(column + (i * dirCol), row + (i * dirRow), playerBoard))
				eatOpponent++;
			// Can't eat more than one opponent piece
			if (eatOpponent > 1)
				return false;
		}
	}
	return true;
}

void Board::printBoard()
{
	for (int column = 0; column < BOARDSIZE; column++)
	{
		for (int row = 0; row < BOARDSIZE; row++)
		{
			if (getPiece(column, row, playerBoard))
			{
				if (getPiece(column, row, playerKingBoard))
					std::cout << "|X|";
				else
					std::cout << " X ";
			}
			else if (getPiece(column, row, robotBoard))
			{
				if (getPiece(column, row, robotKingBoard))
					std::cout << "|O|";
				else
					std::cout << " O ";
			}
			else
			{
				std::cout << " . ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

bool Board::isNewKing(int column, int row)
{
	if (column == 0 && getPiece(column, row, playerBoard))
		return true;
	if (column == BOARDSIZE - 1 && getPiece(column, row, robotBoard))
		return true;
	return false;
}

void Board::upgradePiece(int column, int row)
{
	if (getPiece(column, row, playerBoard))
	{
		setKingPiece(column, row, &playerKingBoard, true);
	}
	else if (getPiece(column, row, robotBoard))
	{
		setKingPiece(column, row, &robotKingBoard, true);
	}
	return;
}

void Board::setPlayerPiece(int column, int row, bool value, bool king)
{
	if (king)
		setKingPiece(column, row, &playerKingBoard, value);
	else if (getPiece(column, row, playerKingBoard) && !value)
		setKingPiece(column, row, &playerKingBoard, value);
	setPiece(column, row, &playerBoard, value);
}

void Board::setRobotPiece(int column, int row, bool value, bool king)
{
	if (king)
		setKingPiece(column, row, &robotKingBoard, value);
	else if (getPiece(column, row, robotKingBoard) && !value)
		setKingPiece(column, row, &robotKingBoard, value);
	setPiece(column, row, &robotBoard, value);
}

bool Board::isInit()
{
	if (playerBoard == 4656793071724282016 && robotBoard == 360856426375152898)
	{
		return true;
	}
	return false;
}

void Board::initBoard()
{
	playerBoard = 4656793071724282016;
	playerKingBoard = 0;
	robotBoard = 360856426375152898;
	robotKingBoard = 0;
}

unsigned __int64 Board::getPlayerBitboard()
{
	return playerBoard;
}

unsigned __int64 Board::getPlayerKingBitboard()
{
	return playerKingBoard;
}

unsigned __int64 Board::getRobotBitboard()
{
	return robotBoard;
}

unsigned __int64 Board::getRobotKingBitboard()
{
	return robotKingBoard;
}

bool Board::isValid()
{
	// #############################################################################
	return true;
}

int Board::getPiece(int column, int row)
{
	if (getPiece(column, row, playerBoard))
	{
		if (getPiece(column, row, playerKingBoard))
			return 3;
		else
			return 1;
	}
	if (getPiece(column, row, robotBoard))
	{
		if (getPiece(column, row, robotKingBoard))
			return 4;
		else
			return 2;
	}
	return 0;
}

bool Board::getPiece(int column, int row, unsigned __int64 board)
{
	unsigned __int64 mask = 1;
	mask = mask << (column + row * BOARDSIZE);
	if (board & mask)
	{
		return true;
	}
	return false;
}

void Board::setPiece(int column, int row, unsigned __int64* board, bool value)
{
	unsigned __int64 mask = 1;
	mask = mask << (column + row * BOARDSIZE);
	if (value)
	{
		*board = *board | mask;
	}
	else
	{
		mask = ~mask;
		*board = *board & mask;
	}
}

void Board::setKingPiece(int column, int row, unsigned __int64* board, bool value)
{
	unsigned __int64 mask = 1;
	mask = mask << (column + row * BOARDSIZE);
	if (value)
	{
		*board = *board | mask;
	}
	else
	{
		mask = ~mask;
		*board = *board & mask;
	}
}

bool Board::checkWin(unsigned __int64 winBboard, unsigned __int64 loseBoard, unsigned __int64 loseKingBoard)
{
	// no more piece in loseBoard
	if (loseBoard == 0)
	{
		return true;
	}

	//can't move any piece
	for (int column = 1; column < BOARDSIZE - 1; column++)
	{
		for (int row = 1; row < BOARDSIZE - 1; row++)
		{
			if (getPiece(column, row, loseBoard))
			{
				// piece/king can move forward (no piece in front of the piece/king)
				if (isValidMove(column, row, column + 1, row) || isValidMove(column, row, column - 1, row))
				{
					return false;
				}
				// piece can eat
				if (isValidMove(column, row, column + 2, row - 2) || isValidMove(column, row, column + 2, row + 2)
					|| isValidMove(column, row, column - 2, row - 2) || isValidMove(column, row, column - 2, row + 2))
					return false;
				// king can move in diagonal
				if (getPiece(column, row, playerKingBoard) || getPiece(column, row, robotKingBoard))
					if (isValidMove(column, row, column + 1, row - 1) || isValidMove(column, row, column + 1, row + 1)
						|| isValidMove(column, row, column - 1, row - 1) || isValidMove(column, row, column - 1, row + 1))
						return false;
			}
		}
	}
	return true;
}


//######################################################################################################################################
/// <summary>
/// This fonction doses not work for all cases, it is a fast check for win
/// </summary>
bool Board::checkWinFast(unsigned __int64 winBoard, unsigned __int64 loseBoard, unsigned __int64 loseKingBoard)
{
	return checkWin(winBoard, loseBoard, loseKingBoard);
	/*
	unsigned __int64 m = board & (board >> BOARDSIZE);
	if (m & (m >> 14))
	{
		return true;
	}

	m = board & (board >> 6);
	if (m & (m >> 12))
	{
		return true;
	}

	m = board & (board >> 8);
	if (m & (m >> 16))
	{
		return true;
	}

	m = board & (board >> 1);
	if (m & (m >> 2))
	{
		return true;
	}

	return false;
	*/
}

bool Board::moveIsWinning(int column, int row, int newColumn, int newRow)
{
	Board boardCopy = copy();
	boardCopy.Play(column, row, newColumn, newRow);
	if (boardCopy.playerWins())
	{
		return true;
	}
	if (boardCopy.robotWins())
	{
		return true;
	}
	return false;
}
