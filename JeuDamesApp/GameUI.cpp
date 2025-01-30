#include "GameUI.h"


GameUI::GameUI()
{
	robot = nullptr;
	webcamImage = nullptr;
	webcamSprite = nullptr;
	webcamTexture = nullptr;
}

GameUI::~GameUI()
{
	if (webcamThread != nullptr)
	{
		webcamThreadRunningGame = false;
		webcamThread->join();
		delete webcamThread;
		webcamThread = nullptr;
	}
	delete webcamImage;
	delete webcamTexture;
	delete webcamSprite;
}

GameUI::GameUI(sf::RenderWindow& window, sf::Font* font, Robot* robot)
{
	backButton = Button();
	backButton.setDefaultButtonColor();
	backButton.setButtonSize(sf::Vector2f(250, 100));
	backButton.setButtonPosition(sf::Vector2f(10, 10));
	backButton.setButtonFont(font);
	backButton.setButtonText("Retour");
	backButton.setButtonTextSize(60);

	gameBoard.setFillColor(sf::Color(84, 56, 34));

	webcamImage = new sf::Image();
	webcamTexture = new sf::Texture();
	webcamSprite = new sf::Sprite();
	webcamSprite->setScale(0.7f, 0.7f);
	webcamSprite->setRotation(-90);

	for (int i = 0; i < BOARDSIZE * BOARDSIZE; i++)
	{
		sf::CircleShape circle;
		circle.setFillColor(sf::Color::Transparent);
		circlesPieces.push_back(circle);

		sf::RectangleShape squares;
		squares.setFillColor(sf::Color::Transparent);
		gameSquares.push_back(squares);

		sf::Text mark;
		mark.setFont(*font);
		mark.setString("K");
		mark.setFillColor(sf::Color::Transparent);
		kingMarks.push_back(mark);

	}

	for (int i = 0; i < BOARDSIZE; i++)
	{
		for (int j = 0; j < BOARDSIZE; j++)
		{
			if (i % 2 != j % 2)
				gameSquares[i + j * BOARDSIZE].setFillColor(sf::Color(105, 70, 42));
			else
				gameSquares[i + j * BOARDSIZE].setFillColor(sf::Color(168, 136, 109));
		}
	}

	loadingText.setFont(*font);
	loadingText.setString("Chargement de la camera, \n\tVeuillez patienter...");
	loadingText.setCharacterSize(30);
	loadingText.setFillColor(sf::Color::White);

	victoryText.setFont(*font);
	victoryText.setCharacterSize(70);
	victoryText.setFillColor(sf::Color::White);

	restartButton = Button();
	restartButton.setDefaultButtonColor();
	restartButton.setButtonSize(sf::Vector2f(250, 100));
	restartButton.setButtonFont(font);
	restartButton.setButtonText("Réinitialiser");
	restartButton.setButtonTextSize(60);

	refillButton = Button();
	refillButton.setDefaultButtonColor();
	refillButton.setButtonSize(sf::Vector2f(250, 100));
	refillButton.setButtonPosition(sf::Vector2f(10, 130));
	refillButton.setButtonFont(font);
	refillButton.setButtonText("Recharger");
	refillButton.setButtonTextSize(60);

	playButton = Button();
	playButton.setDefaultButtonColor();
	playButton.setButtonSize(sf::Vector2f(250, 100));
	playButton.setButtonFont(font);
	playButton.setButtonText("Jouer");
	playButton.setButtonTextSize(60);

	left_available_pieces.setFillColor(sf::Color(84, 56, 34));

	for (int i = 0; i < 8; i++)
	{
		sf::CircleShape circle;
		circle.setFillColor(sf::Color::White);
		availablePieces.push_back(circle);

		sf::Text kingMark;
		kingMark.setFont(*font);
		kingMark.setString("K");
		kingMark.setFillColor(sf::Color(0, 0, 0, 70));
		availableKingMarks.push_back(kingMark);
	}

	this->robot = robot;
}

