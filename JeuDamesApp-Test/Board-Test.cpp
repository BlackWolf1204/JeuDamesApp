#include "pch.h"
#include "CppUnitTest.h"
#include "../JeuDamesApp/Board.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BoardTest
{
	TEST_CLASS(BoardTest)
	{
	private:

		Board* board;

	public:

		TEST_METHOD_INITIALIZE(TestInitialize)
		{
			board = new Board();
		}


		TEST_METHOD(TestIsValidMoveForward)
		{

			// Can go forward
			board->setRobotPiece(0, 0, true);
			Assert::AreEqual(board->isValidMoveForward(0, 0, 1, 0), true);

			// Can't go forward (don't move forward)
			board->setRobotPiece(6, 6, true);
			Assert::AreEqual(board->isValidMoveForward(6, 6, 5, 6), false);
			board->setRobotPiece(6, 6, false);

			// Can't go forward (don't move in the column)
			Assert::AreEqual(board->isValidMoveForward(0, 0, 1, 1), true);

			// Can't go forward (piece in front)
			board->setPlayerPiece(1, 0, true);
			Assert::AreEqual(board->isValidMoveForward(0, 0, 1, 0), false);

			// Can't go forward (to much case forward)
			board->setPlayerPiece(1, 0, false);
			Assert::AreEqual(board->isValidMoveForward(0, 0, 2, 0), false);

			// Can't go forward (eat to mush opponent piece)
			board->upgradePiece(0, 0);
			board->setPlayerPiece(1, 0, true);
			board->setPlayerPiece(2, 0, true);
			Assert::AreEqual(board->isValidMoveForward(0, 0, 3, 0), false);

			// Can go forward (king)
			board->setPlayerPiece(1, 0, false);
			board->setPlayerPiece(2, 0, false);
			Assert::AreEqual(board->isValidMoveForward(0, 0, 2, 0), true);

			// Can't go forward (eat a piece of his side)
			board->setRobotPiece(1, 0, true);
			Assert::AreEqual(board->isValidMoveForward(0, 0, 2, 0), false);
		}

		TEST_METHOD(TestCheckWin_EatPiece)
		{
			// Can eat (piece)
			board->setPlayerPiece(1, 1, true);
			board->setRobotPiece(0, 0, true);
			Assert::AreEqual(board->isValidMoveDiagonal(0, 0, 2, 2), true);

			// Can't eat (move to far)
			Assert::AreEqual(board->isValidMoveDiagonal(0, 0, 3, 3), true);

			// Can't eat (don't move in diagonal)
			Assert::AreEqual(board->isValidMoveDiagonal(0, 0, 1, 2), true);

			// Can't eat (no piece to eat)
			board->setPlayerPiece(1, 1, false);
			board->setRobotPiece(0, 0, true);
			Assert::AreEqual(board->isValidMoveDiagonal(0, 0, 2, 2), false);

			// Can move (king)
			board->upgradePiece(0, 0);
			Assert::AreEqual(board->isValidMoveDiagonal(0, 0, 3, 3), true);

			// Can eat (king)
			board->setPlayerPiece(1, 1, true);
			Assert::AreEqual(board->isValidMoveDiagonal(0, 0, 3, 3), true);

			// Can't eat (eat more than one opponent piece)
			board->setPlayerPiece(2, 2, true);
			Assert::AreEqual(board->isValidMoveDiagonal(0, 0, 3, 3), false);

			// Can't eat (eat a piece of his side)
			board->setPlayerPiece(1, 1, false);
			board->setPlayerPiece(2, 2, false);
			board->setRobotPiece(2, 2, true);
			Assert::AreEqual(board->isValidMoveDiagonal(0, 0, 3, 3), false);

		}

	};
}
