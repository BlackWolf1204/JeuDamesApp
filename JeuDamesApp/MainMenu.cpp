#include "MainMenu.h"

MainMenu::MainMenu()
{
	portText = "";
}

MainMenu::MainMenu(sf::Font* font, Robot* robot)
{
	playButton.setDefaultButtonColor();
	playButton.setButtonSize(sf::Vector2f(250, 100));
	playButton.setButtonFont(font);
	playButton.setButtonText("Jouer");
	playButton.setButtonTextSize(70);


	frameDetailButton = Button();
	frameDetailButton.setDefaultButtonColor();
	frameDetailButton.setButtonSize(sf::Vector2f(370, 100));
	frameDetailButton.setButtonPosition(sf::Vector2f(250, 110 + playButton.getButtonSize().y));
	frameDetailButton.setButtonFont(font);
	frameDetailButton.setButtonText("Image Details");
	frameDetailButton.setButtonTextSize(70);

	rulesButton = Button();
	rulesButton.setDefaultButtonColor();
	rulesButton.setButtonSize(sf::Vector2f(250, 100));
	rulesButton.setButtonPosition(sf::Vector2f(250, 110 + playButton.getButtonSize().y));
	rulesButton.setButtonFont(font);
	rulesButton.setButtonText("Règles");
	rulesButton.setButtonTextSize(70);

	portInputBar = InputBar();
	portInputBar.setDefaultInputBarColor();
	portInputBar.setInputBarSize(sf::Vector2f(300, 80));
	portInputBar.setInputBarPosition(sf::Vector2f(10, 10));
	portInputBar.setInputBarFont(font);
	portInputBar.setInputBarTextSize(50);

	enterButton = Button();
	enterButton.setDefaultButtonColor();
	enterButton.setButtonSize(sf::Vector2f(130, 80));
	enterButton.setButtonPosition(sf::Vector2f(20 + portInputBar.getInputBarSize().x, 10));
	enterButton.setButtonFont(font);
	enterButton.setButtonText("Entrer");
	enterButton.setButtonTextSize(50);

	calibrationButton = Button();
	calibrationButton.setDefaultButtonColor();
	calibrationButton.setButtonSize(sf::Vector2f(300, 100));
	calibrationButton.setButtonFont(font);
	calibrationButton.setButtonText("Calibrage");
	calibrationButton.setButtonTextSize(70);

	this->robot = robot;
}

void MainMenu::updateButton(sf::Vector2u windowSize)
{
	frameDetailButton.setButtonPosition(sf::Vector2f(windowSize.x / 2 - frameDetailButton.getButtonSize().x / 2, windowSize.y / 2 - frameDetailButton.getButtonSize().y / 2 - playButton.getButtonSize().y / 2 - 10));
	playButton.setButtonPosition(sf::Vector2f((float)windowSize.x / 2 - playButton.getButtonSize().x - 10, (float)windowSize.y / 2 + 20));
	rulesButton.setButtonPosition(sf::Vector2f((float)windowSize.x / 2 + 10, (float)windowSize.y / 2 + 20));
	calibrationButton.setButtonPosition(sf::Vector2f(20, (float)windowSize.y - calibrationButton.getButtonSize().y - 20));
}

void MainMenu::draw(sf::RenderWindow& window)
{
	playButton.draw(window);
	frameDetailButton.draw(window);
	rulesButton.draw(window);
	enterButton.draw(window);
	portInputBar.draw(window);
	calibrationButton.draw(window);
}