void GameUI::draw(sf::RenderWindow& window)
{
	sf::Vector2u windowSize = window.getSize();

	// Update the playing and restart button position according to the winsow size
	playButton.setButtonPosition(sf::Vector2f((float)windowSize.x - playButton.getButtonSize().x - 10, 10));
	restartButton.setButtonPosition(sf::Vector2f((float)windowSize.x - restartButton.getButtonSize().x - 10, playButton.getButtonSize().y + 30));

	// Update the board size and position according to the window size
	gameBoard.setSize(sf::Vector2f((float)(windowSize.y * 0.5), (float)(windowSize.y * 0.5)));
	gameBoard.setPosition(sf::Vector2f(windowSize.x / 2 - gameBoard.getSize().x / 2, windowSize.y - gameBoard.getSize().y - 10));

	// Update the circles size and position according to the game board size and position
	for (int i = 0; i < BOARDSIZE; i++)
	{
		for (int j = 0; j < BOARDSIZE; j++)
		{
			circlesPieces[i + j * BOARDSIZE].setPosition(sf::Vector2f((gameBoard.getPosition().x + 10) + i * (gameBoard.getSize().x - 20) / BOARDSIZE + 5, (gameBoard.getPosition().y + 10) + j * (gameBoard.getSize().y - 20) / BOARDSIZE + 5));
			circlesPieces[i + j * BOARDSIZE].setRadius((float)windowSize.y / 42);
			
			kingMarks[i + j * BOARDSIZE].setCharacterSize((float)circlesPieces[0].getRadius() * 3 / 2);
			kingMarks[i + j * BOARDSIZE].setPosition(sf::Vector2f(circlesPieces[i + j * BOARDSIZE].getPosition().x + circlesPieces[i + j * BOARDSIZE].getRadius() * 3 / 5, circlesPieces[i + j * BOARDSIZE].getPosition().y - circlesPieces[i + j * BOARDSIZE].getRadius() * 1 / 5));
		}
	}

	// Update the squares size and position according to the game board size and position
	for (int i = 0; i < BOARDSIZE; i++)
	{
		for (int j = 0; j < BOARDSIZE; j++)
		{
			gameSquares[i + j * BOARDSIZE].setPosition(sf::Vector2f((gameBoard.getPosition().x + 10) + i * (gameBoard.getSize().x - 20) / BOARDSIZE, (gameBoard.getPosition().y + 10) + j * (gameBoard.getSize().y - 20) / BOARDSIZE));
			gameSquares[i + j * BOARDSIZE].setSize(sf::Vector2f((gameBoard.getSize().x - 20) / BOARDSIZE, (gameBoard.getSize().y - 20) / BOARDSIZE));
		}
	}

	// Update the available pieces size and position according to the window size
	left_available_pieces.setSize(sf::Vector2f((float)windowSize.x / 11, (float)windowSize.y / 3));
	left_available_pieces.setPosition(sf::Vector2f(windowSize.x / 2 - gameBoard.getSize().x / 2 - 10 - left_available_pieces.getSize().x, gameBoard.getPosition().y));

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			availablePieces[i + j * 2].setRadius((float)windowSize.y / 40);
			availablePieces[i + j * 2].setPosition(sf::Vector2f(left_available_pieces.getPosition().x + i * gameBoard.getSize().x / 6 + 10, left_available_pieces.getPosition().y + j * gameBoard.getSize().y / 6 + 10));
			
			availableKingMarks[i + j * 2].setCharacterSize((float)availablePieces[0].getRadius() * 3 / 2);
			availableKingMarks[i + j * 2].setPosition(sf::Vector2f(availablePieces[i + j * 2].getPosition().x + availablePieces[i + j * 2].getRadius() * 3 / 5, availablePieces[i + j * 2].getPosition().y - availablePieces[i + j * 2].getRadius() * 1 / 5));
		}
	}

	// Update the webcam feed size and position according to the window size
	if (webcamTexture->getSize().x > 0 && webcamTexture->getSize().y > 0)
	{
		float scaleX = windowSize.x / webcamTexture->getSize().x * 0.5f;
		float scaleY = windowSize.y / webcamTexture->getSize().y * 0.5f;
		float scale = std::min(scaleX, scaleY);
		webcamSprite->setScale(scale, scale);
	}

	webcamSprite->setPosition(sf::Vector2f(windowSize.x / 2 - webcamSprite->getGlobalBounds().width / 2 - 10, (windowSize.y - gameBoard.getPosition().y) / 2 + webcamSprite->getGlobalBounds().height / 2 - 10));
	
	// Update the loading text size and position according to the window size
	loadingText.setPosition(sf::Vector2f(windowSize.x / 2 - loadingText.getGlobalBounds().width / 2, 100));

	
	window.draw(loadingText);
	window.draw(*webcamSprite);

	window.draw(gameBoard);
	for (int i = 0; i < BOARDSIZE * BOARDSIZE; i++)
	{
		window.draw(gameSquares[i]);
	}
	for (int i = 0; i < BOARDSIZE * BOARDSIZE; i++)
	{
		window.draw(circlesPieces[i]);
		window.draw(kingMarks[i]);
	}

	window.draw(left_available_pieces);

	for (int i = 0; i < robot->getRemainingKing(); i++)
	{
		window.draw(availablePieces[7 - i]);
		window.draw(availableKingMarks[7 - i]);
	}

	backButton.draw(window);
	restartButton.draw(window);
	refillButton.draw(window);
	playButton.draw(window);

	if (victoryVisible)
	{
		victoryText.setPosition(sf::Vector2f(windowSize.x / 2 - victoryText.getGlobalBounds().width / 2, windowSize.y / 2 - victoryText.getGlobalBounds().height / 2));
		window.draw(victoryText);
	}
}

