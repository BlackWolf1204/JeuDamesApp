#pragma once
#include <SFML/Graphics.hpp>

class InputBar
{
public:
	InputBar();

	/// <summary>
	/// Get the input bar size
	/// </summary>
	/// <returns></returns>
	sf::Vector2f getInputBarSize();

	/// <summary>
	/// Get the input bar text
	/// </summary>
	/// <returns></returns>
	sf::String getInputBarText();

	/// <summary>
	/// Set the input bar size
	/// </summary>
	/// <param name="size">Size vector containing the width and height of the input bar</param>
	void setInputBarSize(sf::Vector2f size);

	/// <summary>
	/// Set the input bar color
	/// </summary>
	void setDefaultInputBarColor();

	/// <summary>
	/// Set the input bar color
	/// </summary>
	void setSelectedInputBarColor();

	/// <summary>
	/// Set the input bar position
	/// </summary>
	/// <param name="position">Position vector containing the x and y position of the input bar</param>
	void setInputBarPosition(sf::Vector2f position);

	/// <summary>
	/// Set the input bar text
	/// </summary>
	/// <param name="text">String containing the text to be displayed on the input bar</param>
	void setInputBarText(std::string text);

	/// <summary>
	/// Set the input bar font
	/// </summary>
	/// <param name="font">Font of the text using a Font type from SFML library</param>
	void setInputBarFont(sf::Font* font);

	/// <summary>
	/// Set the input bar text size
	/// </summary>
	/// <param name="size">Size of the text</param>
	void setInputBarTextSize(int size);

	/// <summary>
	/// Get isWriting state (if the input bar is selected or not)
	/// </summary>
	/// <return>isWriting state</return>
	bool getIsWriting();

	/// <summary>
	/// Set isWriting state (if the input bar is selected or not)
	/// </summary>
	/// <param name="size">State of isWriting (input bar selected or not)</param>
	void setIsWriting(bool state);

	/// <summary>
	/// Draw the input bar on the screen
	/// </summary>
	/// <param name="window">Window to draw the input bar on</param>
	void draw(sf::RenderWindow& window);

	/// <summary>
	/// Check if the mouse is inside the input bar
	/// </summary>
	/// <param name="mousePosition">Position of the mouse</param>
	/// <returns>True if the mouse is inside the input bar, false otherwise</returns>
	bool mouseIsInsideInputBar(sf::Vector2f mousePosition);

	/// <summary>
	/// Handle the keyboard input
	/// </summary>
	/// <param name="keyboarInput">Unicode of the keyboard input</param>
	void handleKeyboardInput(uint32_t keyboardInput);

private:
	sf::RectangleShape inputBarRect;
	sf::Color inputBarColor;
	sf::Text inputBarText;
	sf::Vector2f inputBarSize;
	sf::Color inputBarTextColor;
	sf::Vector2f inputBarPosition;
	bool isWriting;
};

