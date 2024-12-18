#include "BoardDetector.h"


Board BoardDetector::detectBoard(cv::Mat image)
{
	// copy of the image to draw on and keep a clean image for the detection
	cv::Mat copy = image.clone();
	cv::Mat copy2 = image.clone();
	// modify the image to see only the contours
	modifyFrame(copy);

	// Square positions on the image
	cv::Point p1(510, 460);
	cv::Point p2(100, 30);
	float gap = (p2.x - p1.x) / BOARDSIZE;
	std::vector<cv::Vec3f> sortedSquares;

	for (int i = 0; i < BOARDSIZE; i++)
	{
		for (int j = 0; j < BOARDSIZE; j++)
		{
			cv::Vec3f square(p1.x + gap * i, p1.y + gap * j, gap);
			sortedSquares.push_back(square);
			// Uncomment to show the squares positions on the camera
			//cv::rectangle(image, cv::Point(square[0], square[1]), cv::Point(square[0] + square[2], square[1] + square[2]), cv::Scalar(255, 0, 255), 2);
		}
	}

	//Detect the circles in the image
	std::vector<std::vector<cv::Point>> contours = getShapeContours(copy);
	std::vector<cv::Vec3f> circles = detectCircles(image, contours);
	if (circles.size() == 0)
	{
		std::cout << "No circles detected" << std::endl;
		return Board();
	}
	std::vector<cv::Vec4f> containedCircles = containCircles(circles, sortedSquares);
	if (containedCircles.size() == 0)
	{
		std::cout << "Not contained" << std::endl;
		return Board();
	}
	for (int i = 0; i < containedCircles.size(); i++)
	{
		cv::circle(image, cv::Point(containedCircles[i][0], containedCircles[i][1]), containedCircles[i][2], cv::Scalar(0, 255, 255), 2);
	}
	
	//Detect the colors of the circles
	Board board = detectColors(copy2, containedCircles);
	
	return board;
}

std::vector<cv::Mat> BoardDetector::modifyFrame(cv::Mat& frame)
{
	std::vector<cv::Mat> modifiedFrame;
	if (frame.empty())
	{
		return modifiedFrame;
	}
	cv::Mat img_squares = frame.clone();

	// Declaring few Mat object for further operations
	cv::Mat img_gray, color_gray, img_gaus_blur, color_gaus_blur, img_canny, color_canny;

	// Square positions on the image
	cv::Point p1(510, 460);
	cv::Point p2(100, 30);
	float gap = (p2.x - p1.x) / BOARDSIZE;

	for (int i = 0; i < BOARDSIZE; i++)
	{
		for (int j = 0; j < BOARDSIZE; j++)
		{
			cv::Vec3f square(p1.x + gap * i, p1.y + gap * j, gap);
			cv::rectangle(img_squares, cv::Point(square[0], square[1]), cv::Point(square[0] + square[2], square[1] + square[2]), cv::Scalar(255, 0, 255), 2);
		}
	}
	modifiedFrame.push_back(img_squares);

	// Convert img color to gray. Output image is second arg
	cv::cvtColor(frame, img_gray, cv::COLOR_BGR2GRAY);
	cv::cvtColor(img_gray, color_gray, cv::COLOR_GRAY2BGR);
	modifiedFrame.push_back(color_gray);

	// Blurring image using gaussian fliter. Size(3,3) is SE kernal (erase noise)
	cv::GaussianBlur(img_gray, img_gaus_blur, cv::Size(3, 3), 3, 0);
	cv::cvtColor(img_gaus_blur, color_gaus_blur, cv::COLOR_GRAY2BGR);
	modifiedFrame.push_back(color_gaus_blur);

	// Edge detection using canny algo
	cv::Canny(img_gaus_blur, img_canny, 25, 110);
	
	// Running dilation on canny output to improve edge thickness
	cv::Mat se1 = getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
	cv::dilate(img_canny, frame, se1);
	cv::cvtColor(frame, color_canny, cv::COLOR_GRAY2BGR);
	modifiedFrame.push_back(color_canny);

	return modifiedFrame;
}