void GameUI::getCameraFrame(cv::Mat frame)
{
	if (frame.empty())
	{
		return;
	}
	int frameWidth = frame.cols;
	int frameHeight = frame.rows;
	// cut the left and right sides of the frame
	int diff = (frameWidth - frameHeight) / 2;
	sf::Uint8* pixels = new sf::Uint8[4 * frameHeight * frameHeight];
	for (int i = 0; i < frameHeight; i++)
	{
		for (int j = 0; j < frameHeight; j++)
		{
			cv::Vec3b color = frame.at<cv::Vec3b>(j, i + diff);
			pixels[(i + j * frameHeight) * 4] = color[2];
			pixels[(i + j * frameHeight) * 4 + 1] = color[1];
			pixels[(i + j * frameHeight) * 4 + 2] = color[0];
			pixels[(i + j * frameHeight) * 4 + 3] = 255;
		}
	}
	webcamImage->create(frameHeight, frameHeight, pixels);
	delete[] pixels;
	webcamTexture->loadFromImage(*webcamImage);
	webcamSprite->setTexture(*webcamTexture);

	loadingText.setFillColor(sf::Color::Transparent);
}

StateMachine::State GameUI::handleEvent(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		victoryVisible = false;
		if (backButton.mouseIsInsideButton(sf::Vector2f(float(event.mouseButton.x), float(event.mouseButton.y))))
		{
			std::cout << "Back button pressed" << std::endl;
			backButton.setDefaultButtonColor();
			return StateMachine::State::MainMenu;
		}
		if (restartButton.mouseIsInsideButton(sf::Vector2f(float(event.mouseButton.x), float(event.mouseButton.y))))
		{
			std::cout << "Restart button pressed" << std::endl;
			restartButton.setDefaultButtonColor();
			victoryVisible = false;
			restart = true;
		}
		if (refillButton.mouseIsInsideButton(sf::Vector2f(float(event.mouseButton.x), float(event.mouseButton.y))))
		{
			std::cout << "Refill button pressed" << std::endl;
			refillButton.setDefaultButtonColor();
			robot->Refill();
		}
		if (playButton.mouseIsInsideButton(sf::Vector2f(float(event.mouseButton.x), float(event.mouseButton.y))))
		{
			std::cout << "Play button pressed" << std::endl;
			playButton.setDefaultButtonColor();
			if (robot->getPlaying() == Robot::PlayingState::WAIT)
				robot->setPlaying(Robot::PlayingState::BEGIN);
		}
	}
	if (event.type == sf::Event::MouseMoved)
	{
		if (backButton.mouseIsInsideButton(sf::Vector2f(float(event.mouseMove.x), float(event.mouseMove.y))))
		{
			backButton.setSelectedButtonColor();
			restartButton.setDefaultButtonColor();
			refillButton.setDefaultButtonColor();
			playButton.setDefaultButtonColor();
		}
		else if (restartButton.mouseIsInsideButton(sf::Vector2f(float(event.mouseMove.x), float(event.mouseMove.y))))
		{
			restartButton.setSelectedButtonColor();
			backButton.setDefaultButtonColor();
			refillButton.setDefaultButtonColor();
			playButton.setDefaultButtonColor();
		}
		else if (refillButton.mouseIsInsideButton(sf::Vector2f(float(event.mouseMove.x), float(event.mouseMove.y))))
		{
			refillButton.setSelectedButtonColor();
			backButton.setDefaultButtonColor();
			restartButton.setDefaultButtonColor();
			playButton.setDefaultButtonColor();
		}
		else if (playButton.mouseIsInsideButton(sf::Vector2f(float(event.mouseMove.x), float(event.mouseMove.y))))
		{
			playButton.setSelectedButtonColor();
			backButton.setDefaultButtonColor();
			restartButton.setDefaultButtonColor();
			refillButton.setDefaultButtonColor();
		}
		else
		{
			backButton.setDefaultButtonColor();
			restartButton.setDefaultButtonColor();
			refillButton.setDefaultButtonColor();
			playButton.setDefaultButtonColor();
		}
	}
	return StateMachine::State::Game;
}

