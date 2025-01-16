#include "Button.h"

Button::Button()
{
	buttonRect.setOutlineThickness(3);
	buttonColor = sf::Color(3, 10, 140);
	buttonRect.setOutlineColor(sf::Color(242, 229, 48));
	buttonText.setFillColor(sf::Color(242, 229, 48));
}

sf::Vector2f Button::getButtonSize()
{
	return buttonSize;
}

void Button::setDefaultButtonColor()
{
	buttonColor = sf::Color(3, 10, 140);
}
void Button::setSelectedButtonColor()
{
	buttonColor = sf::Color(154, 187, 242);
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

	buttonText.setOrigin(buttonText.getLocalBounds().width / 2, buttonText.getLocalBounds().height);
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