std::vector<std::vector<cv::Point>> BoardDetector::getShapeContours(cv::Mat& frame)
{
	if (frame.empty())
	{
		return std::vector<std::vector<cv::Point>>();
	}

	// vector of points to store contour points
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	findContours(frame, contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

	return contours;
}

std::vector<cv::Vec3f> BoardDetector::detectCircles(cv::Mat frame, std::vector<std::vector<cv::Point>> contours)
{
	if (frame.empty())
	{
		return std::vector<cv::Vec3f>();
	}
	/*
	//Convert the frame to gray
	cv::Mat grayFrame;
	cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);

	//Search for circles in the frame
	std::vector<cv::Vec3f> circles;
	cv::HoughCircles(grayFrame, circles, cv::HOUGH_GRADIENT, 0.5, grayFrame.rows / 12, 200, 30, grayFrame.rows / 24, grayFrame.rows / 10);

	return circles;*/
	
	//Search for circles in the frame
	std::vector<std::vector<cv::Point>> contourPoly(contours.size());

	// bounding box/rect around shape
	std::vector<cv::Rect> bound_rect(contours.size());
	std::vector<cv::Vec3f> circles;

	// loop through all contours detected
	for (int i = 0; i < contours.size(); ++i)
	{
		int c_area = cv::contourArea(contours[i]);   // area of each object contour

		if (c_area > 500) // Area based threshold for emoving noise 
		{
			float peri = arcLength(contours[i], true);

			// Approximate poly curve with stated accurracy
			approxPolyDP(contours[i], contourPoly[i], 0.02 * peri, true);

			bound_rect[i] = cv::boundingRect(contourPoly[i]);

			int obj_corners = (int)contourPoly[i].size();
			// number of corners
			if (obj_corners > 5)
			{
				float aspect_ratio = (float)bound_rect[i].width /
					(float)bound_rect[i].height;
				
				// tolerance for l/w ratio and size of the object
				if (bound_rect[i].width <= frame.rows / 10 && bound_rect[i].width > frame.rows/26)
				{
					// center and width of the circle
					cv::Point center(bound_rect[i].x + bound_rect[i].width / 2, bound_rect[i].y + bound_rect[i].height / 2);
					float radius = bound_rect[i].width / 2;

					circles.push_back(cv::Vec3f(center.x, center.y, radius));
				}
			}
		}
	}

	return circles;
}

std::vector<cv::Vec4f> BoardDetector::containCircles(std::vector<cv::Vec3f> boardCircles, std::vector<cv::Vec3f> boardSquares)
{
	std::vector<cv::Vec4f> containedCircles;

	// For all the squares
	for (int j = 0; j < boardSquares.size(); j++)
	{
		//For all the circles
		for (uint i = 0; i < boardCircles.size(); i++)
		{
			// If it's not a clear square
			if ((j % BOARDSIZE) % 2 == ((int)j / BOARDSIZE) % 2)
			{
				// If the circle is inside the square
				if (boardSquares[j][0] > boardCircles[i][0] && boardSquares[j][0] + boardSquares[j][2] < boardCircles[i][0]
					&& boardSquares[j][1] > boardCircles[i][1] && boardSquares[j][1] + boardSquares[j][2] < boardCircles[i][1])
				{
					containedCircles.push_back(cv::Vec4f(boardCircles[i][0], boardCircles[i][1], boardCircles[i][2], j));
					// Only one circle by square
					i = boardCircles.size();
				}
			}
		}
	}

	return containedCircles;
}

Board BoardDetector::detectColors(cv::Mat image, std::vector<cv::Vec4f> containedCircles)
{
	Board board;

	for (int i = 0; i < containedCircles.size(); i++)
	{
		cv::Vec3b pieceColor = getCircleMeanColor(image, containedCircles[i]);

		//Uncomment to draw the circle with the detected color for debug
		//cv::circle(image, cv::Point(containedCircles[i][0], containedCircles[i][1]), containedCircles[i][2] - 10, cv::Scalar(pieceColor[0], pieceColor[1], pieceColor[2]), -1);

		//Detect the color of the circle
		Color color = getColor(pieceColor);

		if (color == Color::GREEN)
		{
			board.setPlayerPiece((int)containedCircles[i][3] % BOARDSIZE, (int)containedCircles[i][3] / BOARDSIZE, true);
		}
		else if (color == Color::BLUE)
		{
			board.setPlayerPiece((int)containedCircles[i][3] % BOARDSIZE, (int)containedCircles[i][3] / BOARDSIZE, true, true);
		}
		else if (color == Color::WHITE)
		{
			board.setRobotPiece((int)containedCircles[i][3] % BOARDSIZE, (int)containedCircles[i][3] / BOARDSIZE, true);
		}
		else
		{
			board.setRobotPiece((int)containedCircles[i][3] % BOARDSIZE, (int)containedCircles[i][3] / BOARDSIZE, true, true);
		}
	}
	//Uncomment to show the debug image with the detected circles
	//cv::imshow("Debug", image);
	//cv::waitKey(0);

	return board;
}

cv::Vec3b BoardDetector::getCircleMeanColor(cv::Mat image, cv::Vec4f circle)
{
	//Create a mask to get only the circle pixels
	cv::Mat mask = cv::Mat::zeros(image.size(), CV_8UC1);
	cv::circle(mask, cv::Point(circle[0], circle[1]), circle[2] - 10, cv::Scalar(255, 255, 255), -1);	

	//Get the mean color of the circle
	cv::Scalar mean = cv::mean(image, mask);
	return cv::Vec3b(mean[0], mean[1], mean[2]);
}

BoardDetector::Color BoardDetector::getColor(cv::Vec3b color)
{
	if (abs(color[0] - color[1]) < 40 && abs(color[1] - color[2]) < 40 && abs(color[0] - color[2]) < 40)
	{
		return Color::WHITE;
	}
	if (abs(color[2] - color[0]) > 50 && abs(color[2] - color[1]) > 50)
	{
		return Color::RED;
	}
	if (abs(color[0] - color[1]) > 35 && abs(color[0] - color[2]) > 50)
	{
		return Color::BLUE;
	}
	return Color::GREEN;
}

