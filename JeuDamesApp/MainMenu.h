#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.h"
#include "InputBar.h"
#include "StateMachine.h"
#include "Robot.h"

/// <summary>
/// This class is responsible for the main menu of the game.
/// </summary>
class MainMenu {
public:
	MainMenu();
	MainMenu(sf::Font* font, Robot* robot);
	void updateButton(sf::Vector2u windowSize);
	void draw(sf::RenderWindow& window);
	StateMachine::State handleEvent(sf::Event event);

	std::string portText;

private:
	Button playButton;
	Button frameDetailButton;
	Button rulesButton;
	Button enterButton;
	Button calibrationButton;
	
	InputBar portInputBar;

	Robot* robot;
};
