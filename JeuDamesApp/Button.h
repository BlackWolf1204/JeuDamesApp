#pragma once
#include <SFML/Graphics.hpp>

class Button
{
public:
	Button();

	/// <summary>
	/// Get the button size
	/// </summary>
	/// <returns></returns>
	sf::Vector2f getButtonSize();

	/// <summary>
	/// Set the button color
	/// </summary>
	/// <param name="color">Color of the button using a Color type from SFML library</param>
	void setButtonColor(sf::Color color);

	/// <summary>
	/// Set the button size
	/// </summary>
	/// <param name="size">Size vector containing the width and height of the button</param>
	void setButtonSize(sf::Vector2f size);

	/// <summary>
	/// Set the button position
	/// </summary>
	/// <param name="position">Position vector containing the x and y position of the button</param>
	void setButtonPosition(sf::Vector2f position);

	/// <summary>
	/// Set the button text color
	/// </summary>
	/// <param name="color">Color of the text using a Color type from SFML library</param>
	void setButtonTextColor(sf::Color color);

	/// <summary>
	/// Set the button text
	/// </summary>
	/// <param name="text">String containing the text to be displayed on the button</param>
	void setButtonText(std::string text);

	/// <summary>
	/// Set the button font
	/// </summary>
	/// <param name="font">Font of the text using a Font type from SFML library</param>
	void setButtonFont(sf::Font* font);

	/// <summary>
	/// Set the button text size
	/// </summary>
	/// <param name="size">Size of the text</param>
	void setButtonTextSize(int size);

	/// <summary>
	/// Draw the button on the screen
	/// </summary>
	/// <param name="window">Window to draw the button on</param>
	void draw(sf::RenderWindow& window);

	/// <summary>
	/// Check if the mouse is inside the button
	/// </summary>
	/// <param name="mousePosition">Position of the mouse</param>
	/// <returns>True if the mouse is inside the button, false otherwise</returns>
	bool mouseIsInsideButton(sf::Vector2f mousePosition);

private:
	sf::RectangleShape buttonRect;
	sf::Color buttonColor;
	sf::Text buttonText;
	sf::Vector2f buttonSize;
	sf::Color buttonTextColor;
	sf::Vector2f buttonPosition;
};

