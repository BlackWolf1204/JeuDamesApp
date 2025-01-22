#include "Robot.h"

Robot::Robot()
{// ######################################################################################################
	squareCoordinates[0] = { 170, 75, -7, 0 };
	squareCoordinates[1] = { 170, 33, -7, 0 };
	squareCoordinates[2] = { 168, -8, -7, 0 };
	squareCoordinates[3] = { 165, -50, -7, 0 };
	squareCoordinates[4] = { 189, 52, -7, 0 };
	squareCoordinates[5] = { 188, 11, -7, 0 };
	squareCoordinates[6] = { 186, -30, -7, 0 };
	squareCoordinates[7] = { 184, -71, -7, 0 };
	squareCoordinates[8] = { 210, 72, -7, 0 };
	squareCoordinates[9] = { 208, 31, -7, 0 };
	squareCoordinates[10] = { 208, -11, -7, 0 };
	squareCoordinates[11] = { 205, -51, -7, 0 };
	squareCoordinates[12] = { 228, 50, -7, 0 };
	squareCoordinates[13] = { 227, 9, -7, 0 };
	squareCoordinates[14] = { 225, -32, -7, 0 };
	squareCoordinates[15] = { 223, -73, -7, 0 };
	squareCoordinates[16] = { 249, 69, -7, 0 };
	squareCoordinates[17] = { 247, 28, -7, 0 };
	squareCoordinates[18] = { 245, -13, -7, 0 };
	squareCoordinates[19] = { 244, -54, -7, 0 };
	squareCoordinates[20] = { 268, 48, -7, 0 };
	squareCoordinates[21] = { 266, 7, -7, 0 };
	squareCoordinates[22] = { 264, -34, -7, 0 };
	squareCoordinates[23] = { 262, -75, -7, 0 };
	squareCoordinates[24] = { 288, 67, -7, 0 };
	squareCoordinates[25] = { 286, 26, -7, 0 };
	squareCoordinates[26] = { 285, -15, -7, 0 };
	squareCoordinates[27] = { 283, -54, -7, 0 };
	squareCoordinates[28] = { 306, 45, -7, 0 };
	squareCoordinates[29] = { 306, 4, -7, 0 };
	squareCoordinates[30] = { 303, -36, -7, 0 };
	squareCoordinates[31] = { 302, -76, -7, 0 };

	kingCoordinates[0] = { 35, -200, 5, 0 };
	kingCoordinates[1] = { 10, -199, 5, 0 };
	kingCoordinates[2] = { -16, -197, 5, 0 };
	kingCoordinates[3] = { -42, -197, 5, 0 };
	kingCoordinates[4] = { 36, -175, 5, 0 };
	kingCoordinates[5] = { 10, -174, 5, 0 };
	kingCoordinates[6] = { -16, -173, 5, 0 };
	kingCoordinates[7] = { -41, -171, 5, 0 };

	removedPieceCoordinates = { -58, -220, -126, 90 };

	calibrationCoordinates[0] = { 170, 75, -7, 0 };		// Left bottom square
	calibrationCoordinates[1] = { 302, -76, -7, 0 };	// Right top square
	calibrationCoordinates[2] = { 0, 200, 5, 90 };		// Removed pieces
	calibrationCoordinates[3] = { -41, -171, 5, 0 };	// Right bottom king
	calibrationCoordinates[5] = { 35, -200, 5, 0 };		// Left top king
	// ###################################################################
}

Robot::~Robot()
{
}

