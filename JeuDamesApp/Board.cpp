#include <cstdlib>
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
	Board newBoard;
	newBoard.playerBoard = playerBoard;
	newBoard.playerKingBoard = playerKingBoard;
	newBoard.robotBoard = robotBoard;
	newBoard.robotKingBoard = robotKingBoard;
	newBoard.moveNumber = moveNumber;
	return newBoard;
}

std::vector<int> Board::Play(int initPos, int newPos)
{
	int column = initPos % BOARDSIZE;
	int row = initPos / BOARDSIZE;
	int newColumn = newPos % BOARDSIZE;
	int newRow = newPos / BOARDSIZE;


	if (isValidMove(column, row, newColumn, newRow))
	{
		int moveEat = MoveEatPiece(column, row, newColumn, newRow);
		moveNumber++;
		// move the piece/king
		int getpiece = getPiece(column, row);
		if (getpiece % 2 == 1)
		{
			setPlayerPiece(column, row, false);
			if (getpiece == 3)
				setPlayerPiece(newColumn, newRow, true, true);
			else
				setPlayerPiece(newColumn, newRow, true);
		}
		else if (getpiece % 2 == 0)
		{
			setRobotPiece(column, row, false);
			if (getpiece == 4)
				setRobotPiece(newColumn, newRow, true, true);
			else
				setRobotPiece(newColumn, newRow, true);
		}
		if (moveEat != -1)
		{
			if (getpiece % 2 == 0)
				setPlayerPiece(moveEat % BOARDSIZE, (int)moveEat / BOARDSIZE, false);
			if (getpiece % 2 == 1)
				setRobotPiece(moveEat % BOARDSIZE, (int)moveEat / BOARDSIZE, false);
			std::vector<std::vector<int>> positions = canMoveEat(newColumn, newRow);
			return positions[1];
		}
		std::vector<int> empty;
		return empty;
	}

	throw std::exception("Invalid move");

}

bool Board::isTerminal()
{
	if (playerWins()) std::cout << "Player wins" << std::endl;
	if (robotWins()) std::cout << "Robot wins" << std::endl;
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
	// possibilty to add the precise rules leading to a draw
	return false;
}

std::vector<std::vector<int>> Board::canMoveEat(int column, int row)
{
	std::vector<int> positionsMove;
	std::vector<int> positionsEat;
	unsigned __int64 opponentBoard;
	if (getPiece(column, row, playerBoard))
		opponentBoard = getRobotBitboard();
	else
		opponentBoard = getPlayerBitboard();

	// king
	if (getPiece(column, row, playerKingBoard) || getPiece(column, row, robotKingBoard))
	{
		// Bottom left
		if (row > 1 && column > 1 && !getPiece(column - 2, row - 2) && getPiece(column - 1, row - 1, opponentBoard))
			positionsEat.push_back((column - 2) + (row - 2) * BOARDSIZE);
		if (row > 0 && column > 0 && !getPiece(column - 1, row - 1))
			positionsMove.push_back((column - 1) + (row - 1) * BOARDSIZE);
		// Bottom right
		if (row > 1 && column < 6 && !getPiece(column + 2, row - 2) && getPiece(column + 1, row - 1, opponentBoard))
			positionsEat.push_back((column + 2) + (row - 2) * BOARDSIZE);
		if (row > 0 && column < 7 && !getPiece(column + 1, row - 1))
			positionsMove.push_back((column + 1) + (row - 1) * BOARDSIZE);
		// Top left
		if (row < 6 && column > 1 && !getPiece(column - 2, row + 2) && getPiece(column - 1, row + 1, opponentBoard))
			positionsEat.push_back((column - 2) + (row + 2) * BOARDSIZE);
		if (row < 7 && column < 7 && !getPiece(column + 1, row + 1))
			positionsMove.push_back((column + 1) + (row + 1) * BOARDSIZE);
		// Top right
		if (row < 6 && column < 6 && !getPiece(column + 2, row + 2) && getPiece(column + 1, row + 1, opponentBoard))
			positionsEat.push_back((column + 2) + (row + 2) * BOARDSIZE);
		if (row < 7 && column > 0 && !getPiece(column - 1, row + 1))
			positionsMove.push_back((column - 1) + (row + 1) * BOARDSIZE);
	}
	else
	{
		// piece
		if (getPiece(column, row, playerBoard))
		{
			if (row > 1 && column > 1 && !getPiece(column - 2, row - 2) && getPiece(column - 1, row - 1, robotBoard))
				positionsEat.push_back((column - 2) + (row - 2) * BOARDSIZE);
			if (row > 1 && column < 6 && !getPiece(column + 2, row - 2) && getPiece(column + 1, row - 1, robotBoard))
				positionsEat.push_back((column + 2) + (row - 2) * BOARDSIZE);
			if (row > 0 && column > 0 && !getPiece(column - 1, row - 1))
				positionsMove.push_back((column - 1) + (row - 1) * BOARDSIZE);
			if (row > 0 && column < 7 && !getPiece(column + 1, row - 1))
				positionsMove.push_back((column + 1) + (row - 1) * BOARDSIZE);
		}
		if (getPiece(column, row, robotBoard))
		{
			if (row < 6 && column > 1 && !getPiece(column - 2, row + 2) && getPiece(column - 1, row + 1, playerBoard))
				positionsEat.push_back((column - 2) + (row + 2) * BOARDSIZE);
			if (row < 6 && column < 6 && !getPiece(column + 2, row + 2) && getPiece(column + 1, row + 1, playerBoard))
				positionsEat.push_back((column + 2) + (row + 2) * BOARDSIZE);
			if (row < 7 && column > 0 && !getPiece(column - 1, row + 1))
				positionsMove.push_back((column - 1) + (row + 1) * BOARDSIZE);
			if (row < 7 && column < 7 && !getPiece(column + 1, row + 1))
				positionsMove.push_back((column + 1) + (row + 1) * BOARDSIZE);
		}
	}
	std::vector<std::vector<int>> positions;
	positions.push_back(positionsMove);
	positions.push_back(positionsEat);

	return positions;
}

