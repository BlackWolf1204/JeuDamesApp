#include "uiController.h"


uiController::uiController(sf::Vector2u windowSize, Robot* robot)
{	
	window.create(sf::VideoMode(windowSize.x, windowSize.y), "Jeu de Dames avec le robot !");
	window.setFramerateLimit(60);
	font = new sf::Font();
	if (!font->loadFromFile(fontPath)) {
		std::cerr << "Add the font file here :" << fontPath << std::endl;
	}
	mainMenu = new MainMenu(font);
	gameUI = new GameUI(font, robot);
}

StateMachine::State uiController::tick(StateMachine::State actualState)
{
	sf::Event event;
	while (window.pollEvent(event)) {

		if (event.type == sf::Event::Closed)
			window.close();
		if (event.type == sf::Event::Resized) {
			sf::Vector2f windowSize = window.getView().getSize();
			window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
		}
		if (actualState == StateMachine::State::MainMenu) {
			StateMachine::State newState = mainMenu->handleEvent(event);
			if (newState != StateMachine::State::MainMenu) {
				return newState;
			}
		}
		if (actualState == StateMachine::State::Game) {
			StateMachine::State newState = gameUI->handleEvent(event);
			if (newState != StateMachine::State::Game) {
				return newState;
			}
		}
	}

	window.clear();

	if (actualState == StateMachine::State::MainMenu) {
		mainMenu->updateButton(window.getSize());
		mainMenu->draw(window);
	}
	else if (actualState == StateMachine::State::Game) {
		gameUI->draw(window);
	}

	window.display();

	return actualState;
}

sf::RenderWindow& uiController::getWindow()
{
	return window;
}

void uiController::stop(StateMachine::State actualState)
{
	if (actualState == StateMachine::State::MainMenu) {
		mainMenu->~MainMenu();
	}
	else if (actualState == StateMachine::State::Game) {
		gameUI->~GameUI();
	}
}

GameUI* uiController::getGameUI()
{
	return gameUI;
}
