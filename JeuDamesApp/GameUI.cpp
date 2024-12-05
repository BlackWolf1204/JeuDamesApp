#include "GameUI.h"


GameUI::GameUI()
{
}

GameUI::~GameUI()
{
	if (webcamThread != nullptr)
	{
		webcamThreadRunning = false;
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
	backButton.setButtonColor(sf::Color::Red);
	backButton.setButtonSize(sf::Vector2f(250, 100));
	backButton.setButtonPosition(sf::Vector2f(10, 10));
	//backButton.setButtonFont(font);
	backButton.setButtonTextColor(sf::Color::White);
	backButton.setButtonText("Retour");
	backButton.setButtonTextSize(80);

	gameBoard.setFillColor(sf::Color(36, 193, 224));

	webcamImage = new sf::Image();
	webcamTexture = new sf::Texture();
	webcamSprite = new sf::Sprite();
	webcamSprite->setScale(0.7, 0.7);
	webcamSprite->setRotation(-90);

	for (int i = 0; i < BOARDSIZE * BOARDSIZE; i++)
	{
		sf::CircleShape circle;
		circle.setFillColor(sf::Color::Transparent);
		circlesPieces.push_back(circle);
	}

	for (int i = 0; i < BOARDSIZE * BOARDSIZE; i++)
	{
		sf::RectangleShape squares;
		squares.setFillColor(sf::Color::Transparent);
		gameSquares.push_back(squares);
	}

	//loadingText.setFont(*font);
	loadingText.setString("Chargement de la camera, \nVeuillez patienter...");
	loadingText.setCharacterSize(30);
	loadingText.setFillColor(sf::Color::White);

	victoryText.setFont(*font);
	//victoryText.setCharacterSize(80);
	victoryText.setFillColor(sf::Color::White);

	restartButton = Button();
	restartButton.setButtonColor(sf::Color::Red);
	restartButton.setButtonSize(sf::Vector2f(250, 100));
	restartButton.setButtonPosition(sf::Vector2f(10, 130));
	//restartButton.setButtonFont(font);
	restartButton.setButtonTextColor(sf::Color::White);
	restartButton.setButtonText("Rejouer");
	restartButton.setButtonTextSize(78);

	refillButton = Button();
	refillButton.setButtonColor(sf::Color::Red);
	refillButton.setButtonSize(sf::Vector2f(250, 100));
	refillButton.setButtonPosition(sf::Vector2f(10, 250));
	//refillButton.setButtonFont(font);
	refillButton.setButtonTextColor(sf::Color::White);
	refillButton.setButtonText("Recharger");
	refillButton.setButtonTextSize(62);

	frameDetailButton = Button();
	frameDetailButton.setButtonColor(sf::Color::Red);
	frameDetailButton.setButtonSize(sf::Vector2f(300, 100));
	frameDetailButton.setButtonPosition(sf::Vector2f(window.getSize().x - 310, 10));
	//frameDetailButton.setButtonFont(font);
	frameDetailButton.setButtonTextColor(sf::Color::White);
	frameDetailButton.setButtonText("Image Details");
	frameDetailButton.setButtonTextSize(80);

	left_available_pieces.setFillColor(sf::Color(46, 161, 0));

	for (int i = 0; i < 8; i++)
	{
		sf::CircleShape circle;
		circle.setFillColor(sf::Color::White);
		availablePieces.push_back(circle);
	}

	this->robot = robot;
}

void GameUI::draw(sf::RenderWindow& window)
{
	sf::Vector2u windowSize = window.getSize();

	// Update the board size and position according to the window size
	gameBoard.setSize(sf::Vector2f(windowSize.y * 0.5, windowSize.y * 0.5));
	gameBoard.setPosition(sf::Vector2f(windowSize.x / 2 - gameBoard.getSize().x / 2, windowSize.y - gameBoard.getSize().y - 10));

	// Update the circles size and position according to the game board size and position
	for (int i = 0; i < BOARDSIZE; i++)
	{
		for (int j = 0; j < BOARDSIZE; j++)
		{
			circlesPieces[i + j * BOARDSIZE].setPosition(sf::Vector2f(gameBoard.getPosition().x + i * gameBoard.getSize().x / BOARDSIZE + 5, gameBoard.getPosition().y + j * gameBoard.getSize().y / BOARDSIZE + 5));
			circlesPieces[i + j * BOARDSIZE].setRadius(windowSize.y / 40);
		}
	}

	// Update the squares size and position according to the game board size and position
	for (int i = 0; i < BOARDSIZE; i++)
	{
		for (int j = 0; j < BOARDSIZE; j++)
		{
			if (i % 2 != j % 2)
			{
				gameSquares[i + j * BOARDSIZE].setPosition(sf::Vector2f(gameBoard.getPosition().x + i * gameBoard.getSize().x / BOARDSIZE, gameBoard.getPosition().y + j * gameBoard.getSize().y / BOARDSIZE));
				gameSquares[i + j * BOARDSIZE].setSize(sf::Vector2f(gameBoard.getSize().x / BOARDSIZE, gameBoard.getSize().y / BOARDSIZE));
				gameSquares[i + j * BOARDSIZE].setFillColor(sf::Color(30, 6, 91));
			}
		}
	}

	// Update the available pieces size and position according to the window size
	left_available_pieces.setSize(sf::Vector2f(windowSize.x / 11, windowSize.y / 3));
	left_available_pieces.setPosition(sf::Vector2f(windowSize.x / 2 - gameBoard.getSize().x / 2 - 10 - left_available_pieces.getSize().x, gameBoard.getPosition().y));

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			availablePieces[i + j * 2].setRadius(windowSize.y / 40);
			availablePieces[i + j * 2].setPosition(sf::Vector2f(left_available_pieces.getPosition().x + i * gameBoard.getSize().x / 6 + 10, left_available_pieces.getPosition().y + j * gameBoard.getSize().y / 6 + 10));

		}
	}

	// Update the webcam feed size and position according to the window size
	webcamSprite->setPosition(sf::Vector2f(windowSize.x / 2 - webcamSprite->getGlobalBounds().width / 2 - 10, webcamSprite->getGlobalBounds().width + 10));
	
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
	}

	window.draw(left_available_pieces);

	for (int i = 0; i < robot->getRemainingKing(); i++)
	{
		window.draw(availablePieces[7 - i]);
	}

	backButton.draw(window);
	restartButton.draw(window);
	refillButton.draw(window);
	frameDetailButton.draw(window);

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
}