bool Board::isValidMove(int column, int row, int newColumn, int newRow)
{
	// in the board
	if (column < 0 || column > BOARDSIZE - 1 || row < 0 || row > BOARDSIZE - 1)
	{
		return false;
	}
	if (newColumn < 0 || newColumn > BOARDSIZE - 1 || newRow < 0 || newRow > BOARDSIZE - 1)
	{
		return false;
	}
	// there are no pieces in the initial position
	if (!getPiece(column, row, playerBoard) && !getPiece(column, row, robotBoard))
	{
		return false;
	}
	// there is a pieces in the new position
	if (getPiece(newColumn, newRow, playerBoard) || getPiece(newColumn, newRow, robotBoard))
	{
		return false;
	}

	// movements allowed
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
	
	// piece
	int piece = getPiece(column, row);
	if (piece == 1 || piece == 2)
	{
		// Move 2 cases in diagonal forward
		if (diffR * side == 2)
		{
			// Don't eat an opponent piece
			if (getPiece(column, row, playerBoard) && !getPiece(column + dirCol, row + side, robotBoard))
				return false;
			if (getPiece(column, row, robotBoard) && !getPiece(column + dirCol, row + side, playerBoard))
				return false;
		}
		// Don't move 1 case in diagonal forward
		else if (diffR * side != 1)
			return false;
	}
	// king
	else
	{
		if (diffR == -2 || diffR == 2)
		{
			// Don't eat an opponent piece
			if (getPiece(column, row, playerBoard) && !getPiece(column + dirRow, row + dirRow, robotBoard))
				return false;
			if (getPiece(column, row, robotBoard) && !getPiece(column + dirCol, row + dirRow, playerBoard))
				return false;
		}
	}
	return true;
}

bool Board::isValid()
{
	// There is at least one piece
	if (robotBoard == 0 && playerBoard == 0)
	{
		std::cout << "Plateau non valide : Aucun pion sur le plateau" << std::endl;
		return false;
	}
	// A piece can't be on a light square
	for (int i = 0; i < BOARDSIZE; i++)
	{
		for (int j = 0; j < BOARDSIZE; j++)
		{
			if (i % 2 != j % 2 && getPiece(j, i))
			{
				std::cout << "Plateau non valide : Un pion est sur une case claire" << std::endl;
				return false;
			}
		}
	}
	return true;
}

