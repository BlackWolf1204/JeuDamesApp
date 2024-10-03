#include "Board.h"

Board::Board()
{
	playerBoard = 0;
	playerKingBoard = 0;
	robotBoard = 0;
	robotKingBoard = 0;
	moveNumber = 0;
}

Board Board::copy()
{
	//Not Tested
	Board newBoard;
	newBoard.playerBoard = playerBoard;
	newBoard.playerKingBoard = playerKingBoard;
	newBoard.robotBoard = robotBoard;
	newBoard.robotKingBoard = robotKingBoard;
	newBoard.moveNumber = moveNumber;
	return newBoard;
}

void Board::Play(int column, int row, int newColumn, int newRow)
{
	std::cout << "Board::Play" << std::endl;
	return;

	/*
	for (int row = 0; row < 6; row++)
	{
		if (!getPiece(column, row, playerBoard) && !getPiece(column, row, robotBoard))
		{
			if (getMoveNumber() % 2 == 0)
			{
				setPiece(column, row, &playerBoard, true);
			}
			else
			{
				setPiece(column, row, &robotBoard, true);
			}
			return;
		}
	}
	throw std::exception("Invalid move");
	*/
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
	int way = 0;
	if (getPiece(column, row, playerBoard))
		way = -1;
	else
		way = 1;
	int diffC = (newColumn - column) * way;
	int diffR = (newRow - row) * way;
	if ((newColumn - column) * way == 1)
	{
		// go forward
		if (row - newRow == 0)
		{
			return true;
		}
	}
	else if ((newColumn - column) * way == 2)
	{
		// eat a piece
		if (row - newRow == -2 || row - newRow == 2)
		{
			if ()
		}
	}
	// movements allowed for a piece
	if (!getPiece(column, row, playerKingBoard) || !getPiece(column, row, robotKingBoard))
	{
		// go forward
		if (diffC == 1 && diffR == 0)
		{
			return true;
		}
		// eat a piece
		else if (diffC == 2 && diffR == 2)
		{
			return true;
		}
		
	}
	// movements allowed for a king
	else
	{

	}
	return false;
}

int Board::getMoveNumber()
{
	return moveNumber;
}

void Board::printBoard()
{
	for (int row = BOARDSIZE-1; row >= 0; row--)
	{
		for (int column = 0; column < BOARDSIZE-1; column++)
		{
			if (getPiece(column, row, playerBoard))
			{
				std::cout << "X ";
			}
			else if (getPiece(column, row, robotBoard))
			{
				std::cout << "O ";
			}
			else
			{
				std::cout << ". ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	if (getMoveNumber() % 2 == 0)
		std::cout << "Player's turn (X)" << std::endl;
	else
		std::cout << "Robot's turn (O)" << std::endl;
}

void Board::setPlayerPiece(int column, int row, bool value, bool king=0)
{
	if (king != 0)
		setKingPiece(column, row, &playerKingBoard, value);
	setPiece(column, row, &playerBoard, value);
}

void Board::setRobotPiece(int column, int row, bool value, bool king=0)
{
	if (king != 0)
		setKingPiece(column, row, &robotKingBoard, value);
	setPiece(column, row, &robotBoard, value);
}

bool Board::isInit()
{
	if (playerBoard == 9313586142364319904 && robotBoard == 360856426375152898)
	{
		return true;
	}
	return false;
}

unsigned __int64 Board::getPlayerBitboard()
{
	return playerBoard;
}

unsigned __int64 Board::getRobotBitboard()
{
	return robotBoard;
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
	if (value)
	{
		moveNumber++;
	}
	/* ##########################################################################################
	else
	{
		moveNumber--;
	}
	########################################################################################## */

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
	if (value)
	{
		moveNumber++;
	}
	/* ##############################################################################################
	else
	{
		moveNumber--;
	}
	############################################################################################## */

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

// ########################################################################################################
bool Board::checkWin(unsigned __int64 board, unsigned __int64 winBoard, unsigned __int64 winKingBoard)
{
	// can't move
	// no pore piece
	
	//Check for 4 in a row
	for (int column = 0; column < BOARDSIZE; column++)
	{
		for (int row = 0; row < 3; row++)
		{
			if (getPiece(column, row, board) && getPiece(column, row + 1, board) && getPiece(column, row + 2, board) && getPiece(column, row + 3, board))
			{
				return true;
			}
		}
	}

	//Check for 4 in a column
	for (int column = 0; column < 4; column++)
	{
		for (int row = 0; row < 6; row++)
		{
			if (getPiece(column, row, board) && getPiece(column + 1, row, board) && getPiece(column + 2, row, board) && getPiece(column + 3, row, board))
			{
				return true;
			}
		}
	}

	//Check for 4 in a diagonal from bottom left to top right
	for (int column = 0; column < 4; column++)
	{
		for (int row = 0; row < 3; row++)
		{
			if (getPiece(column, row, board) && getPiece(column + 1, row + 1, board) && getPiece(column + 2, row + 2, board) && getPiece(column + 3, row + 3, board))
			{
				return true;
			}
		}
	}

	//Check for 4 in a diagonal from top left to bottom right
	for (int column = 0; column < 4; column++)
	{
		for (int row = 3; row < 6; row++)
		{
			if (getPiece(column, row, board) && getPiece(column + 1, row - 1, board) && getPiece(column + 2, row - 2, board) && getPiece(column + 3, row - 3, board))
			{
				return true;
			}
		}
	}
	return false;
}


//#########################################################################################################
/// <summary>
/// This fonction doses not work for all cases, it is a fast check for win
/// </summary>
bool Board::checkWinFast(unsigned __int64 board, unsigned __int64 winBoard, unsigned __int64 winKingBoard)
{
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
