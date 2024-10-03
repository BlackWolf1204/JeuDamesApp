#pragma once

#include <vector>
#include <opencv2/opencv.hpp>
#include "Board.h"

class BoardDetector {

public:
	enum class Color
	{
		RED,
		YELLOW,
		EMPTY
	};

	static Board detectBoard(cv::Mat image, Color playerColor);

private:

	// <summary>
	// Modify a given image using gaussian filter and Canny algorithm
	// </summary>
	// <param name="frame">Source image containing the board</param>
	static void modifyFrame(cv::Mat& frame);

	// <summary>
	// Search contours in a given image using gaussian filter and Canny algorithm
	// </summary>
	// <param name="frame">Source image containing the board</param>
	// <returns>A vector containing all the shapes found (vector containing the points of the shape)</returns>
	static std::vector<std::vector<cv::Point>> getShapeContours(cv::Mat& frame);

	/// <summary>
	/// Search for circles in a list of contours (shapes)
	/// </summary>
	// <param name="frame">Modified image containing the board</param>
	/// <returns>A vector containing all the circles detected in the image</returns>
	static std::vector<cv::Vec3f> detectCircles(cv::Mat& frame);

	/// <summary>
	/// Search for squares in a list of contours (shapes)
	/// </summary>
	/// <param name="frame">Source image</param>
	/// <param name="contours">Vector containing the contours</param>
	/// <returns>A vector containing all the squares (represented in circles) detected in the image</returns>
	static std::vector<cv::Vec3f> detectSquares(cv::Mat frame, std::vector<std::vector<cv::Point>> contours);


	/// <summary>
	/// Because the player start, the first played piece is searched
	/// </summary>
	/// <param name="image">Source image containing the board</param>
	/// <param name="circles">Vector containing all the circles detected in the image</param>
	/// <param name="playerColor">Color of the player</param>
	/// <returns>A vector containing the coordinate of the circle and its radius</returns>
	static cv::Vec3f searchFirstCircle(cv::Mat image, std::vector<cv::Vec3f> circles, Color playerColor);

	/// <summary>
	/// Filter the circles to only keep the one from the real board using their position
	/// </summary>
	/// <param name="image">Source image containing the board</param>
	/// <param name="circles">Vector containing all the circles detected in the image</param>
	/// <param name="firstCircle">Coordinates of the first circle played by the player</param>
	/// <returns>A vector containing the 42 coordinate of the circle from the board</returns>
	static std::vector<cv::Vec3f> filterCircles(cv::Mat image, std::vector<cv::Vec3f> circles, cv::Vec3f firstCircle);

	/// <summary>
	/// Sort the circles in the correct squares of the board
	/// </summary>
	/// <param name="boardCircles">Vector containing the circles from the board</param>
	/// <returns>A vector containing the squares id which contain the circles </returns>
	static std::vector<int> sortCircles(std::vector<cv::Vec3f> boardCircles);

	/// <summary>
	/// Create squares and sort from the corners board in the correct order :
	/// 
	/// 0  8 16 24 32 40 48 56
	/// 1  9 17 25 33 41 49 57
	/// 2 10 18 26 34 42 50 58
	/// 3 11 19 27 35 43 51 59
	/// 4 12 20 28 36 44 52 60
	/// 5 13 21 29 37 45 53 61
	/// 6 14 22 30 38 46 54 62
	/// 7 15 23 31 39 47 55 63
	/// 
	/// </summary>
	/// <param name="squares">Vector containing the squares from the board</param>
	/// <returns>A vector containing the squares from the board in the correct order</returns>
	static std::vector<cv::Vec3f> sortSquares(std::vector<cv::Vec3f> squares);

	/// <summary>
	/// Detect the color inside the circle acording to the image
	/// </summary>
	/// <param name="image">Source image containing the board</param>
	/// <param name="boardCircles">Vector containing the circles from the board and in a correct order</param>
	/// <returns>A board object describing the status of the game</returns>
	static Board detectColors(cv::Mat image, std::vector<cv::Vec3f> boardCircles);

	/// <summary>
	/// Get the color of the circle
	/// </summary>
	/// <param name="image">Image containing the circle</param>
	/// <param name="circle">Coordinates of the circle (x, y, radius)</param>
	/// <returns>RGB color inside the circle</returns>
	static cv::Vec3b getCircleMeanColor(cv::Mat image, cv::Vec3f circle);

	/// <summary>
	/// Get the color enum element corresponding to the given RGB color
	/// </summary>
	/// <param name="color">RGB color</param>
	/// <returns>Color enum element</returns>
	static Color getColor(cv::Vec3b color);

	static std::vector<cv::Vec3f> workingCircles;

	static std::vector<cv::Vec3f> addAndRemoveDuplicatesCircle(std::vector<cv::Vec3f> newCircles, std::vector<cv::Vec3f> previousCircles);

	static std::vector<cv::Vec3f> addAndRemoveDuplicatesSquare(std::vector<cv::Vec3f> newSquares, std::vector<cv::Vec3f> previousSquares);
};