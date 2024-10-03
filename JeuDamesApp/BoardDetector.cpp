#include "BoardDetector.h"


std::vector<cv::Vec3f> BoardDetector::workingCircles;

Board BoardDetector::detectBoard(cv::Mat image, Color playerColor)
{
	// copy of the image to draw on the image and keep a clean image for the detection
	cv::Mat copy = image.clone();
	// modify the image to see only the contours
	modifyFrame(copy);

	//Detect the squares in the image
	std::vector<std::vector<cv::Point>> contours = getShapeContours(copy);
	cv::imshow("Modified frame", copy);
	std::vector<cv::Vec3f> squares = detectSquares(image, contours);
	std::vector<cv::Vec3f> sortedSquares = sortSquares(squares);
	if (squares.size() == 0)
	{
		std::cout << "No squares detected" << std::endl;
		return Board();
	}
	for (int i = 0; i < squares.size(); i++)
	{
		cv::circle(image, cv::Point(squares[i][0], squares[i][1]), squares[i][2], cv::Scalar(255, 0, 0), 2);
	}
	if (sortedSquares.size() == 0)
	{
		std::cout << "Not sorted" << std::endl;
		return Board();
	}
	for (int i = 0; i < sortedSquares.size(); i++)
	{
		// draw squares in the image
		cv::Point text_point = cv::Point(sortedSquares[i][0], sortedSquares[i][1] - 10);
		cv:putText(image, std::to_string(i),            // shape type
			text_point,         // x,y co-ordinate 
			cv::FONT_HERSHEY_PLAIN,  // Font name
			2,                   // Font scale
			cv::Scalar(0, 0, 255),   // Font color in BGR (Red)
			2);                  // Thickness
	}
	
	//Detect the circles in the image
	std::vector<cv::Vec3f> circles = detectCircles(copy);
	if (circles.size() == 0)
	{
		std::cout << "No circles detected" << std::endl;
		return Board();
	}
	for (int i = 0; i < circles.size(); i++)
	{
		// draw circles in the image (showed by the application ?)
		cv::circle(image, cv::Point(circles[i][0], circles[i][1]), circles[i][2], cv::Scalar(0, 0, 255), 2);
	}
	
	return Board();
	/*
	//Search the first circle played by the player
	cv::Vec3f firstCircle = searchFirstCircle(image, circles, playerColor);
	if (firstCircle == cv::Vec3f())
	{
		std::cout << "No first circle detected" << std::endl;
		return Board();
	}
	cv::circle(image, cv::Point(firstCircle[0], firstCircle[1]), 5, cv::Scalar(255, 255, 255), -1);

	//Filter the circles to only keep the one from the board
	std::vector<cv::Vec3f> boardCircles = filterCircles(image, circles, firstCircle);
	if (boardCircles.size() == 0)
	{
		std::cout << "No board circles detected" << std::endl;
	}

	//Sort the circles in the correct order
	std::vector<cv::Vec3f> sortedCircles = sortCircles(boardCircles);
	if (sortedCircles.size() == 0)
	{
		std::cout << "No sorted circles detected" << std::endl;
	}

	//Detect the colors of the circles
	Board board = detectColors(image, sortedCircles);
	return board;*/
}

