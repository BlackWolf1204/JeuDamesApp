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
		
		/* ###################################*/
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
			/* ###########################################*/
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
			/* #############################################
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
			/*if (lastPos % BOARDSIZE == 0 && board.getPiece(lastPos % BOARDSIZE, lastPos / BOARDSIZE) == 1)
			{
				// show that the piece need to be upgraded
			}*/
			/* ####################################*/
		}

	}
	uiController.stop(stateMachine.getState());
	/**/
	/*
	Board board;
	board.initBoard();
	while (!board.isTerminal())
	{
		board.printBoard();
		int pos = 0;
		int newpos = 0;
		int continuer = 1;
		// player
		while (continuer == 1)
		{
			cout << "Positions initial : ";
			cin >> pos;
			cout << "Nouvelle position : ";
			cin >> newpos;
			std::cout << pos << std::endl;
			std::cout << newpos << std::endl;
			std::cout << "Continuer ? (1/0) : ";
			cin >> continuer;
			board.Play(pos, newpos);
			board.newKing();
		}

		board.printBoard();
		// Robot
		TranspositionTable* transpositionTable = new TranspositionTable();
		std::vector<int> bestPositions = Negamax::GetBestMove(board, transpositionTable, 8);
		std::cout << "Reponse : ";
		for (int i = 0; i < bestPositions.size() - 1; i++)
		{
			std::cout << "(" << bestPositions[i] << ", " << bestPositions[i + 1] << ") ";
			board.Play(bestPositions[i], bestPositions[i + 1]);
			board.newKing();
		}
		std::cout << std::endl;
	}
	*/
	return 0;
}