bool Robot::connect(std::string portName)
{
	/*
	char dobotPortName[64];
	int dobotSearchCount = SearchDobot(dobotPortName, 64);
	
	if (dobotSearchCount == 0) {
		std::cerr << "No dobot found" << std::endl;
		return false;
	}
	else if (dobotSearchCount > 1) {
		std::cerr << "Multiple dobot found. Please connect only one dobot" << std::endl;
		return false;
	}*/

	const char* dobotPortName = portName.c_str();

	int connectDobotResult = ConnectDobot(dobotPortName, 115200, nullptr, nullptr, &dobotId);
	if (connectDobotResult != DobotConnect_NoError) {
		std::cerr << "Failed to connect to dobot. Error : ";
		switch (connectDobotResult) {
		case DobotConnect_NotFound:
			std::cerr << "Dobot not found";
			return false;
		case DobotConnect_Occupied:
			std::cerr << "Dobot port occupied";
			return false;
		}
	}

	std::cout << "Connected to dobot" << std::endl;

	int resultClearAllAlarms = ClearAllAlarmsState(dobotId);
	if (resultClearAllAlarms != DobotCommunicate_NoError) {
		std::cerr << "Failed to clear all alarms" << std::endl;
		return false;
	}
	
	JOGCoordinateParams* jogCoordinateParams = new JOGCoordinateParams;
	int result = GetJOGCoordinateParams(dobotId, jogCoordinateParams);
	if (result != DobotCommunicate_NoError) {
		std::cerr << "Failed to get jog coordinate params" << std::endl;
		return false;
	}
	std::cout << "JOGCoordinateParams: velocityX = " << jogCoordinateParams->velocity[0] << ", velocityY = " << jogCoordinateParams->velocity[1] << ", velocityZ = " << jogCoordinateParams->velocity[2] << ", velocityR = " << jogCoordinateParams->velocity[3] << std::endl;
	return true;
}

void Robot::Home()
{
	std::cout << "Resetting dobot position" << std::endl;
	HOMECmd homeCmd;
	uint64_t queuedCmdIndex;
	int resultDobotHome = SetHOMECmd(dobotId, &homeCmd, true, &queuedCmdIndex);
	lastCommandIndex = queuedCmdIndex;
	if (resultDobotHome != DobotCommunicate_NoError) {
		std::cerr << "Failed to reset dobot position" << std::endl;
		return;
	}
	std::cout << "Dobot position successfully reset" << std::endl;

	//goReadBoard();
	
}

void Robot::Play(int initPos, int newPos)
{
	if (dobotId != -1)
	{
		goTo(INITPOS);		// Transition between reading position and playing positions (else path between those two positions impossible)
		if (initPos < 0 && newPos < 0) {
			std::cerr << "Invalid position" << std::endl;
			return;
		}
		if (initPos == -1) {
			addKing(newPos);
			return;
		}
		else if (newPos == -1) {
			removePiece(initPos);
			return;
		}
		if ((int)initPos / BOARDSIZE > 7 || (int)newPos / BOARDSIZE > 7) {
			std::cerr << "Invalid position" << std::endl;
			return;
		}
		if (initPos > -1 && newPos > -1) {

			std::cout << "Move from position " << initPos << " to position " << newPos << std::endl;
			goTo(squareCoordinates[initPos], HIGHT);
			goTo(squareCoordinates[initPos]);
			activeSuctionCup();
			wait(0.5);
			goTo(squareCoordinates[newPos], HIGHT);
			goTo(squareCoordinates[newPos]);
			desactiveSuctionCup();
			wait(0.5);
			turnOffSuctionCup();
		}
		goReadBoard();
	}
}

void Robot::Refill()
{
	std::cout << "Refilling pieces" << std::endl;
	remainingKing = 8;
}

void Robot::Empty()
{
	std::cout << "Empty removed piece locations" << std::endl;
	removedPieces = 0;
}

void Robot::Calibrate()
{
	if (dobotId != -1 && allCmdExecuted() && playing == PlayingState::WAIT)
	{
		setPlaying(PlayingState::DOING);
		std::cout << "Calibrate to postion " << calibrationPosition << std::endl;
		if (calibrationPosition == 0)		// Transition between reading position and calibration position (else path between those two positions impossible)
			goTo(INITPOS);
		if (calibrationPosition < 6)
		{
			goTo(calibrationCoordinates[calibrationPosition]);
			calibrationPosition++;
		}
		else
		{
			calibrationPosition = 0;
			goReadBoard();
		}
	}
}

