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
	// ###################################################################
}

Robot::~Robot()
{
}

bool Robot::connect()
{
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
}

void Robot::Home()
{
	std::cout << "Resetting dobot position" << std::endl;
	HOMECmd homeCmd;
	uint64_t queuedCmdIndex;
	int resultDobotHome = SetHOMECmd(dobotId, &homeCmd, true, &queuedCmdIndex);
	if (resultDobotHome != DobotCommunicate_NoError) {
		std::cerr << "Failed to reset dobot position" << std::endl;
		return;
	}
	std::cout << "Dobot position successfully reset" << std::endl;

	goReadBoard();
	
}

void Robot::Play(int initPos, int newPos)
{
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
	if (initPos != -1 && newPos != -1) {

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
	goTo({ 217, 62, 160,0 });
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
	goTo(removedPieceCoordinates[removedPieces], HIGHT);
	goTo(removedPieceCoordinates[removedPieces]);
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
	waitCmd.timeout = seconds * 1000;

	uint64_t queuedCmdIndex;
	int resultDobotWait = SetWAITCmd(dobotId, &waitCmd, true, &queuedCmdIndex);
	if (resultDobotWait != DobotCommunicate_NoError) {
		std::cerr << "Failed to wait" << std::endl;
	}
}
