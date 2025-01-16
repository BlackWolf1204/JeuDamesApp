#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <opencv2/opencv.hpp>
#include "Button.h"
#include "StateMachine.h"

/// <summary>
/// This class is responsible for the rules description. It will describre the different rules of this checkers version.
/// </summary>
class Rules
{
public:
	/// <summary>
	/// Initialize the rules description with the given font.
	/// </summary>
	/// <param name="window">The window where is the FrameDetail.</param>
	/// <param name="font">The font to use for the texts.</param>
	Rules(sf::RenderWindow& window, sf::Font* font);

	/// <summary>
	/// Draw the rules description and all his components on the given window.
	/// </summary>
	/// <param name="window">The window to draw the game UI on.</param>
	void draw(sf::RenderWindow& window);

	/// <summary>
	/// Handle the given event (Mopuse click, Mouse move, ...)
	/// </summary>
	/// <param name="event">The event to handle.</param>
	StateMachine::State handleEvent(sf::Event event);

private:
	Button backButton;

	// Description text
	sf::Text versionText;
	sf::Text rulesText;
};