Robot::PlayingState Robot::getPlaying()
{
	return playing;
}

void Robot::setPlaying(PlayingState state)
{
	playing = state;
}

bool Robot::allCmdExecuted()
{
	uint64_t queuedCmdCurrentIndex;
	int result = GetQueuedCmdCurrentIndex(dobotId, &queuedCmdCurrentIndex);
	if (result != 0)
	{
		std::cout << "Failed to verify queue command current index" << std::endl;
		return false;
	}
	return (queuedCmdCurrentIndex == lastCommandIndex);
}

int Robot::getRemainingKing()
{
	return remainingKing;
}

int Robot::getRemovedPieces()
{
	return removedPieces;
}

int Robot::getCalibrationPosition()
{
	return calibrationPosition;
}

void Robot::goTo(Pose position)
{
	PTPCmd ptpCmd = { 0 };
	ptpCmd.ptpMode = PTPJUMPXYZMode;
	ptpCmd.x = position.x;
	ptpCmd.y = position.y;
	ptpCmd.z = position.z;
	ptpCmd.r = position.r;

	uint64_t queuedCmdIndex;
	int resultDobotPTP = SetPTPCmd(dobotId, &ptpCmd, true, &queuedCmdIndex);
	lastCommandIndex = queuedCmdIndex;
	if (resultDobotPTP != DobotCommunicate_NoError) {
		std::cerr << "Failed to move dobot to position" << std::endl;
	}
}

void Robot::goTo(Pose position, float z)
{
	Pose newPose = {position.x, position.y, position.z + z, position.r};
	goTo(newPose);
}

void Robot::goReadBoard()
{
	goTo(INITPOS);
	goTo({ 217, 62, 160});
}

void Robot::addKing(int position)
{

	if (remainingKing== 0) {
		std::cerr << "No more king" << std::endl;
		return;
	}
	std::cout << "Adding a king in position " << position << std::endl;
	goTo(kingCoordinates[8 - remainingKing]);
	activeSuctionCup();
	goTo(kingCoordinates[8 - remainingKing], HIGHT);
	wait(0.5);
	remainingKing--;
	goTo(squareCoordinates[position], HIGHT);
	goTo(squareCoordinates[position]);
	desactiveSuctionCup();
	wait(0.5);
	turnOffSuctionCup();
}

void Robot::removePiece(int position)
{

	if (removedPieces == 8) {
		std::cerr << "No more empty position" << std::endl;
		return;
	}
	std::cout << "Removing piece in position " << position << std::endl;
	goTo(squareCoordinates[position], HIGHT);
	goTo(squareCoordinates[position]);
	activeSuctionCup();
	wait(0.5);
	goTo(removedPieceCoordinates, HIGHT);
	goTo(removedPieceCoordinates);
	desactiveSuctionCup();
	wait(0.5);
	turnOffSuctionCup();
	removedPieces++;
}

void Robot::activeSuctionCup()
{
	suctionCup(false, true);
}

void Robot::desactiveSuctionCup()
{
	suctionCup(true, true);
}

void Robot::suctionCup(bool close, bool on)
{
	uint64_t queuedCmdIndex;
	int resultDobotGripper = SetEndEffectorSuctionCup(dobotId, on, close, true, &queuedCmdIndex);
	lastCommandIndex = queuedCmdIndex;
	if (resultDobotGripper != DobotCommunicate_NoError) {
		std::cerr << "Failed to suck" << std::endl;
	}
}

void Robot::turnOffSuctionCup()
{
	suctionCup(false, false);
}

void Robot::wait(float seconds)
{ 
	WAITCmd waitCmd = { 0 };
	waitCmd.timeout = (uint32_t)seconds * 1000;

	uint64_t queuedCmdIndex;
	int resultDobotWait = SetWAITCmd(dobotId, &waitCmd, true, &queuedCmdIndex);
	lastCommandIndex = queuedCmdIndex;
	if (resultDobotWait != DobotCommunicate_NoError) {
		std::cerr << "Failed to wait" << std::endl;
	}
}
