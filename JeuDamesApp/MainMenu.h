#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.h"
#include "StateMachine.h"

/// <summary>
/// This class is responsible for the main menu of the game.
/// </summary>
class MainMenu {
public:
	MainMenu();
	MainMenu(sf::Font* font);
	void updateButton(sf::Vector2u windowSize);
	void draw(sf::RenderWindow& window);
	StateMachine::State handleEvent(sf::Event event);

private:
	Button playButton;
};
