#include "uiController.h"


uiController::uiController(sf::Vector2u windowSize, Robot* robot)
{	
	window.create(sf::VideoMode(windowSize.x, windowSize.y), "Jeu de Dames avec le robot !");
	window.setFramerateLimit(60);
	font = new sf::Font();
	if (!font->loadFromFile(fontPath)) {
		std::cerr << "Add the font file here :" << fontPath << std::endl;
	}
	mainMenu = new MainMenu(font, robot);
	gameUI = new GameUI(window, font, robot);
	frameDetail = new FrameDetail(window, font);
	rules = new Rules(window, font);
}

StateMachine::State uiController::tick(StateMachine::State actualState)
{
	sf::Event event;
	while (window.pollEvent(event)) {

		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		if (event.type == sf::Event::Resized) {
			sf::Vector2f windowSize = window.getView().getSize();
			window.setView(sf::View(sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height)));
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
		if (actualState == StateMachine::State::FrameDetail) {
			frameDetail->setDisplayed(true);
			StateMachine::State newState = frameDetail->handleEvent(event);
			if (newState != StateMachine::State::FrameDetail) {
				frameDetail->setDisplayed(false);
				return newState;
			}
		}
		if (actualState == StateMachine::State::Rules) {
			StateMachine::State newState = rules->handleEvent(event);
			if (newState != StateMachine::State::Rules) {
				return newState;
			}
		}
	}

	window.clear(sf::Color(80, 86, 191));

	if (actualState == StateMachine::State::MainMenu) {
		mainMenu->updateButton(window.getSize());
		mainMenu->draw(window);
	}
	else if (actualState == StateMachine::State::Game) {
		gameUI->draw(window);
	}
	else if (actualState == StateMachine::State::FrameDetail) {
		frameDetail->draw(window);
	}
	else if (actualState == StateMachine::State::Rules) {
		rules->draw(window);
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
	else if (actualState == StateMachine::State::FrameDetail) {
		frameDetail->~FrameDetail();
	}
}

MainMenu* uiController::getMainMenu()
{
	return mainMenu;
}


GameUI* uiController::getGameUI()
{
	return gameUI;
}

FrameDetail* uiController::getFrameDetail()
{
	return frameDetail;
}