int Board::MoveEatPiece(int column, int row, int newColumn, int newRow)
{
	int diffC = newColumn - column;
	int dirCol = (diffC >= 0) - (diffC < 0);
	int diffR = newRow - row;
	int dirRow = (diffR >= 0) - (diffR < 0);
	
	if (getPiece(column, row, playerBoard) && getPiece(column + dirCol, row + dirRow, robotBoard))
	{
		return (column + dirCol + (row + dirRow) * BOARDSIZE);
	}
	if (getPiece(column, row, robotBoard) && getPiece(column + dirCol, row + dirRow, playerBoard))
		return (column + dirCol + (row + dirRow) * BOARDSIZE);

	return -1;
}

void Board::printBoard()
{
	for (int row = 0; row < BOARDSIZE; row++)
	{
		for (int column = BOARDSIZE - 1; column >= 0; column--)
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

int Board::getMoveNumber()
{
	return moveNumber;
}

void Board::setMoveNumber(int move)
{
	moveNumber = move;
}

void Board::setPlayerPiece(int column, int row, bool value, bool king)
{
	if (king)
		setKingPiece(column, row, &playerKingBoard, value);
	else if (getPiece(column, row, playerKingBoard))
		setKingPiece(column, row, &playerKingBoard, value);
	setPiece(column, row, &playerBoard, value);
}

void Board::setRobotPiece(int column, int row, bool value, bool king)
{
	if (king)
		setKingPiece(column, row, &robotKingBoard, value);
	else if (getPiece(column, row, robotKingBoard))
		setKingPiece(column, row, &robotKingBoard, value);
	setPiece(column, row, &robotBoard, value);
}

bool Board::newKing()
{
	bool upgraded = false;
	for (int i = 0; i < BOARDSIZE; i++)
	{
		if (getPiece(i, 0) == 1)
		{
			upgradePiece(i, 0);
			upgraded = true;
		}
		if (getPiece(i, BOARDSIZE - 1) == 2)
		{
			upgradePiece(i, BOARDSIZE - 1);
			upgraded = true;
		}
	}

	return upgraded;
}

bool Board::isInit()
{
	if (playerBoard == 12273903276444876800 && robotBoard == 5614165)
	{
		return true;
	}
	return false;
}

void Board::initBoard()
{
	playerBoard = 12273903276444876800;
	playerKingBoard = 0;
	robotBoard = 5614165;
	robotKingBoard = 0;
	moveNumber = 0;
}

// ################## Functions to calculate the board score ######################
int Board::numCaptured(int side)
{
	int count = 0;
	unsigned __int64 sideBoard;
	if (side == 0)
		sideBoard = getPlayerBitboard();
	else
		sideBoard = getRobotBitboard();

	for (int i = 0; i < 64; i++)
	{
		count += sideBoard & 1;
		sideBoard >>= 1;
	}
	return 12 - count;
}

int Board::possibleMoves(int side)
{
	int countMove = 0;
	int countEat = 0;
	for (int i = 0; i < BOARDSIZE; i++)
	{
		for (int j = 0; j < BOARDSIZE; j++)
		{
			if (getPiece(j, i) % 2 == side)
			{
				std::vector<std::vector<int>> moves = canMoveEat(j, i);
				countMove += moves[0].size();
				countEat += moves[1].size();
			}
		}
	}

	if (countEat > 0)
		return countEat;
	return countMove;
}

int Board::numMen(int side)
{
	int count = 0;
	unsigned __int64 sideBoard;
	unsigned __int64 sideKingBoard;
	if (side == 0)
	{
		sideBoard = getRobotBitboard();
		sideKingBoard = getRobotKingBitboard();
	}
	else
	{
		sideBoard = getPlayerBitboard();
		sideKingBoard = getPlayerKingBitboard();
	}

	for (int i = 0; i < 64; i++)
	{
		count += sideBoard & 1 && sideKingBoard & 0;
		sideBoard >>= 1;
		sideKingBoard >>= 1;
	}

	return count;
}

int Board::numKings(int side)
{
	int count = 0;
	unsigned __int64 sideBoard;
	if (side == 0)
		sideBoard = getRobotKingBitboard();
	else
		sideBoard = getPlayerKingBitboard();

	for (int i = 0; i < 64; i++)
	{
		count += sideBoard & 1;
		sideBoard >>= 1;
	}
	return count;
}

int Board::capturables(int side)
{
	int count = 0;
	unsigned __int64 sideBoard;
	if (side == 0)
		sideBoard = getPlayerBitboard();
	else
		sideBoard = getRobotBitboard();

	for (int i = 0; i < BOARDSIZE; i++)
	{
		for (int j = 0; j < BOARDSIZE; j++)
		{
			if (getPiece(i, j, sideBoard))
				// no support from the neighboring squares
				if (!getPiece(i + 1, j + 1, sideBoard) && !getPiece(i + 1, j - 1, sideBoard) && !getPiece(i - 1, j + 1, sideBoard) && !getPiece(i - 1, j - 1, sideBoard))
					count++;
		}
	}

	return count;
}

int Board::uncapturables(int side)
{
	int count = 0;
	unsigned __int64 sideBoard;
	if (side == 0)
		sideBoard = getRobotBitboard();
	else
		sideBoard = getPlayerBitboard();

	for (int i = 0; i < BOARDSIZE; i++)
	{
		for (int j = 0; j < BOARDSIZE; j++)
		{
			if (getPiece(i, j, sideBoard))
			{
				if (i > 0 && i < BOARDSIZE - 1 && j > 0 && j < BOARDSIZE - 1)
				{
					if (getPiece(i + 1, j + 1) && getPiece(i + 1, j - 1))
						count++;
					else if (getPiece(i - 1, j + 1, sideBoard) && getPiece(i - 1, j - 1, sideBoard))
						count++;
					else if (getPiece(i + 1, j + 1, sideBoard) && getPiece(i - 1, j + 1, sideBoard))
						count++;
					else if (getPiece(i + 1, j - 1, sideBoard) && getPiece(i - 1, j - 1, sideBoard))
						count++;
				}
				// pieces in the borders
				else
					count++;
			}
		}
	}



	return count;
}

int Board::atMiddle(int side)
{
	int count = 0;
	unsigned __int64 sideBoard;
	unsigned __int64 sideKingBoard;
	if (side == 0)
	{
		sideBoard = getRobotBitboard();
		sideKingBoard = getRobotKingBitboard();
	}
	else
	{
		sideBoard = getPlayerBitboard();
		sideKingBoard = getPlayerKingBitboard();
	}

	for (int i = 0; i < BOARDSIZE ; i++)
	{
		for (int j = 3; j < BOARDSIZE - 3; j++)
		{
			if (getPiece(i, j, sideBoard) && !getPiece(i, j, sideKingBoard))
				count++;
		}
	}
	return count;
}

int Board::atEnemy(int side)
{
	int count = 0;
	unsigned __int64 sideBoard;
	unsigned __int64 sideKingBoard;
	int begin = 0;
	int end = 0;
	if (side == 0)
	{
		sideBoard = getRobotBitboard();
		sideKingBoard = getRobotKingBitboard();
		begin = 4;
		end = 8;
	}
	else
	{
		sideBoard = getPlayerBitboard();
		sideKingBoard = getPlayerKingBitboard();
		begin = 0;
		end = 3;
	}

	for (int i = 0; i < BOARDSIZE; i++)
	{
		for (int j = begin; j < end; j++)
		{
			if (getPiece(i, j, sideBoard) && !getPiece(i, j, sideKingBoard))
				count++;
		}
	}
	return count;
}
// ####################### End functions board score ###############################

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
		return true;

	//can't move any piece
	for (int column = 0; column < BOARDSIZE; column++)
	{
		for (int row = 0; row < BOARDSIZE; row++)
		{
			if (getPiece(column, row, loseBoard))
			{
				std::vector<std::vector<int>> moveEat = canMoveEat(column, row);
				if (moveEat[0].size() > 0 || moveEat[1].size() > 0)
					return false;
			}
		}
	}
	return true;
}

bool Board::moveIsWinning(int column, int row, int newColumn, int newRow)
{
	Board boardCopy = copy();
	boardCopy.Play(column + BOARDSIZE * row, newColumn + BOARDSIZE * newRow);
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
