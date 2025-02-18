#pragma once

#include <vector>
#include <exception>
#include <iostream>

#define BOARDSIZE 8

class Board
{
public:
	/// <summary>
	/// Default constructor
	/// </summary>
	Board();

	/// <summary>
	/// Copy a board to a new board object
	/// </summary>
	/// <returns>The new board object</returns>
	Board copy();

	/// <summary>
	/// Play a move corresponding to the given positions
	/// </summary>
	/// <param name="initPos">Initial position</param>
	/// <param name="newPos">New position</param>
	/// <return>Vector of positions where moved piece can move to eat (sweep), empty if the move played din't eat a piece or no more piece to eat</return>
	std::vector<int> Play(int initPos, int newPos);

	/// <summary>
	/// Check if the game is over (Win or Draw)
	/// </summary>
	/// <returns>True if the game is over, false otherwise</returns>
	bool isTerminal();

	/// <summary>
	/// Check if the player wins
	/// </summary>
	/// <returns>True if the player wins, false otherwise</returns>
	bool playerWins();

	/// <summary>
	/// Check if the robot wins
	/// </summary>
	/// <returns>True if the robot wins, false otherwise</returns>
	bool robotWins();

	/// <summary>
	/// Check if the game is a draw
	/// </summary>
	/// <returns>True if the game is a draw, false otherwise</returns>
	bool draw();

	/// <summary>
	/// Return the positions where the piece can move or eat
	/// </summary>
	/// <param name="column">Column of the initial position</param>
	/// <param name="row">Row of the initial position</param>
	/// <returns>Vector of list of position where the pieces can move, empty if can't move and list of position where the piece can eat, empty if can't eat</returns>
	std::vector<std::vector<int>> canMoveEat(int column, int row);

	/// <summary>
	/// Return the piece eaten by the move, -1 if no piece is eaten
	/// </summary>
	/// <param name="column">Column of the initial position</param>
	/// <param name="row">Row of the initial position</param>
	/// <param name="newColumn">Column of the new position</param>
	/// <param name="newRow">Row of the new position</param>
	/// <returns>Position of the eaten piece, -1 if no piece eaten</returns>
	int MoveEatPiece(int column, int row, int newColumn, int newRow);

	/// <summary>
	/// Check if a move is valid
	/// </summary>
	/// <param name="column">Column of the initial position</param>
	/// <param name="row">Row of the initial position</param>
	/// <param name="newColumn">Column of the new position</param>
	/// <param name="newRow">Row of the new position</param>
	/// <returns>True if the move is valid, false otherwise</returns>
	bool isValidMove(int column, int row, int newColumn, int newRow);

	/// <summary>
	/// Check if the board is valid
	/// </summary>
	bool isValid();

	/// <summary>
	/// Print the board in the console (X for player pieces and O for robot pieces)
	/// </summary>
	void printBoard();

	/// <summary>
	/// Upgrade a piece (given by its position) into a king
	/// </summary>
	/// <param name="column">Column of the position</param>
	/// <param name="row">Row of the position</param>
	void upgradePiece(int column, int row);

	/// <summary>
	/// Get the piece at the given position
	/// </summary>
	/// <returns>1 if the player has a piece, 3 if the player has a king, 2 if the robot has a piece, 4 if the robot has a king, 0 otherwise</returns>
	int getPiece(int column, int row);

	/// <summary>
	/// Get the player bitboard as an unsigned __int64
	/// </summary>
	/// <returns>The player king bitboard</returns>
	unsigned __int64 getPlayerBitboard();

	/// <summary>
	/// Get the player king bitboard as an unsigned __int64
	/// </summary>
	/// <returns>The player bitboard</returns>
	unsigned __int64 getPlayerKingBitboard();

	/// <summary>
	/// Get the robot bitboard as an unsigned __int64
	/// </summary>
	/// <returns>The robot bitboard</returns>
	unsigned __int64 getRobotBitboard();

	/// <summary>
	/// Get the robot king bitboard as an unsigned __int64
	/// </summary>
	/// <returns>The robot king bitboard</returns>
	unsigned __int64 getRobotKingBitboard();

	/// <summary>
	/// Get the number of move done by the robot
	/// </summary>
	/// <returns>Number of move done</returns>
	int getMoveNumber();
	
	/// <summary>
	/// Set the number of move done by the robot
	/// </summary>
	/// <param name="number">Number of move done</param>
	void setMoveNumber(int number);

	/// <summary>
	/// Move the player piece at the given position (empty the position if value is false)
	/// </summary>
	/// <param name="column">Column of the initial position</param>
	/// <param name="row">Row of the initial position</param>
	/// <param name="value">If add or empty the position
	/// <param name="king">If the piece is a king or not (false for piece and true for king)</param>
	void setPlayerPiece(int column, int row, bool value, bool king=false);

	/// <summary>
	/// Move the robot piece at the given position (empty the position if value is false)
	/// </summary>
	/// <param name="column">Column of the position</param>
	/// <param name="row">Row of the position</param>
	/// <param name="value">If add or empty the position
	/// <param name="king">If the piece is a king or not (false for piece and true for king)</param>
	void setRobotPiece(int column, int row, bool value, bool king=false);