StateMachine::State MainMenu::handleEvent(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (portInputBar.mouseIsInsideInputBar(sf::Vector2f(float(event.mouseButton.x), float(event.mouseButton.y))))
		{
			std::cout << "Port input bar selected" << std::endl;
			portInputBar.setIsWriting(true);
			portInputBar.setSelectedInputBarColor();
		}
		else
		{
			portInputBar.setIsWriting(false);
			portInputBar.setDefaultInputBarColor();
		}
		if (playButton.mouseIsInsideButton(sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y)))
		{
			std::cout << "Play button pressed" << std::endl;
			playButton.setDefaultButtonColor();
			return StateMachine::State::Game;
		}
		if (frameDetailButton.mouseIsInsideButton(sf::Vector2f(float(event.mouseButton.x), float(event.mouseButton.y))))
		{
			std::cout << "Frame detail button pressed" << std::endl;
			frameDetailButton.setDefaultButtonColor();
			return StateMachine::State::FrameDetail;
		}
		if (rulesButton.mouseIsInsideButton(sf::Vector2f(float(event.mouseButton.x), float(event.mouseButton.y))))
		{
			std::cout << "Rules description button pressed" << std::endl;
			rulesButton.setDefaultButtonColor();
			return StateMachine::State::Rules;
		}
		if (enterButton.mouseIsInsideButton(sf::Vector2f(float(event.mouseButton.x), float(event.mouseButton.y))))
		{
			std::cout << "Enter button pressed" << std::endl;
			enterButton.setDefaultButtonColor();
			portInputBar.setDefaultInputBarColor();
			portInputBar.setIsWriting(false);
			portText = portInputBar.getInputBarText();
			portInputBar.setInputBarText("");
		}
		if (calibrationButton.mouseIsInsideButton(sf::Vector2f(float(event.mouseButton.x), float(event.mouseButton.y))))
		{
			std::cout << "Calibration button pressed" << std::endl;
			calibrationButton.setDefaultButtonColor();
			if (robot != nullptr)
			{
				robot->Calibrate();
			}
		}
	}
	if (event.type == sf::Event::MouseMoved) {
		if (playButton.mouseIsInsideButton(sf::Vector2f((float)event.mouseMove.x, (float)event.mouseMove.y)))
		{
			playButton.setSelectedButtonColor();
			frameDetailButton.setDefaultButtonColor();
			rulesButton.setDefaultButtonColor();
			enterButton.setDefaultButtonColor();
			calibrationButton.setDefaultButtonColor();
		}
		else if (frameDetailButton.mouseIsInsideButton(sf::Vector2f(float(event.mouseMove.x), float(event.mouseMove.y))))
		{
			frameDetailButton.setSelectedButtonColor();
			playButton.setDefaultButtonColor();
			rulesButton.setDefaultButtonColor();
			enterButton.setDefaultButtonColor();
			calibrationButton.setDefaultButtonColor();
		}
		else if (rulesButton.mouseIsInsideButton(sf::Vector2f(float(event.mouseMove.x), float(event.mouseMove.y))))
		{
			rulesButton.setSelectedButtonColor();
			playButton.setDefaultButtonColor();
			frameDetailButton.setDefaultButtonColor();
			enterButton.setDefaultButtonColor();
			calibrationButton.setDefaultButtonColor();
		}
		else if (enterButton.mouseIsInsideButton(sf::Vector2f(float(event.mouseMove.x), float(event.mouseMove.y))))
		{
			enterButton.setSelectedButtonColor();
			rulesButton.setDefaultButtonColor();
			playButton.setDefaultButtonColor();
			frameDetailButton.setDefaultButtonColor();
			calibrationButton.setDefaultButtonColor();
		}
		else if (calibrationButton.mouseIsInsideButton(sf::Vector2f(float(event.mouseMove.x), float(event.mouseMove.y))))
		{
			calibrationButton.setSelectedButtonColor();
			rulesButton.setDefaultButtonColor();
			playButton.setDefaultButtonColor();
			frameDetailButton.setDefaultButtonColor();
			enterButton.setDefaultButtonColor();
		}
		else
		{
			playButton.setDefaultButtonColor();
			frameDetailButton.setDefaultButtonColor();
			rulesButton.setDefaultButtonColor();
			enterButton.setDefaultButtonColor();
			calibrationButton.setDefaultButtonColor();
		}
	}
	if (event.type == sf::Event::TextEntered && portInputBar.getIsWriting())
	{
		// Enter input
		if (event.text.unicode == 13)
		{
			std::cout << "Enter button pressed" << std::endl;
			portInputBar.setDefaultInputBarColor();
			portInputBar.setIsWriting(false);
			portText = portInputBar.getInputBarText();
			portInputBar.setInputBarText("");
		}
		portInputBar.handleKeyboardInput(event.text.unicode);
	}
	return StateMachine::State::MainMenu;
}
