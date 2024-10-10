#include "uiController.h"
#include <opencv2/opencv.hpp>
#include "Robot.h"
#include "Board.h"
#include "Negamax.h"
#include "Camera.h"
#include "BoardDetector.h"
#include "TranspositionTable.h"

using namespace std;

int main()
{
	sf::Vector2u windowSize(1280, 720);
	Robot* robot = new Robot();
	uiController uiController(windowSize, robot);
	StateMachine stateMachine;
	Camera* camera = new Camera();
	TranspositionTable* transpositionTable = new TranspositionTable();
	int moveNumber = -1;
	bool isConnected = false;

	
	while (uiController.getWindow().isOpen())
	{
		if (!isConnected)
		{
			isConnected = robot->connect();
			if (isConnected)
			{
				robot->Home();
			}
			else
			{
				continue;
			}
		}

		StateMachine::State newState = uiController.tick(stateMachine.getState());
		if (newState != stateMachine.getState()) {
			stateMachine.ChangeState(newState);
		}

		cv::Mat frame = camera->getFrame();

		uiController.getGameUI()->getCameraFrame(frame);

		if (frame.empty())
		{
			continue;
		}



		if (uiController.getGameUI()->restart)
		{
			moveNumber = -1;
			uiController.getGameUI()->restart = false;
			Board emptyBoard;
			uiController.getGameUI()->updateBoard(uiController.getWindow(), emptyBoard);
		}

		Board board = BoardDetector::detectBoard(frame, BoardDetector::Color::RED);
		uiController.getGameUI()->getCameraFrame(frame);

		if (!board.isInit() && board.isValid())
		{
			if (board.playerWins())
			{
				uiController.getGameUI()->updateBoard(uiController.getWindow(), board);
				uiController.getGameUI()->playerVictory(uiController.getWindow());
				moveNumber = -1;
				continue;
			}
			else if (board.robotWins())
			{
				uiController.getGameUI()->updateBoard(uiController.getWindow(), board);
				uiController.getGameUI()->playerDefeat(uiController.getWindow());
				moveNumber = -1;
				continue;
			}
			/*
			if (moveNumber == -1)
			{
				if (board.getMoveNumber() % 2 == 1)
				{
					moveNumber = board.getMoveNumber() - 1;
				}
				else
				{
					moveNumber = board.getMoveNumber();
				}
			}
			*/
			board.printBoard();
			uiController.getGameUI()->updateBoard(uiController.getWindow(), board);
			/*
			if (board.getMoveNumber() == moveNumber + 1 && board.getMoveNumber() % 2 == 1)
			{
				moveNumber += 2;
				int bestMove = Negamax::GetBestMove(board, transpositionTable, 8);
				board.Play(bestMove);
				board.printBoard();
				robot->Play(bestMove);
			}*/
		}

	}
	uiController.stop(stateMachine.getState());

	return 0;
}