#pragma once

#include <vector>
#include <opencv2/opencv.hpp>
#include "Board.h"

class BoardDetector {

public:
	enum class Color
	{
		GREEN,		// player's piece
		BLUE,		// player's king
		WHITE,		// robot's piece
		RED			// robot's king
	};

	static Board detectBoard(cv::Mat image);

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
	static std::vector<cv::Vec3f> detectCircles(cv::Mat frame, std::vector<std::vector<cv::Point>> contours);

	/// <summary>
	/// Sort the circles in the correct squares of the board
	/// The squares are ordered like this :
	/// 
	///         ROBOT
	///  7  6  5  4  3  2  1  0
	/// 15 14 13 12 11 10  9  8
	/// 23 22 21 20 19 18 17 16
	/// 31 30 29 28 27 26 25 24
	/// 39 38 37 36 35 34 33 32
	/// 47 46 45 44 43 42 41 40
	/// 55 54 53 52 51 50 49 48
	/// 63 62 61 60 59 58 57 56
	///         PLAYER
	/// 
	/// </summary>
	/// <param name="boardCircles">Vector containing the circles from the board</param>
	/// <param name="boardSquares">Vector containing the squares from the board</param>
	/// <returns>A vector containing the position of the circles and the square id which contain them</returns>
	static std::vector<cv::Vec4f> containCircles(std::vector<cv::Vec3f> boardCircles, std::vector<cv::Vec3f> boardSquares);

	/// <summary>
	/// Detect the color inside the circle acording to the image
	/// </summary>
	/// <param name="image">Source image containing the board</param>
	/// <param name="containedCircles">Vector containing the position of the circles and the squares id which contain them</param>
	/// <returns>A board object describing the status of the game</returns>
	static Board detectColors(cv::Mat image, std::vector<cv::Vec4f> containedCircles);

	/// <summary>
	/// Get the color of the circle
	/// </summary>
	/// <param name="image">Image containing the circle</param>
	/// <param name="circle">Coordinates of the circle (x, y, radius)</param>
	/// <returns>RGB color inside the circle</returns>
	static cv::Vec3b getCircleMeanColor(cv::Mat image, cv::Vec4f circle);

	/// <summary>
	/// Get the color enum element corresponding to the given RGB color
	/// </summary>
	/// <param name="color">RGB color</param>
	/// <returns>Color enum element</returns>
	static Color getColor(cv::Vec3b color);

};