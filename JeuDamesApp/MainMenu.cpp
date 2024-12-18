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
	playButton.setButtonTextSize(60);
	playButton.setButtonTextColor(sf::Color::White);


	frameDetailButton = Button();
	frameDetailButton.setButtonColor(sf::Color::Red);
	frameDetailButton.setButtonSize(sf::Vector2f(370, 100));
	frameDetailButton.setButtonPosition(sf::Vector2f(250, 110 + playButton.getButtonSize().y));
	frameDetailButton.setButtonFont(font);
	frameDetailButton.setButtonTextColor(sf::Color::White);
	frameDetailButton.setButtonText("Image Details");
	frameDetailButton.setButtonTextSize(60);
}

void MainMenu::updateButton(sf::Vector2u windowSize)
{
	playButton.setButtonPosition(sf::Vector2f(windowSize.x / 2 - playButton.getButtonSize().x / 2, windowSize.y / 2 - playButton.getButtonSize().y / 2 - frameDetailButton.getButtonSize().y / 2 - 10));
	frameDetailButton.setButtonPosition(sf::Vector2f((float)windowSize.x / 2 - frameDetailButton.getButtonSize().x / 2, (float)windowSize.y / 2 + 20));
}

void MainMenu::draw(sf::RenderWindow& window)
{
	playButton.draw(window);
	frameDetailButton.draw(window);
}

StateMachine::State MainMenu::handleEvent(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (playButton.mouseIsInsideButton(sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y)))
		{
			std::cout << "Play button pressed" << std::endl;
			playButton.setButtonColor(sf::Color::Red);
			return StateMachine::State::Game;
		}
		if (frameDetailButton.mouseIsInsideButton(sf::Vector2f(float(event.mouseButton.x), float(event.mouseButton.y))))
		{
			std::cout << "Frame detail button pressed" << std::endl;
			frameDetailButton.setButtonColor(sf::Color::Red);
			return StateMachine::State::FrameDetail;
		}
	}
	if (event.type == sf::Event::MouseMoved) {
		if (playButton.mouseIsInsideButton(sf::Vector2f((float)event.mouseMove.x, (float)event.mouseMove.y)))
		{
			playButton.setButtonColor(sf::Color::Green);
			frameDetailButton.setButtonColor(sf::Color::Red);
		}
		else if (frameDetailButton.mouseIsInsideButton(sf::Vector2f(float(event.mouseMove.x), float(event.mouseMove.y))))
		{
			frameDetailButton.setButtonColor(sf::Color::Green);
			playButton.setButtonColor(sf::Color::Red);
		}
		else
		{
			playButton.setButtonColor(sf::Color::Red);
			frameDetailButton.setButtonColor(sf::Color::Red);
		}
	}
	return StateMachine::State::MainMenu;
}