void BoardDetector::modifyFrame(cv::Mat& frame)
{
	if (frame.empty())
	{
		return;
	}

	// Declaring few Mat object for further operations
	cv::Mat img_gray, img_blur, img_canny, img_dilate;

	// Convert img color to gray. Output image is second arg
	cv::cvtColor(frame, img_gray, cv::COLOR_BGR2GRAY);

	// Threshold the image (resistant to the change of luminosity)
	//cv::adaptiveThreshold(img_gray, img_threshold, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 3, 5);
	//cv::imshow("Threshold", img_threshold);
	// Blurring image using gaussian fliter. Size(3,3) is SE kernal (erase noise)
	cv::GaussianBlur(img_gray, img_blur, cv::Size(3, 3), 3, 0);

	// Edge detection using canny algo
	cv::Canny(img_blur, img_canny, 25, 75);
	
	// Running dilation on canny output to improve edge thickness
	cv::Mat se1 = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	cv::dilate(img_canny, frame, se1);

	cv::imshow("Test", frame);
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

std::vector<cv::Vec3f> BoardDetector::detectCircles(cv::Mat& frame)
{
	//Search for circles in the frame
	std::vector<cv::Vec3f> circles;
	cv::HoughCircles(frame, circles, cv::HOUGH_GRADIENT, 0.5, frame.rows / 12, 200, 30, frame.rows / 24, frame.rows / 9);


	return circles;
}

std::vector<cv::Vec3f> BoardDetector::detectSquares(cv::Mat frame, std::vector<std::vector<cv::Point>> contours)
{
	std::vector<std::vector<cv::Point>> contourPoly(contours.size());

	// bounding box/rect around shape
	std::vector<cv::Rect> bound_rect(contours.size());
	std::vector<cv::Vec3f> squares;

	// loop through all contours detected
	for (int i = 0; i < contours.size(); ++i)
	{
		int c_area = cv::contourArea(contours[i]);   // area of each object contour

		if (c_area > 1000) // Area based threshold for emoving noise 
		{
			float peri = arcLength(contours[i], true);

			// Approximate poly curve with stated accurracy
			approxPolyDP(contours[i], contourPoly[i], 0.02 * peri, true);

			bound_rect[i] = cv::boundingRect(contourPoly[i]);

			int obj_corners = (int)contourPoly[i].size();
			cv::rectangle(frame, cv::Point(bound_rect[i].x, bound_rect[i].y), cv::Point(bound_rect[i].x + bound_rect[i].width, bound_rect[i].y + bound_rect[i].height), cv::Scalar(0, 0, 255), 1);
			// number of corners
			if (obj_corners == 4)
			{
				float aspect_ratio = (float)bound_rect[i].width /
					(float)bound_rect[i].height;

				// tolerance for l/w ratio and size of the object
				if (aspect_ratio >= 0.7 && aspect_ratio <= 1.5 && bound_rect[i].width <= frame.rows/8)
				{
					// center and width of the square
					cv::Point center(bound_rect[i].x + bound_rect[i].width / 2, bound_rect[i].y + bound_rect[i].height / 2);
					float radius = bound_rect[i].width/2;

					// Ajouter le centre et la largeur au vecteur
					squares.push_back(cv::Vec3f(center.x, center.y, radius));
				}
			}
		}
	}

	return squares;
}

cv::Vec3f BoardDetector::searchFirstCircle(cv::Mat image, std::vector<cv::Vec3f> circles, Color playerColor)
{
	std::cout << "BoardDetector::searchFirstCircle" << std::endl;
	cv::Vec3f circle;
	return circle;

	/*
	if (circles.size() == 0)
	{
		return cv::Vec3f();
	}

	//Search the first circle with the player color inside
	uint closestCircleIndex = 0;
	uint closestCircleValue = 1000000;
	for (int i = 0; i < circles.size(); i++)
	{
		cv::Vec3b detectedColor = getCircleMeanColor(image, circles[i]);

		Color detectedColorType = getColor(detectedColor);
		if (detectedColorType == Color::EMPTY)
		{
			continue;
		}
		if (detectedColorType == playerColor)
		{
			closestCircleIndex = i;
			break;
		}
	}
	cv::Vec3f firstCircle = circles[closestCircleIndex];

	//Remove the first circle from the circles vector
	circles.erase(circles.begin() + closestCircleIndex);
	return firstCircle;
	*/
}

std::vector<cv::Vec3f> BoardDetector::filterCircles(cv::Mat image, std::vector<cv::Vec3f> circles, cv::Vec3f firstCircle)
{
	std::cout << "BoardDetector::filterCircles" << std::endl;
	std::vector<cv::Vec3f> circles2;
	return circles2;

	/*
	std::vector<cv::Vec3f> boardCircles;
	
	//Search in the same line
	uint i = 0;
	while(i < circles.size())
	{
		if (circles[i][1] >= firstCircle[1] - 10 && circles[i][1] <= firstCircle[1] + 10) //&& circles[i][2] >= firstCircle[2] - 5 && circles[i][2] <= firstCircle[2] + 5)
		{
			boardCircles.push_back(circles[i]);
			circles.erase(circles.begin() + i);
		}
		i++;
	}

	if (boardCircles.size() != 7)
	{
		std::cout << "Not enough circles in the same line" << std::endl;
		return std::vector<cv::Vec3f>();
	}

	//Search in the same column
	for (int i = 0; i < boardCircles.size(); i++)
	{
		uint j = 0;
		while (j < circles.size())
		{
			if (circles[j][0] >= boardCircles[i][0] - 10 && circles[j][0] <= boardCircles[i][0] + 10 && circles[j][2] >= boardCircles[i][2] - 5 && circles[j][2] <= boardCircles[i][2] + 5)
			{
				boardCircles.push_back(circles[j]);
				circles.erase(circles.begin() + j);
			}
			j++;
		}
	}

	//If the board is not complete
	if (boardCircles.size() != 42)
	{
		std::cout << "Not enough circles in the same column" << std::endl;
		return std::vector<cv::Vec3f>();
	}

	return boardCircles;
	*/
}

std::vector<int> BoardDetector::sortCircles(std::vector<cv::Vec3f> boardCircles)
{
	std::cout << "BoardDetector::sortedCircles" << std::endl;
	std::vector<int> circles;
	return circles;

	/*
	if (boardCircles.size() != 42)
	{
		return std::vector<cv::Vec3f>();
	}

	std::vector<cv::Vec3f> sortedCircles;

	//For all the columns
	for (uint i = 0; i < 7; i++)
	{
		uint min = 1000000;
		uint minIndex = 0;

		//Search the first circle at minimum x and y
		for (int j = 0; j < boardCircles.size(); j++)
		{
			if (boardCircles[j][0] + boardCircles[j][1] < min)
			{
				min = boardCircles[j][0] + boardCircles[j][1];
				minIndex = j;
			}
		}

		//Add the first circle to the sortedCircles vector
		sortedCircles.push_back(boardCircles[minIndex]);
		//Remove the first circle from the boardCircles vector
		boardCircles.erase(boardCircles.begin() + minIndex);

		//Search the next 5 circles in the same line
		for (int j = 0; j < 5; j++)
		{
			min = 1000000;
			minIndex = 0;
			for (int j = 0; j < boardCircles.size(); j++)
			{
				if (abs(boardCircles[j][0] - sortedCircles[i * 6][0]) < sortedCircles[i*6][2] && boardCircles[j][1] < min)
				{
					min = boardCircles[j][1];
					minIndex = j;
				}
			}
			sortedCircles.push_back(boardCircles[minIndex]);
			boardCircles.erase(boardCircles.begin() + minIndex);
		}
	}

	return sortedCircles;
	*/
}

std::vector<cv::Vec3f> BoardDetector::sortSquares(std::vector<cv::Vec3f> boardSquares)
{ 
	if (boardSquares.size() != 64)
	{
		return std::vector<cv::Vec3f>();
	}

	std::vector<cv::Vec3f> sortedSquares;

	//For all the columns
	for (uint i = 0; i < BOARDSIZE; i++)
	{
		uint min = 1000000;
		uint minIndex = 0;

		//Search the first circle at minimum x and y
		for (int j = 0; j < boardSquares.size(); j++)
		{
			if (boardSquares[j][0] + boardSquares[j][1] < min)
			{
				min = boardSquares[j][0] + boardSquares[j][1];
				minIndex = j;
			}
		}

		//Add the first square to the sortedSquares vector
		sortedSquares.push_back(boardSquares[minIndex]);
		//Remove the first square from the boardSquares vector
		boardSquares.erase(boardSquares.begin() + minIndex);

		//Search the next squares in the same column
		for (int j = 0; j < BOARDSIZE-1; j++)
		{
			min = 1000000;
			minIndex = 0;
			for (int j = 0; j < boardSquares.size(); j++)
			{
				if (abs(boardSquares[j][0] - sortedSquares[i * (BOARDSIZE)][0]) < sortedSquares[i * (BOARDSIZE)][2] && boardSquares[j][1] < min)
				{
					min = boardSquares[j][1];
					minIndex = j;
				}
			}
			sortedSquares.push_back(boardSquares[minIndex]);
			boardSquares.erase(boardSquares.begin() + minIndex);
		}
	}

	return sortedSquares;
}

Board BoardDetector::detectColors(cv::Mat image, std::vector<cv::Vec3f> boardCircles)
{
	std::cout << "BoardDetector::detectColors" << std::endl;
	return Board();

	/*
	if (boardCircles.size() != 42)
	{
		if (workingCircles.size() == 42)
		{
			boardCircles = workingCircles;
		}
		else
		{
			return Board();
		}
	}
	else
	{
		workingCircles = boardCircles;
	}

	Board board;
	uint playerThreshold = 200;
	uint robotThreshold = 150;

	for (int i = 0; i < boardCircles.size(); i++)
	{
		cv::Vec3b pieceColor = getCircleMeanColor(image, boardCircles[i]);

		//Draw the circle with the detected color for debug
		cv::circle(image, cv::Point(boardCircles[i][0], boardCircles[i][1]), boardCircles[i][2] - 10, cv::Scalar(pieceColor[0], pieceColor[1], pieceColor[2]), -1);

		//Detect the color of the circle
		Color color = getColor(pieceColor);

		if (color == Color::EMPTY)
		{
			continue;
		}
		else if (color == Color::RED)
		{

			board.setPlayerPiece(i / 6, 5 - i % 6, true);
		}
		else
		{
			board.setRobotPiece(i / 6, 5 - i % 6, true);
		}
	}
	//Uncomment to show the debug image with the detected circles
	//cv::imshow("Debug", image);

	return board;
	*/
}

cv::Vec3b BoardDetector::getCircleMeanColor(cv::Mat image, cv::Vec3f circle)
{
	std::cout << "BoardDetector::getCircleMeanColor" << std::endl;
	cv::Vec3b mean;
	return mean;

	/*
	//Create a mask to get only the circle pixels
	cv::Mat mask = cv::Mat::zeros(image.size(), CV_8UC1);
	cv::circle(mask, cv::Point(circle[0], circle[1]), circle[2] - 10, cv::Scalar(255), -1);	

	//Get the mean color of the circle
	cv::Scalar mean = cv::mean(image, mask);
	return cv::Vec3b(mean[0], mean[1], mean[2]);
	*/
}

BoardDetector::Color BoardDetector::getColor(cv::Vec3b color)
{
	std::cout << "BoardDetector::getColor" << std::endl;
	return Color::EMPTY;

	/*
	if (abs(color[0] - color[1]) < 60 && abs(color[1] - color[2]) < 60 && abs(color[0] - color[2]) < 60)
	{
		return Color::EMPTY;
	}
	if (abs(color[2] - color[0]) > 50 && abs(color[2] - color[1]) > 50)
	{
		return Color::RED;
	}
	return Color::YELLOW;
	*/
}

std::vector<cv::Vec3f> BoardDetector::addAndRemoveDuplicatesCircle(std::vector<cv::Vec3f> newCircles, std::vector<cv::Vec3f> oldCircles)
{
	std::cout << "BoardDetector::addAndRemoveDuplicatesCircle" << std::endl;
	std::vector<cv::Vec3f> circles;
	return circles;

	/*
	std::vector<cv::Vec3f> result = newCircles;

	for (int i = 0; i < oldCircles.size(); i++)
	{
		result.push_back(oldCircles[i]);
	}

	for (int i = 0; i < result.size(); i++)
	{
		for (int j = i + 1; j < result.size(); j++)
		{
			if (abs(result[i][0] - result[j][0]) < 10 && abs(result[i][1] - result[j][1]) < 10)
			{
				result.erase(result.begin() + j);
			}
		}
	}

	return result;
	*/
}

std::vector<cv::Vec3f> BoardDetector::addAndRemoveDuplicatesSquare(std::vector<cv::Vec3f> newsquares, std::vector<cv::Vec3f> oldSquares)
{
	std::cout << "BoardDetector::addAndRemoveDuplicatesSquare" << std::endl;
	std::vector<cv::Vec3f> squares;
	return squares;

	/*
	std::vector<cv::Vec3f> result = newCircles;

	for (int i = 0; i < oldCircles.size(); i++)
	{
		result.push_back(oldCircles[i]);
	}

	for (int i = 0; i < result.size(); i++)
	{
		for (int j = i + 1; j < result.size(); j++)
		{
			if (abs(result[i][0] - result[j][0]) < 10 && abs(result[i][1] - result[j][1]) < 10)
			{
				result.erase(result.begin() + j);
			}
		}
	}

	return result;
	*/
}
