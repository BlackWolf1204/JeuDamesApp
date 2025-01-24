#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <opencv2/opencv.hpp>
#include "Button.h"
#include "StateMachine.h"
#include "Camera.h"
#include "Board.h"
#include "Robot.h"

static std::atomic<bool> webcamThreadRunningGame = true;

/// <summary>
/// This class is responsible for the game UI. it will display the webcam feed and the game grid.
/// </summary>
class GameUI
{
public:
	GameUI();

	/// <summary>
	/// Terminate the webcam thread and free the memory.
	/// </summary>
	~GameUI();

	/// <summary>
	/// Initialize the game UI with the given font.
	/// </summary>
	/// <param name="window">The window where is the GameUI.</param>
	/// <param name="font">The font to use for the texts.</param>
	/// <para name="robot">The robot playing</param>
	GameUI(sf::RenderWindow& window, sf::Font* font, Robot* robot);

	/// <summary>
	/// Draw the game UI and all his components on the given window.
	/// </summary>
	/// <param name="window">The window to draw the game UI on.</param>
	void draw(sf::RenderWindow& window);

	/// <summary>
	/// Get the camera frame and update the webcam feed.
	/// </summary>
	/// <param name="frame">The camera frame to update the webcam feed with.</param>
	void getCameraFrame(cv::Mat frame);

	/// <summary>
	/// Handle the given event (Mopuse click, Mouse move, ...)
	/// </summary>
	/// <param name="event">The event to handle.</param>
	StateMachine::State handleEvent(sf::Event event);

	void updateBoard(sf::RenderWindow& window, Board board);
	void playerVictory(sf::RenderWindow& window);
	void playerDefeat(sf::RenderWindow& window);

	bool restart = false;

private:
	Button backButton;
	Button restartButton;
	Button refillButton;
	Button playButton;

	std::thread* webcamThread = nullptr;

	
	sf::Image* webcamImage;
	sf::Texture* webcamTexture;
	sf::Sprite* webcamSprite;

	// game board
	sf::RectangleShape gameBoard;

	// squares of the board
	std::vector<sf::RectangleShape> gameSquares;

	// circles of the pieces color in the board
	std::vector<sf::CircleShape> circlesPieces;

	// marks of the king on the piece of the board
	std::vector<sf::Text> kingMarks;

	// marks of the available king
	std::vector<sf::Text> availableKingMarks;

	// charging text
	sf::Text loadingText;

	// victory text
	sf::Text victoryText;
	bool victoryVisible = false;

	sf::RectangleShape left_available_pieces;
	std::vector<sf::CircleShape> availablePieces;

	Robot* robot;
};

