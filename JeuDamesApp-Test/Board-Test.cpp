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

		TEST_METHOD(TestIsValidMove)
		{
			// For robot pieces
			// Can go forward
			board->setRobotPiece(0, 0, true);
			Assert::AreEqual(true, board->isValidMove(0, 0, 1, 1));

			// Can't go forward (don't move forward)
			board->setRobotPiece(6, 6, true);
			Assert::AreEqual(false, board->isValidMove(6, 6, 5, 5));
			board->setRobotPiece(6, 6, false);

			// Can't go forward (don't move in diagonal)
			Assert::AreEqual(false, board->isValidMove(0, 0, 1, 0));

			// Can't go forward (too much case forward without eating)
			Assert::AreEqual(false, board->isValidMove(0, 0, 2, 2));

			// Can eat (piece)
			board->setPlayerPiece(1, 1, true);
			Assert::AreEqual(true, board->isValidMove(0, 0, 2, 2));

			// Can't eat (move too far)
			Assert::AreEqual(false, board->isValidMove(0, 0, 3, 3));

			// Can move (king)
			board->upgradePiece(0, 0);
			Assert::AreEqual(true, board->isValidMove(0, 0, 3, 3));

			// Can eat (king)
			board->setPlayerPiece(1, 1, true);
			Assert::AreEqual(true, board->isValidMove(0, 0, 3, 3));

			// Can't eat (eat more than one opponent piece)
			board->setPlayerPiece(2, 2, true);
			Assert::AreEqual(false, board->isValidMove(0, 0, 3, 3));

			// Can't eat (eat a piece of his side)
			board->setPlayerPiece(1, 1, false);
			board->setPlayerPiece(2, 2, false);
			board->setRobotPiece(2, 2, true);
			Assert::AreEqual(false, board->isValidMove(0, 0, 3, 3));
			board->setRobotPiece(2, 2, false);
			board->setRobotPiece(0, 0, false);

			// For player pieces
			// Can go forward
			board->setPlayerPiece(7, 7, true);
			Assert::AreEqual(true, board->isValidMove(7, 7, 6, 6));

			// Can't go forward (don't move forward)
			board->setPlayerPiece(0, 0, true);
			Assert::AreEqual(false, board->isValidMove(0, 0, 1, 1));
			board->setPlayerPiece(0, 0, false);

			// Can't go forward (don't move in diagonal)
			Assert::AreEqual(false, board->isValidMove(7, 7, 6, 7));

			// Can't go forward (too much case forward without eating)
			Assert::AreEqual(false, board->isValidMove(7, 7, 5, 5));

			// Can eat (piece)
			board->setRobotPiece(6, 6, true);
			Assert::AreEqual(true, board->isValidMove(7, 7, 5, 5));

			// Can't eat (move too far)
			Assert::AreEqual(false, board->isValidMove(7, 7, 4, 4));

			// Can move (king)
			board->upgradePiece(7, 7);
			Assert::AreEqual(true, board->isValidMove(7, 7, 4, 4));

			// Can eat (king)
			board->setRobotPiece(6, 6, true);
			Assert::AreEqual(true, board->isValidMove(7, 7, 4, 4));

			// Can't eat (eat more than one opponent piece)
			board->setRobotPiece(5, 5, true);
			Assert::AreEqual(false, board->isValidMove(7, 7, 4, 4));

			// Can't eat (eat a piece of his side)
			board->setRobotPiece(6, 6, false);
			board->setRobotPiece(5, 5, false);
			board->setPlayerPiece(5, 5, true);
			Assert::AreEqual(false, board->isValidMove(7, 7, 4, 4));
			board->setPlayerPiece(5, 5, false);
			board->setPlayerPiece(7, 7, false);
		}
	
		TEST_METHOD(TestCanEat)
		{
			// For robot pieces
			// Can't eat
			board->setRobotPiece(0, 0, true);
			Assert::AreEqual((size_t)0, board->canEat(0, 0).size());

			// Can eat
			board->setPlayerPiece(1, 1, true);
			Assert::AreEqual((size_t)1, board->canEat(0, 0).size());
			Assert::AreEqual(9, board->canEat(0, 0)[0]);
			board->setPlayerPiece(1, 1, false);

			// Can't eat (king)
			board->upgradePiece(0, 0);
			Assert::AreEqual((size_t)0, board->canEat(0, 0).size());

			// Can eat (king)
			board->setPlayerPiece(2, 2, true);
			Assert::AreEqual((size_t)1, board->canEat(0, 0).size());
			Assert::AreEqual(18, board->canEat(0, 0)[0]);
			board->setPlayerPiece(2, 2, false);
			board->setRobotPiece(0, 0, false);

			// For player pieces
			// Can't eat
			board->setPlayerPiece(7, 0, true);
			Assert::AreEqual((size_t)0, board->canEat(7, 0).size());

			// Can eat
			board->setRobotPiece(6, 1, true);
			Assert::AreEqual((size_t)1, board->canEat(7, 0).size());
			Assert::AreEqual(14, board->canEat(7, 0)[0]);
			board->setRobotPiece(6, 1, false);

			// Can't eat (king)
			board->upgradePiece(7, 0);
			Assert::AreEqual((size_t)0, board->canEat(7, 0).size());

			// Can eat (king)
			board->setRobotPiece(5, 2, true);
			Assert::AreEqual((size_t)1, board->canEat(7, 0).size());
			Assert::AreEqual(21, board->canEat(7, 0)[0]);
		}
	
	};
}
