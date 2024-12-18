#pragma warning(disable: 4996)
#include <opencv2/opencv.hpp>
#include "Robot.h"
#include "Board.h"
#include "Negamax.h"
#include "Camera.h"
#include "BoardDetector.h"
#include "TranspositionTable.h"
#include "uiController.h"

using namespace std;

int main()
{
	/* ###############################################
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
		/*
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
		}*/
		/* #######################################
		StateMachine::State newState = uiController.tick(stateMachine.getState());
		if (newState != stateMachine.getState()) {
			stateMachine.ChangeState(newState);
		}

		cv::Mat frame = camera->getFrame();
		uiController.getGameUI()->getCameraFrame(frame);
		cv::Mat copy = frame.clone();
		std::vector<cv::Mat> modifiedFrame = BoardDetector::modifyFrame(copy);

		if (modifiedFrame.size() > 0)
		{
			uiController.getFrameDetail()->getCameraFrame(modifiedFrame[0]);
			uiController.getFrameDetail()->getGrayFrame(modifiedFrame[1]);
			uiController.getFrameDetail()->getBlurFrame(modifiedFrame[2]);
			uiController.getFrameDetail()->getCannyFrame(modifiedFrame[3]);
		}
		
		if (frame.empty())
		{
			continue;
		}

		if (uiController.getGameUI()->restart)
		{
			uiController.getGameUI()->restart = false;
			Board newBoard;
			newBoard.initBoard();
			uiController.getGameUI()->updateBoard(uiController.getWindow(), newBoard);
		}

		Board board = BoardDetector::detectBoard(frame);
		uiController.getGameUI()->getCameraFrame(frame);

		if (board.isValid())
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
			}*/
			/* ##############################################
			board.printBoard();
			uiController.getGameUI()->updateBoard(uiController.getWindow(), board);
			/*
			std::vector<int> bestPositions = Negamax::GetBestMove(board, transpositionTable, 8);
			for (int i = 0; i < bestPositions.size() - 1; i++)
			{
				int column = bestPositions[i] % BOARDSIZE;
				int row = (int)bestPositions[i] / BOARDSIZE;
				int newCol = bestPositions[i + 1] % BOARDSIZE;
				int newRow = (int)bestPositions[i + 1] / BOARDSIZE;
				board.Play(bestPositions[i], bestPositions[i + 1]);

				// remove a player piece if eaten by robot's piece
				int eatPiece = board.MoveEatPiece(column, row, newCol, newRow);
				if (eatPiece != -1) {
					robot->Play(eatPiece, -1);
				}
				board.printBoard();
				robot->Play(bestPositions[i], bestPositions[i+1]);
			}
			
			// upgrade a piece into a king if at the opposite of the board (only for robot pieces)
			int lastPos = bestPositions.back();
			if (lastPos % BOARDSIZE == BOARDSIZE - 1 && board.getPiece(lastPos % BOARDSIZE, (int)lastPos / BOARDSIZE) == 2)
			{
				robot->Play(lastPos, -1);
				robot->Play(-1, lastPos);
			}
			if (lastPos % BOARDSIZE == 0 && board.getPiece(lastPos % BOARDSIZE, lastPos / BOARDSIZE) == 1)
			{
				// show that the piece need to be upgraded
			}*/
			/* ###################################
		}
	
	}
	uiController.stop(stateMachine.getState());
	############################################### */
	
	Board board;
	board.initBoard();
	/*
	board.setPlayerPiece(5, 5, true);

	board.setRobotPiece(0, 4, true);
	board.setRobotPiece(0, 6, true);
	board.upgradePiece(0, 6);
	board.setRobotPiece(1, 1, true);
	board.setRobotPiece(2, 0, true);
	board.setRobotPiece(3, 1, true);
	board.setRobotPiece(7, 5, true);
	*/

	while (!board.isTerminal())
	{
		board.printBoard();
		int pos = -1;
		int newpos = -1;
		int continuer = 1;
		// player
		while (continuer == 1)
		{
			while (!board.isValidMove(pos % BOARDSIZE, (int)pos / BOARDSIZE, newpos % BOARDSIZE, (int)newpos / BOARDSIZE))
			{
				cout << "Positions initial : ";
				cin >> pos;
				cout << "Nouvelle position : ";
				cin >> newpos;
			}
			std::cout << "Continuer ? (1/0) : ";
			cin >> continuer;
			board.Play(pos, newpos);
			board.newKing();
		}

		// Robot
		TranspositionTable* transpositionTable = new TranspositionTable();
		std::cout << "Beginning Negamax." << std::endl;
		std::vector<int> bestPositions = Negamax::GetBestMove(board, transpositionTable, 4);
		std::cout << "End Negamax." << std::endl;
		board.printBoard();
		if (bestPositions.size() > 0)
		{
			for (size_t i = 0; i < bestPositions.size() - 1; i++)
			{
				std::cout << bestPositions[i] << ", " << bestPositions[i + 1] << std::endl;
				board.Play(bestPositions[i], bestPositions[i + 1]);
				board.newKing();
			}
		}
		else
		{
			std::cout << "No moves found." << std::endl;
		}
	}
	
	return 0;
}