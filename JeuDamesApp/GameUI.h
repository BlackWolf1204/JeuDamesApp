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

static std::atomic<bool> webcamThreadRunning = true;

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
	/// <param name="font">The font to use for the texts.</param>
	GameUI(sf::Font* font, Robot* robot);

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

	std::thread* webcamThread = nullptr;

	
	sf::Image* webcamImage;
	sf::Texture* webcamTexture;
	sf::Sprite* webcamSprite;

	//grille de jeu
	sf::RectangleShape gameGrid;

	//cercles de la couleur des pièces dans la grille de jeu
	std::vector<sf::CircleShape> circlesPieces;

	//texte de chargement
	sf::Text loadingText;

	//texte de victoire
	sf::Text victoryText;
	bool victoryVisible = false;

	Button restartButton;
	Button refillButton;

	sf::RectangleShape left_available_pieces;
	sf::RectangleShape right_available_pieces;
	std::vector<sf::CircleShape> availablePieces;

	Robot* robot;
};

