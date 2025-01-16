#include "InputBar.h"

InputBar::InputBar()
{
	inputBarRect.setOutlineThickness(4);
	inputBarRect.setOutlineColor(sf::Color::Transparent);
	inputBarColor = sf::Color(sf::Color(188, 187, 242));
	inputBarText.setFillColor(sf::Color::Black);
	isWriting = false;
}

sf::Vector2f InputBar::getInputBarSize()
{
	return inputBarSize;
}

sf::String InputBar::getInputBarText()
{
	return inputBarText.getString();
}

void InputBar::setInputBarSize(sf::Vector2f size)
{
	inputBarSize = size;
	inputBarRect.setSize(inputBarSize);
}

void InputBar::setDefaultInputBarColor()
{
	inputBarRect.setOutlineColor(sf::Color::Transparent);
}
void InputBar::setSelectedInputBarColor()
{
	inputBarRect.setOutlineColor(sf::Color(242, 242, 242));
}

void InputBar::setInputBarPosition(sf::Vector2f position)
{
	inputBarPosition = position;
}

void InputBar::setInputBarText(std::string text)
{
	inputBarText.setString(text);
}

void InputBar::setInputBarFont(sf::Font* font)
{
	inputBarText.setFont(*font);
}

void InputBar::setInputBarTextSize(int size)
{
	inputBarText.setCharacterSize(size);
}

bool InputBar::getIsWriting()
{
	return isWriting;
}

void InputBar::setIsWriting(bool state)
{
	isWriting = state;
}

void InputBar::draw(sf::RenderWindow& window)
{
	sf::Vector2u windowSize = window.getSize();

	inputBarRect.setPosition(inputBarPosition);
	inputBarRect.setFillColor(inputBarColor);

	inputBarText.setOrigin(inputBarText.getLocalBounds().width / 2, inputBarText.getLocalBounds().height);
	inputBarText.setPosition(inputBarRect.getPosition().x + inputBarRect.getSize().x / 2, inputBarRect.getPosition().y + inputBarRect.getSize().y / 2);

	window.draw(inputBarRect);
	window.draw(inputBarText);
}

bool InputBar::mouseIsInsideInputBar(sf::Vector2f mousePosition)
{
	if (inputBarRect.getGlobalBounds().contains(mousePosition)) {
		return true;
	}
	return false;
}

void InputBar::handleKeyboardInput(uint32_t keyboardInput)
{
	// Delete input
	if (keyboardInput == 8 && inputBarText.getString() != "")
		setInputBarText(inputBarText.getString().substring(0, inputBarText.getString().getSize() - 1));
	// Escape input
	if (keyboardInput == 27)
		setIsWriting(false);
	// Digit input
	if (keyboardInput >= 48 && keyboardInput <= 57 && inputBarText.getString().getSize() < 10)
		setInputBarText(inputBarText.getString() + (char)keyboardInput);
	// Uppercase letter input
	if (keyboardInput >= 65 && keyboardInput <= 90 && inputBarText.getString().getSize() < 10)
		setInputBarText(inputBarText.getString() + (char)keyboardInput);
	// lowercase letter input
	if (keyboardInput >= 97 && keyboardInput <= 122 && inputBarText.getString().getSize() < 10)
		setInputBarText(inputBarText.getString() + (char)(keyboardInput - 32));
}