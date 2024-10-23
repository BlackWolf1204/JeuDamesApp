#include "Robot.h"

Robot::Robot()
{// ######################################################################################################
	squareCoordinates[0] = { 254, -111, 88, 0 };
	squareCoordinates[1] = { 255, -77, 88, 0 };
	squareCoordinates[2] = { 256, -38, 88, 0 };
	squareCoordinates[3] = { 256, -6, 88, 0 };
	squareCoordinates[4] = { 256, 32, 88, 0 };
	squareCoordinates[5] = { 257, 66, 88, 0 };
	squareCoordinates[6] = { 257, 107, 88, 0 };
	squareCoordinates[7] = { 254, -111, 88, 0 };
	squareCoordinates[8] = { 255, -77, 88, 0 };
	squareCoordinates[9] = { 256, -38, 88, 0 };
	squareCoordinates[10] = { 256, -6, 88, 0 };
	squareCoordinates[11] = { 256, 32, 88, 0 };
	squareCoordinates[12] = { 257, 66, 88, 0 };
	squareCoordinates[13] = { 257, 107, 88, 0 };
	squareCoordinates[14] = { 254, -111, 88, 0 };
	squareCoordinates[15] = { 255, -77, 88, 0 };
	squareCoordinates[16] = { 256, -38, 88, 0 };
	squareCoordinates[17] = { 256, -6, 88, 0 };
	squareCoordinates[18] = { 256, 32, 88, 0 };
	squareCoordinates[19] = { 257, 66, 88, 0 };
	squareCoordinates[20] = { 257, 107, 88, 0 };
	squareCoordinates[21] = { 254, -111, 88, 0 };
	squareCoordinates[22] = { 255, -77, 88, 0 };
	squareCoordinates[23] = { 256, -38, 88, 0 };
	squareCoordinates[24] = { 256, -6, 88, 0 };
	squareCoordinates[25] = { 256, 32, 88, 0 };
	squareCoordinates[26] = { 257, 66, 88, 0 };
	squareCoordinates[27] = { 257, 107, 88, 0 };
	squareCoordinates[28] = { 256, -6, 88, 0 };
	squareCoordinates[29] = { 256, 32, 88, 0 };
	squareCoordinates[30] = { 257, 66, 88, 0 };
	squareCoordinates[31] = { 257, 107, 88, 0 };
	squareCoordinates[32] = { 254, -111, 88, 0 };
	squareCoordinates[33] = { 255, -77, 88, 0 };
	squareCoordinates[34] = { 256, -38, 88, 0 };
	squareCoordinates[35] = { 256, -6, 88, 0 };
	squareCoordinates[36] = { 256, 32, 88, 0 };
	squareCoordinates[37] = { 257, 66, 88, 0 };
	squareCoordinates[38] = { 257, 107, 88, 0 };
	squareCoordinates[39] = { 254, -111, 88, 0 };
	squareCoordinates[40] = { 255, -77, 88, 0 };
	squareCoordinates[41] = { 256, -38, 88, 0 };
	squareCoordinates[42] = { 256, -6, 88, 0 };
	squareCoordinates[43] = { 256, 32, 88, 0 };
	squareCoordinates[44] = { 257, 66, 88, 0 };
	squareCoordinates[45] = { 257, 107, 88, 0 };
	squareCoordinates[46] = { 256, -6, 88, 0 };
	squareCoordinates[47] = { 256, 32, 88, 0 };
	squareCoordinates[48] = { 257, 66, 88, 0 };
	squareCoordinates[49] = { 257, 107, 88, 0 };
	squareCoordinates[50] = { 254, -111, 88, 0 };
	squareCoordinates[51] = { 255, -77, 88, 0 };
	squareCoordinates[52] = { 256, -38, 88, 0 };
	squareCoordinates[53] = { 256, -6, 88, 0 };
	squareCoordinates[54] = { 256, 32, 88, 0 };
	squareCoordinates[55] = { 257, 66, 88, 0 };
	squareCoordinates[56] = { 257, 107, 88, 0 };
	squareCoordinates[57] = { 254, -111, 88, 0 };
	squareCoordinates[58] = { 255, -77, 88, 0 };
	squareCoordinates[59] = { 256, -38, 88, 0 };
	squareCoordinates[60] = { 256, -6, 88, 0 };
	squareCoordinates[61] = { 256, 32, 88, 0 };
	squareCoordinates[62] = { 257, 66, 88, 0 };
	squareCoordinates[63] = { 257, 107, 88, 0 };

	kingCoordinates[0] = { -58, -220, -126, -90 };
	kingCoordinates[1] = { -13, -220, -126, -90 };
	kingCoordinates[2] = { 28, -220, -126, -90 };
	kingCoordinates[3] = { 75, -220, -126, -90 };
	kingCoordinates[4] = { -50, 223, -126, 90 };
	kingCoordinates[5] = { -11, 223, -126, 90 };
	kingCoordinates[6] = { 33, 223, -126, 90 };
	kingCoordinates[7] = { 78, 222, -126, 90 };

	removedPieceCoordinates[0] = { -58, -220, -126, -90 };
	removedPieceCoordinates[1] = { -13, -220, -126, -90 };
	removedPieceCoordinates[2] = { 28, -220, -126, -90 };
	removedPieceCoordinates[3] = { 75, -220, -126, -90 };
	removedPieceCoordinates[4] = { -50, 223, -126, 90 };
	removedPieceCoordinates[5] = { -11, 223, -126, 90 };
	removedPieceCoordinates[6] = { 33, 223, -126, 90 };
	removedPieceCoordinates[7] = { 78, 222, -126, 90 };
}

