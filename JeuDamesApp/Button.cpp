#include "Button.h"

Button::Button()
{
	buttonRect.setOutlineThickness(3);
	buttonRect.setOutlineColor(sf::Color::White);
}

sf::Vector2f Button::getButtonSize()
{
	return buttonSize;
}

void Button::setButtonColor(sf::Color color)
{
	buttonColor = color;
}

void Button::setButtonSize(sf::Vector2f size)
{
	buttonSize = size;
	buttonRect.setSize(buttonSize);
}

void Button::setButtonPosition(sf::Vector2f position)
{
	buttonPosition = position;
}

void Button::setButtonTextColor(sf::Color color)
{
	buttonText.setFillColor(color);
}

void Button::setButtonText(std::string text)
{
	buttonText.setString(text);
}

void Button::setButtonFont(sf::Font* font)
{
	buttonText.setFont(*font);
}

void Button::setButtonTextSize(int size)
{
	buttonText.setCharacterSize(size);
}

void Button::draw(sf::RenderWindow& window)
{
	sf::Vector2u windowSize = window.getSize();

	buttonRect.setPosition(buttonPosition);
	buttonRect.setFillColor(buttonColor);

	buttonText.setOrigin(buttonText.getLocalBounds().width / 2, buttonText.getLocalBounds().height / 2);
	buttonText.setPosition(buttonRect.getPosition().x + buttonRect.getSize().x / 2, buttonRect.getPosition().y + buttonRect.getSize().y / 2);

	window.draw(buttonRect);
	window.draw(buttonText);
}

bool Button::mouseIsInsideButton(sf::Vector2f mousePosition)
{
	if (buttonRect.getGlobalBounds().contains(mousePosition)) {
		return true;
	}
	return false;
}