StateMachine::State GameUI::handleEvent(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (backButton.mouseIsInsideButton(sf::Vector2f(float(event.mouseButton.x), float(event.mouseButton.y))))
		{
			std::cout << "Back button pressed" << std::endl;
			backButton.setButtonColor(sf::Color::Red);
			return StateMachine::State::MainMenu;
		}
		if (restartButton.mouseIsInsideButton(sf::Vector2f(float(event.mouseButton.x), float(event.mouseButton.y))))
		{
			std::cout << "Restart button pressed" << std::endl;
			restartButton.setButtonColor(sf::Color::Red);
			victoryVisible = false;
			restart = true;
		}
		if (refillButton.mouseIsInsideButton(sf::Vector2f(float(event.mouseButton.x), float(event.mouseButton.y))))
		{
			std::cout << "Refill button pressed" << std::endl;
			refillButton.setButtonColor(sf::Color::Red);
			robot->Refill();
		}
		if (frameDetailButton.mouseIsInsideButton(sf::Vector2f(float(event.mouseButton.x), float(event.mouseButton.y))))
		{
			std::cout << "Frame detail button pressed" << std::endl;
			backButton.setButtonColor(sf::Color::Red);
			//return StateMachine::State::FrameDetails;
		}
	}
	if (event.type == sf::Event::MouseMoved)
	{
		if (backButton.mouseIsInsideButton(sf::Vector2f(float(event.mouseMove.x), float(event.mouseMove.y))))
		{
			backButton.setButtonColor(sf::Color::Green);
		}
		else if (restartButton.mouseIsInsideButton(sf::Vector2f(float(event.mouseMove.x), float(event.mouseMove.y))))
		{
			restartButton.setButtonColor(sf::Color::Green);
		}
		else if (refillButton.mouseIsInsideButton(sf::Vector2f(float(event.mouseMove.x), float(event.mouseMove.y))))
		{
			refillButton.setButtonColor(sf::Color::Green);
		}
		else if (frameDetailButton.mouseIsInsideButton(sf::Vector2f(float(event.mouseMove.x), float(event.mouseMove.y))))
		{
			frameDetailButton.setButtonColor(sf::Color::Green);
		}
		else
		{
			backButton.setButtonColor(sf::Color::Red);
			restartButton.setButtonColor(sf::Color::Red);
			refillButton.setButtonColor(sf::Color::Red);
			frameDetailButton.setButtonColor(sf::Color::Red);
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
			int piece = board.getPiece(BOARDSIZE - j - 1, i);
			if (piece == 0)
				circlesPieces[j + i * BOARDSIZE].setFillColor(sf::Color::Transparent);
			else if (piece == 1)
				circlesPieces[j + i * BOARDSIZE].setFillColor(sf::Color::Green);
			else if (piece == 3)
				circlesPieces[j + i * BOARDSIZE].setFillColor(sf::Color::Blue);
			else if (piece == 2)
				circlesPieces[j + i * BOARDSIZE].setFillColor(sf::Color::White);
			else if (piece == 4)
				circlesPieces[j + i * BOARDSIZE].setFillColor(sf::Color::Red);
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
