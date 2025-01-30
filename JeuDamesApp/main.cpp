#pragma warning(disable: 4996)
#include <opencv2/opencv.hpp>
#include <thread>
#include <chrono>
#include "Robot.h"
#include "Board.h"
#include "Negamax.h"
#include "Camera.h"
#include "BoardDetector.h"
#include "uiController.h"

using namespace std;

void robotPlay(Board* board, Robot* robot)
{
	robot->setPlaying(Robot::PlayingState::DOING);
	std::cout << "Begin Negamax." << std::endl;
	std::vector<int> bestPositions = Negamax::GetBestMove(*board, 4);
	std::cout << "End Negamax." << std::endl;
	if (bestPositions.size() > 0)
	{
		for (int i = 0; i < bestPositions.size() - 1; i++)
		{
			int column = bestPositions[i] % BOARDSIZE;
			int row = (int)bestPositions[i] / BOARDSIZE;
			int newCol = bestPositions[i + 1] % BOARDSIZE;
			int newRow = (int)bestPositions[i + 1] / BOARDSIZE;

			robot->Play(bestPositions[i], bestPositions[i + 1]);
			// remove a player piece if eaten by robot's piece
			int eatPiece = board->MoveEatPiece(column, row, newCol, newRow);
			if (eatPiece != -1) {
				robot->Play(eatPiece, -1);
			}
			board->Play(bestPositions[i], bestPositions[i + 1]);
		}

		// upgrade a piece into a king if at the opposite of the board (only for robot pieces)
		int lastPos = bestPositions.back();
		if (lastPos / BOARDSIZE == BOARDSIZE - 1 && board->getPiece(lastPos % BOARDSIZE, (int)lastPos / BOARDSIZE) == 2)
		{
			board->upgradePiece(lastPos % BOARDSIZE, (int)lastPos / BOARDSIZE);
			robot->Play(lastPos, -1);
			robot->Play(-1, lastPos);
		}
	}
	else
		std::cerr << "No move found." << std::endl;
	robot->goReadBoard();
	this_thread::sleep_for(chrono::seconds(1));		// Let the robot move before verifing if robot->allCmdExecuted() is true
}

int main()
{
	// Initialise
	sf::Vector2u windowSize(1280, 720);
	Robot* robot = new Robot();
	uiController uiController(windowSize, robot);
	StateMachine stateMachine;
	Camera* camera = new Camera();
	Board board;
	board.initBoard();
	int moveNumber = 0;
	bool isConnected = false;
	while (uiController.getWindow().isOpen())
	{
		// Connect the robot
		if (!isConnected)
		{
			isConnected = robot->connect(uiController.getMainMenu()->portText);
			if (isConnected)
			{
				robot->Home();
				//robot->setPlaying(Robot::PlayingState::WAIT);
				this_thread::sleep_for(chrono::seconds(1));		// Let the robot move before verifing if robot->allCmdExecuted() is true
			}
		}

		// Control of UIs
		StateMachine::State newState = uiController.tick(stateMachine.getState());
		if (newState != stateMachine.getState())
			stateMachine.ChangeState(newState);

		// Update game frame
		cv::Mat frame = camera->getFrame();
		uiController.getGameUI()->getCameraFrame(frame);

		// Update frame detail
		cv::Mat copy = frame.clone();
		std::vector<cv::Mat> modifiedFrame = BoardDetector::modifyFrame(copy);
		if (uiController.getFrameDetail()->getDisplayed() && modifiedFrame.size() > 0)
		{
			uiController.getFrameDetail()->getCameraFrame(modifiedFrame[0]);
			uiController.getFrameDetail()->getGrayFrame(modifiedFrame[1]);
			uiController.getFrameDetail()->getBlurFrame(modifiedFrame[2]);
			uiController.getFrameDetail()->getCannyFrame(modifiedFrame[3]);
		}
		
		if (isConnected)
		{
			// Update board, camera frame
			if (robot->getPlaying() == Robot::PlayingState::WAIT)
			{
				Board newBoard = BoardDetector::detectBoard(frame);
				newBoard.setMoveNumber(board.getMoveNumber());
				board = newBoard;
				uiController.getGameUI()->getCameraFrame(frame);
			}
		}

		if (frame.empty())
		{
			continue;
		}

		// Initialise the board
		if (uiController.getGameUI()->restart)
		{
			uiController.getGameUI()->restart = false;
			board.initBoard();
			uiController.getGameUI()->updateBoard(uiController.getWindow(), board);
		}

		if (isConnected)
		{
			// Switch to wainting mode if robot ended playing
			if (robot->allCmdExecuted() && robot->getPlaying() == Robot::PlayingState::DOING)
				robot->setPlaying(Robot::PlayingState::WAIT);

			if (board.isValid())
			{
				// Update board and displayed board
				if (robot->getPlaying() == Robot::PlayingState::WAIT)
				{
					board.printBoard();
					uiController.getGameUI()->updateBoard(uiController.getWindow(), board);

					// Display victory message
					if (board.playerWins())
					{
						uiController.getGameUI()->playerVictory(uiController.getWindow());
						continue;
					}
					else if (board.robotWins())
					{
						uiController.getGameUI()->playerDefeat(uiController.getWindow());
						continue;
					}
				}

				// Robot's turn to play
				if (robot->getPlaying() == Robot::PlayingState::BEGIN)
				{
					robotPlay(&board, robot);
				}
			}
		}
	}

	uiController.stop(stateMachine.getState());
	return 0;
}