void GameUI::updateBoard(sf::RenderWindow& window, Board board)
{
	for (int i = 0; i < BOARDSIZE; i++)
	{
		for (int j = 0; j < BOARDSIZE; j++)
		{
			if (i % 2 != j % 2)
				gameSquares[j + i * BOARDSIZE].setFillColor(sf::Color(105, 70, 42));
			else
				gameSquares[j + i * BOARDSIZE].setFillColor(sf::Color(168, 136, 109));
		}
	}

	for (int i = 0; i < BOARDSIZE; i++)
	{
		for (int j = 0; j < BOARDSIZE; j++)
		{
			int piece = board.getPiece(BOARDSIZE - j - 1, i);
			if (piece == 0)
			{
				circlesPieces[j + i * BOARDSIZE].setFillColor(sf::Color::Transparent);
				kingMarks[j + i * BOARDSIZE].setFillColor(sf::Color::Transparent);
			}
			else if (piece % 2 == 1) {
				std::vector<std::vector<int>> positions = board.canMoveEat(BOARDSIZE - j - 1, i);

				for (int c = 0; c < positions[1].size(); c++)
				{
					int reste = positions[1][c] % BOARDSIZE;
					gameSquares[(BOARDSIZE - reste - 1) + (positions[1][c] - reste)].setFillColor(sf::Color(250, 137, 45));
					gameSquares[j + i * BOARDSIZE].setFillColor(sf::Color(63, 183, 224));
				}
			}
			if (piece == 1)
				circlesPieces[j + i * BOARDSIZE].setFillColor(sf::Color::Green);
			else if (piece == 3)
			{
				circlesPieces[j + i * BOARDSIZE].setFillColor(sf::Color::Green);
				kingMarks[j + i * BOARDSIZE].setFillColor(sf::Color(0, 0, 0, 70));
			}
			else if (piece == 2)
				circlesPieces[j + i * BOARDSIZE].setFillColor(sf::Color::White);
			else if (piece == 4)
			{
				circlesPieces[j + i * BOARDSIZE].setFillColor(sf::Color::White);
				kingMarks[j + i * BOARDSIZE].setFillColor(sf::Color(0, 0, 0, 70));
			}
		}
	}
	return;
}

void GameUI::playerVictory(sf::RenderWindow& window)
{
	victoryVisible = true;
	victoryText.setString("Victoire du joueur !");
}

void GameUI::playerDefeat(sf::RenderWindow& window)
{
	victoryVisible = true;
	victoryText.setString("Defaite du joueur !");
}
