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

GameUI::GameUI(sf::Font* font, Robot* robot)
{
	backButton = Button();
	backButton.setButtonColor(sf::Color::Red);
	backButton.setButtonSize(sf::Vector2f(250, 100));
	backButton.setButtonPosition(sf::Vector2f(10, 10));
	backButton.setButtonFont(font);
	backButton.setButtonTextColor(sf::Color::White);
	backButton.setButtonText("Retour");
	backButton.setButtonTextSize(80);

	gameGrid.setFillColor(sf::Color::Blue);

	webcamImage = new sf::Image();
	webcamTexture = new sf::Texture();
	webcamSprite = new sf::Sprite();
	webcamSprite->setScale(0.7, 0.7);

	for (int i = 0; i < 42; i++)
	{
		sf::CircleShape circle;
		circle.setFillColor(sf::Color::White);
		circlesPieces.push_back(circle);
	}

	loadingText.setFont(*font);
	loadingText.setString("Chargement de la camera, \nVeuillez patienter...");
	loadingText.setCharacterSize(30);
	loadingText.setFillColor(sf::Color::White);

	victoryText.setFont(*font);
	victoryText.setCharacterSize(80);
	victoryText.setFillColor(sf::Color::White);

	restartButton = Button();
	restartButton.setButtonColor(sf::Color::Red);
	restartButton.setButtonSize(sf::Vector2f(250, 100));
	restartButton.setButtonPosition(sf::Vector2f(10, 130));
	restartButton.setButtonFont(font);
	restartButton.setButtonTextColor(sf::Color::White);
	restartButton.setButtonText("Rejouer");
	restartButton.setButtonTextSize(78);

	refillButton = Button();
	refillButton.setButtonColor(sf::Color::Red);
	refillButton.setButtonSize(sf::Vector2f(250, 100));
	refillButton.setButtonPosition(sf::Vector2f(10, 250));
	refillButton.setButtonFont(font);
	refillButton.setButtonTextColor(sf::Color::White);
	refillButton.setButtonText("Recharger");
	refillButton.setButtonTextSize(62);

	left_available_pieces.setFillColor(sf::Color(150, 150, 150));
	
	right_available_pieces.setFillColor(sf::Color(150, 150, 150));

	for (int i = 0; i < 8; i++)
	{
		sf::CircleShape circle;
		circle.setFillColor(sf::Color::Yellow);
		availablePieces.push_back(circle);
	}

	this->robot = robot;
}

void GameUI::draw(sf::RenderWindow& window)
{
	sf::Vector2u windowSize = window.getSize();

	// Update the gride size and position according to the window size
	gameGrid.setSize(sf::Vector2f(windowSize.y * 0.5 * 7 / 6, windowSize.y * 0.5));
	gameGrid.setPosition(sf::Vector2f(windowSize.x / 2 - gameGrid.getSize().x / 2, windowSize.y - gameGrid.getSize().y));

	// Update the circles size and position according to the game grid size and position
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			circlesPieces[i + j * 7].setPosition(sf::Vector2f(gameGrid.getPosition().x + i * gameGrid.getSize().x / 7 + 10, gameGrid.getPosition().y + j * gameGrid.getSize().y / 6 + 10));
			circlesPieces[i + j * 7].setRadius(windowSize.y / 30);
		}
	}

	// Update the available pieces size and position according to the window size
	left_available_pieces.setSize(sf::Vector2f(windowSize.x / 20, windowSize.y / 3));
	left_available_pieces.setPosition(sf::Vector2f(windowSize.x / 2 - gameGrid.getSize().x / 2 - 10 - left_available_pieces.getSize().x, gameGrid.getPosition().y));

	right_available_pieces.setSize(sf::Vector2f(windowSize.x / 20, windowSize.y / 3));
	right_available_pieces.setPosition(sf::Vector2f(windowSize.x / 2 + gameGrid.getSize().x / 2 + 10, gameGrid.getPosition().y));

	for (int i = 0; i < 4; i++)
	{
		availablePieces[i].setRadius(windowSize.y / 30);
		availablePieces[i].setPosition(sf::Vector2f(left_available_pieces.getPosition().x + availablePieces[i].getRadius() / 2 , left_available_pieces.getPosition().y + i * gameGrid.getSize().y / 6 + 10));
	}

	for (int i = 4; i < 8; i++)
	{
		availablePieces[i].setRadius(windowSize.y / 30);
		availablePieces[i].setPosition(sf::Vector2f(right_available_pieces.getPosition().x + availablePieces[i].getRadius() / 2, right_available_pieces.getPosition().y + (i - 4) * gameGrid.getSize().y / 6 + 10));
	}
	
	// Update the webcam feed size and position according to the window size
	webcamSprite->setPosition(sf::Vector2f(windowSize.x / 2 - webcamSprite->getGlobalBounds().width / 2 - 10, 10));
	
	// Update the loading text size and position according to the window size
	loadingText.setPosition(sf::Vector2f(windowSize.x / 2 - loadingText.getGlobalBounds().width / 2, 100));

	
	window.draw(loadingText);
	window.draw(*webcamSprite);

	window.draw(gameGrid);
	for (int i = 0; i < 42; i++)
	{
		window.draw(circlesPieces[i]);
	}

	window.draw(left_available_pieces);
	window.draw(right_available_pieces);

	for (int i = 0; i < robot->getRemainingKing(); i++)
	{
		window.draw(availablePieces[7 - i]);
	}

	backButton.draw(window);
	restartButton.draw(window);
	refillButton.draw(window);

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
	sf::Uint8* pixels = new sf::Uint8[4 * frameWidth * frameHeight];
	for (int i = 0; i < frameWidth; i++)
	{
		for (int j = 0; j < frameHeight; j++)
		{
			cv::Vec3b color = frame.at<cv::Vec3b>(j, i);
			pixels[(i + j * frameWidth) * 4] = color[2];
			pixels[(i + j * frameWidth) * 4 + 1] = color[1];
			pixels[(i + j * frameWidth) * 4 + 2] = color[0];
			pixels[(i + j * frameWidth) * 4 + 3] = 255;
		}
	}
	webcamImage->create(frameWidth, frameHeight, pixels);
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
		else
		{
			backButton.setButtonColor(sf::Color::Red);
			restartButton.setButtonColor(sf::Color::Red);
			refillButton.setButtonColor(sf::Color::Red);
		}
	}
	return StateMachine::State::Game;
}

void GameUI::updateBoard(sf::RenderWindow& window, Board board)
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			int piece = board.getPiece(i, 5 - j);
			if (piece == 0)
			{
				circlesPieces[i + j * 7].setFillColor(sf::Color::White);
			}
			else if (piece == 1)
			{
				circlesPieces[i + j * 7].setFillColor(sf::Color::Red);
			}
			else if (piece == 2)
			{
				circlesPieces[i + j * 7].setFillColor(sf::Color::Yellow);
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