Robot::~Robot()
{
}

bool Robot::connect()
{
	std::cout << "Robot::connect" << std::endl;
	return true;

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
	}

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
	*/
}

void Robot::Home()
{
	std::cout << "Robot::Home" << std::endl;
	return;

	/*
	std::cout << "Resetting dobot position" << std::endl;
	HOMECmd homeCmd;
	uint64_t queuedCmdIndex;
	int resultDobotHome = SetHOMECmd(dobotId, &homeCmd, true, &queuedCmdIndex);
	if (resultDobotHome != DobotCommunicate_NoError) {
		std::cerr << "Failed to reset dobot position" << std::endl;
		return;
	}
	std::cout << "Dobot position successfully reset" << std::endl;

	goReadBoard(pieceCoordinates[0], 90);
	*/
}

void Robot::Play(int initPos, int newPos)
{
	std::cout << "Robot::Play" << std::endl;
	return;

	/*
	if (initPos == -1) {
		addKing(newPos);
		return;
	}
	if (newPos == -1) {
		removePiece(initPos);
		return;
	}
	if ((int)initPos / BOARDSIZE > 7 || (int)newPos / BOARDSIZE > 7) {
		std::cerr << "Invalid position" << std::endl;
		return;
	}

	std::cout << "Playing in column " << column << std::endl;
	grabPiece();
	goTo(columnCoordinates[column], 90);
	goTo(columnCoordinates[column]);
	openGripper();
	wait(0.5);
	turnOffGripper();
	if (remainingPieces > 0) {
		goTo(pieceCoordinates[(8 - remainingPieces)], 90);
	}
	else {
		goTo(pieceCoordinates[0], 90);
	}
	*/
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

int Robot::getRemainingKing()
{
	return remainingKing;
}

int Robot::getRemovedPieces()
{
	return removedPieces;
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
	if (resultDobotPTP != DobotCommunicate_NoError) {
		std::cerr << "Failed to move dobot to position" << std::endl;
	}
}

void Robot::goTo(Pose position, float z)
{
	Pose newPose = {position.x, position.y, z, position.r};
	goTo(newPose);
}

void Robot::goReadBoard()
{
	// #########################################################################
	return;
}

void Robot::addKing(int position)
{

	if (remainingKing== 0) {
		std::cerr << "No more king" << std::endl;
		return;
	}
	goTo(kingCoordinates[8 - remainingKing]);
	activSuctionCup();
	goTo(kingCoordinates[8 - remainingKing], 90);
	wait(0.5);
	remainingKing--;
	// #########################################################################
}

void Robot::removePiece(int position)
{

	if (removedPieces == 8) {
		std::cerr << "No more empty position" << std::endl;
		return;
	}
	// #########################################################################
}

void Robot::activSuctionCup()
{
	return;
	suctionCup(false, true);
}

void Robot::desactivSuctionCup()
{
	return;
	suctionCup(true, true);
}

void Robot::movePiece()
{
	return;
	openGripper();
	goTo(pieceCoordinates[8 - remainingPieces]);
	closeGripper();
	wait(0.5);
	goTo(pieceCoordinates[8 - remainingPieces], 90);
	remainingPieces--;
}

void Robot::gripper(bool close, bool on)
{ 
	return;
	uint64_t queuedCmdIndex;
	int resultDobotGripper = SetEndEffectorGripper(dobotId, on, close, true, &queuedCmdIndex);
	if (resultDobotGripper != DobotCommunicate_NoError) {
		std::cerr << "Failed to close gripper" << std::endl;
	}
}


void Robot::turnOffGripper()
{
	return;
	gripper(false, false);
}

void Robot::wait(float seconds)
{ 
	return;
	WAITCmd waitCmd = { 0 };
	waitCmd.timeout = seconds * 1000;

	uint64_t queuedCmdIndex;
	int resultDobotWait = SetWAITCmd(dobotId, &waitCmd, true, &queuedCmdIndex);
	if (resultDobotWait != DobotCommunicate_NoError) {
		std::cerr << "Failed to wait" << std::endl;
	}
}
