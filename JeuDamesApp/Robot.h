#pragma once

#include "DobotDll.h"
#include "DobotType.h"
#include <iostream>

class Robot
{
public:
	/// <summary>
	/// Initializes the coordinates of the columns and pieces (hardcoded)
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
	/// Ask the Dobot to grab a piece, move it to the column and drop it
	/// </summary>
	/// <param name="column">Column number (0-6)</param>
	void Play(int column);

	void Refill();

	int getRemainingPieces();

private:

	int dobotId = -1;
	int remainingPieces = 8;
	Pose columnCoordinates[7];
	Pose pieceCoordinates[8];

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
	/// Open the gripper of the Dobot
	/// </summary>
	void openGripper();

	/// <summary>
	/// Close the gripper of the Dobot
	/// </summary>
	void closeGripper();
	
	/// <summary>
	/// Open the gripper of the Dobot, go to the last remaining piece, grab it and move up
	/// </summary>
	void grabPiece();

	/// <summary>
	/// Set the gripper to a specific state, Open or Close, and turn the gripper pump on or off
	/// </summary>
	/// <param name="open">True if the gripper should be open, false otherwise</param>
	/// <param name="on">True if the gripper pump should be on, false otherwise</param>
	void gripper(bool open, bool on);

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

