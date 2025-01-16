#pragma once
#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "StateMachine.h"
#include <iostream>
#include "GameUI.h"
#include "FrameDetail.h"
#include "Rules.h"

/// <summary>
/// This class is the controller of the UI, it will manage the window and the different states of the game (main menu, game, etc)
/// </summary>
class uiController {
public:
	uiController(sf::Vector2u windowSize, Robot* robot);
	StateMachine::State tick(StateMachine::State actualState);
	sf::RenderWindow& getWindow();
	sf::Font* font;
	void stop(StateMachine::State actualState);
	MainMenu* getMainMenu();
	GameUI* getGameUI();
	FrameDetail* getFrameDetail();

private:
	sf::RenderWindow window;
	std::string fontPath = "Ressources/Winter Snowman.otf";
	MainMenu* mainMenu;
	GameUI* gameUI;
	FrameDetail* frameDetail;
	Rules* rules;
};