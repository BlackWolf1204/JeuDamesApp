#pragma once

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

	/// <summary> ###########################################################################
	/// Play a move in the corresponding to the given positions
	/// </summary>
	/// <param name="column">Column of the initial position</param>
	/// <param name="row">Row of the initial position</param>
	/// <param name="newColumn">Column of the new position</param>
	/// <param name="newRow">Row of the new position</param>
	void Play(int column, int row, int newColumn, int newRow);

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

	// ###########################################################################
	void mustEat();

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
	/// Get the number of moves played on the board
	/// </summary>
	/// <returns>The number of moves played</returns>
	int getMoveNumber();

	/// <summary>
	/// Print the board in the console
	/// </summary>
	void printBoard();

	/// <summary>
	/// Move the player piece at the givenposition (empty the position if value is false)
	/// </summary>
	/// <param name="column">Column of the initial position</param>
	/// <param name="row">Row of the initial position</param>
	/// <param name="newColumn">Column of the new position</param>
	/// <param name="newRow">Row of the new position</param>
	/// <param name="king">If the piece is a king or not (0 for piece and 1 for king)</param>
	void setPlayerPiece(int column, int row, bool value, bool king=0);

	/// <summary>
	/// Move the robot piece at the given position (empty the position if value is false)
	/// </summary>
	/// <param name="column">Column of the initial position</param>
	/// <param name="row">Row of the initial position</param>
	/// <param name="king">If the piece is a king or not (0 for piece and 1 for king)</param>
	void setRobotPiece(int column, int row, bool value, bool king=0);

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
	/// Get the player bitboard as an unsigned __int64
	/// </summary>
	/// <returns>The player bitboard</returns>
	unsigned __int64 getPlayerBitboard();

	/// <summary>
	/// Get the robot bitboard as an unsigned __int64
	/// </summary>
	/// <returns>The robot bitboard</returns>
	unsigned __int64 getRobotBitboard();

	/// <summary> ############################################################################################
	/// Check if the board is valid
	/// </summary>
	/// <returns>True if every piece has another piece below, false otherwise</returns>
	bool isValid();

	/// <summary>
	/// Get the piece at the given position
	/// </summary>
	/// <returns>1 if the player has a piece, 3 if the player has a king, 2 if the robot has a piece, 4 if the robot has a king 0 otherwise</returns>
	int getPiece(int column, int row);

private:
	unsigned __int64 playerBoard;
	unsigned __int64 playerKingBoard;
	unsigned __int64 robotBoard;
	unsigned __int64 robotKingBoard;
	unsigned int moveNumber;

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

	/// <summary> #############################################################################################
	/// Check if the opponent has no more pieces or can't move anymore
	/// </summary>
	/// <param name="winBoard">Bitboard to check if is winning</param>
	/// <param name="board">Opponent bitboard</param>
	/// <param name="kingBoard">Opponent king bitboard to check</param>
	/// <returns>True if 4 pieces are aligned, false otherwise</returns>
	bool checkWin(unsigned __int64 winBoard, unsigned __int64 board, unsigned __int64 kingBoard);

public:

	/// <summary> ##############################################################################################
	/// A faster way to check if the opponent has no more pieces or can't move anymore
	/// Keep it to improve the speed of the game in the future
	/// </summary>
	/// <param name="winBoard">Bitboard to check if is winning</param>
	/// <param name="board">Opponent bitboard</param>
	/// <param name="kingBoard">Opponent king bitboard to check</param>
	/// <returns>True if 4 pieces are aligned, false otherwise</returns>
	bool checkWinFast(unsigned __int64 winBoard, unsigned __int64 board, unsigned __int64 kingBoard);
	
	bool moveIsWinning(int column, int row, int newColumn, int newRow);
};