	/// <summary>
	/// Upgrade a piece into a king if is at the end of the board
	/// </summary>
	/// <returns>True if there was an upgrade, false otherwise</returns>
	bool newKing();

	/// <summary>
	/// Check if the board is at the initial position :
	/// 
	/// . X . X . X . X
	/// X . X . X . X .
	/// . X . X . X . X
	/// . . . . . . . .
	/// . . . . . . . .
	/// O . O . O . O .
	/// . O . O . O . O
	/// O . O . O . O .
	/// 
	/// </summary>
	/// <returns>True if the board is initialised, false otherwise</returns>
	bool isInit();

	/// <summary>
	/// Initialize the board in the initial position
	/// </summary>
	void initBoard();

	// ##################### Functions to calculate the score of the board #######################################

	/// <summary>
	/// Get the number of opponent piece eaten
	/// </summary>
	/// <param name ="side">0 for the robot point of view and 1 for the player</param>
	/// <returns>Number of opponent piece eaten</returns>
	int numCaptured(int side);

	/// <summary>
	/// Get the number of possible moves of the pieces (don't count simple moves if a piece can eat)
	/// </summary>
	/// <param name ="side">0 for the robot point of view and 1 for the player</param>
	/// <returns>Number of possible moves</returns>
	int possibleMoves(int side);

	/// <summary>
	/// Get the number of ally piece (man)
	/// </summary>
	/// <param name ="side">0 for the robot point of view and 1 for the player</param>
	/// <returns>Number of ally piece (man)</returns>
	int numMen(int side);

	/// <summary>
	/// Get the number of ally king
	/// </summary>
	/// <param name ="side">0 for the robot point of view and 1 for the player</param>
	/// <returns>Number of ally king</returns>
	int numKings(int side);

	/// <summary>
	/// Get the number of opponent piece that can be captured (the capturable piece don't have any support in the neighboring squares)
	/// Don't look if an ally piece block a move that could eat an opponent piece
	/// </summary>
	/// <param name ="side">0 for the robot point of view and 1 for the player</param>
	/// <returns>Number of opponent piece that can be captured</returns>
	int capturables(int side);

	/// <summary>
	/// Get the number of ally piece that can't be captured (the ally piece is supported by two ally pieces that block the eating movements on the two sides)
	/// </summary>
	/// <param name ="side">0 for the robot point of view and 1 for the player</param>
	/// <returns>Number of ally piece that can't be captured</returns>
	int uncapturables(int side);

	/// <summary>
	/// Get the number of ally piece in the middle of the board (doesn't count the kings)
	/// </summary>
	/// <param name ="side">0 for the robot point of view and 1 for the player</param>
	/// <returns>Number of ally piece in the middle of the board</returns>
	int atMiddle(int side);

	/// <summary>
	/// Get the number of ally piece in the opponent part of the board (doesn't count the kings)
	/// </summary>
	/// <param name ="side">0 for the robot point of view and 1 for the player</param>
	/// <returns>Number of ally piece in the opponent part of the board</returns>
	int atEnemy(int side);

	// ######################################################################################################

private:
	unsigned __int64 playerBoard;
	unsigned __int64 playerKingBoard;
	unsigned __int64 robotBoard;
	unsigned __int64 robotKingBoard;
	int moveNumber;

	/// <summary>
	/// Check if a piece is present at the given position
	/// </summary>
	/// <param name="column">Index of the column</param>
	/// <param name="row">Index of the row</param>
	/// <param name="board">Bitboard to check</param>
	/// <returns>True if a piece is present, false otherwise</returns>
	bool getPiece(int column, int row, unsigned __int64 board);

	/// <summary>
	/// Set a piece at the given position in the simple board
	/// </summary>
	/// <param name="column">Index of the column</param>
	/// <param name="row">Index of the row</param>
	/// <param name="board">Bitboard to modify</param>
	/// <param name="value">True to set a piece, false to empty the position</param>
	void setPiece(int column, int row, unsigned __int64* board, bool value);

	/// <summary>
	/// Set a piece at the given position in the king board
	/// </summary>
	/// <param name="column">Index of the column</param>
	/// <param name="row">Index of the row</param>
	/// <param name="board">Bitboard to modify</param>
	/// <param name="value">True to set a piece, false to empty the position</param>
	void setKingPiece(int column, int row, unsigned __int64* board, bool value);

	/// <summary>
	/// Check if the opponent has no more pieces or can't move anymore
	/// </summary>
	/// <param name="winBoard">Bitboard to check if is winning</param>
	/// <param name="loseBoard">Opponent bitboard</param>
	/// <param name="loseKingBoard">Opponent king bitboard to check</param>
	/// <returns>True if the opponent has no more piece or can't move, false otherwise</returns>
	bool checkWin(unsigned __int64 winBoard, unsigned __int64 loseBoard, unsigned __int64 loseKingBoard);

public:

	bool moveIsWinning(int column, int row, int newColumn, int newRow);
};

