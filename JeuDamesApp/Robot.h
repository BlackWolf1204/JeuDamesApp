#pragma once

#include "DobotDll.h"
#include "DobotType.h"
#include <iostream>

class Robot
{
public:
	/// <summary>
	/// Initializes the coordinates of the squares and pieces (hardcoded)
	/// </summary>
	Robot();

	~Robot();

	/// <summary>
	/// Connect to the Dobot and check if it is connected
	/// </summary>
	/// <returns>True if the Dobot is connected, false otherwise</returns>
	bool connect();

	/// <summary>
	/// Reset the Dobot to its initial position
	/// </summary>
	void Home();

	/// <summary>
	/// Ask the Dobot to grab a piece at an initial position and move it to the position
	/// If the initial position is -1, add a king at the given position
	/// If the new position is -1, remove the piece at the initial position of the board
	/// </summary>
	/// <param name="initPos">Initial position</param>
	/// <param name="newPos">New position</param>
	void Play(int initPos, int newPos);

	void Refill();
	void Empty();

	int getRemainingKing();
	int getRemovedPieces();

private:

	int dobotId = -1;
	int remainingKing = 8;
	int removedPieces = 0;
	Pose squareCoordinates[64];
	Pose kingCoordinates[8];
	Pose removedPieceCoordinates[8];

	/// <summary>
	/// Move the Dobot to a specific position
	/// </summary>
	/// <param name="position">Position Vector from the dobot library</param>
	void goTo(Pose position);

	/// <summary>
	/// Move the Dobot to a specific position, with a specific z value (corresponding to the height)
	/// </summary>
	/// <param name="position">Position vector from the dobot library</param>
	/// <param name="z">Z value</param>
	void goTo(Pose position, float z);

	/// <summary>
	/// Move the Dobot to a specific position to read the state of the board
	/// </summary>
	void goReadBoard();

	/// <summary>
	/// Go to the last remaining king, grab it with the suctionCup, move up and put it at the given position in the board
	/// </summary>
	/// <param name="position">Position in the board</param>
	void addKing(int position);

	/// <summary>
	/// Grab the piece at the given position with the suctionCup, move up and put it at the last empty position for removed pieces
	/// </summary>
	/// <param name="position">Position of the piece in the board</param>
	void removePiece(int position);

	/// <summary>
	/// Activate the suctionCup of the Dobot
	/// </summary>
	void activSuctionCup();

	/// <summary>
	/// Desactivate the suctionCup of the Dobot
	/// </summary>
	void desactivSuctionCup();
	
	/// <summary>
	/// Go to the last remaining king, grab it with the suctionCup and move up
	/// </summary>
	void grabKing();

	/// <summary>
	/// Set the suctionCup to a specific state, Open or Close, and turn the suctionCup pump on or off
	/// </summary>
	/// <param name="open">True if the gripper should be open, false otherwise</param>
	/// <param name="on">True if the gripper pump should be on, false otherwise</param>
	void suctionCup(bool open, bool on);

	/// <summary>
	/// Close the gripper of the Dobot, and turn the pump off
	/// </summary>
	void turnOffGripper();

	/// <summary>
	/// Sleep the program for a specific amount of time to let the Dobot move before sending another command
	/// </summary>
	/// <param name="seconds">Seconds to wait</param>
	void wait(float seconds);
};

