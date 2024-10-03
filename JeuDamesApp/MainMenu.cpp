#include "MainMenu.h"

MainMenu::MainMenu()
{
}

MainMenu::MainMenu(sf::Font* font)
{
	playButton.setButtonColor(sf::Color::Red);
	playButton.setButtonSize(sf::Vector2f(250, 100));

	playButton.setButtonFont(font);
	playButton.setButtonText("Jouer");
	playButton.setButtonTextSize(80);
	playButton.setButtonTextColor(sf::Color::White);
}

void MainMenu::updateButton(sf::Vector2u windowSize)
{
	playButton.setButtonPosition(sf::Vector2f(windowSize.x / 2 - playButton.getButtonSize().x / 2, windowSize.y / 2 - playButton.getButtonSize().y / 2));
}

void MainMenu::draw(sf::RenderWindow& window)
{
	playButton.draw(window);
}

StateMachine::State MainMenu::handleEvent(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (playButton.mouseIsInsideButton(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
		{
			std::cout << "Play button pressed" << std::endl;
			playButton.setButtonColor(sf::Color::Red);
			return StateMachine::State::Game;
		}
	}
	if (event.type == sf::Event::MouseMoved) {
		if (playButton.mouseIsInsideButton(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
		{
			playButton.setButtonColor(sf::Color::Green);
		}
		else
		{
			playButton.setButtonColor(sf::Color::Red);
		}
	}
	return StateMachine::State::MainMenu;
}
