#pragma once

#include <opencv2/opencv.hpp>
#include <SFML/Graphics.hpp>
#include <algorithm>

class Camera
{
public:
	Camera();
	~Camera();

	/// <summary>
	/// Lanch the webcam thread
	/// </summary>
	void startWebcamThread();

	/// <summary>
	/// return the image from the webcam
	/// </summary>
	cv::Mat getFrame();

private:

	/// <summary>
	/// Get the image from the webcam, and store it in the frame variable
	/// </summary>
	/// <param name="frame">The frame to store the image</param>
	void getWebcamImage(cv::Mat* frame);

	bool webcamThreadRunning = false;
	cv::Mat* frame;
	std::thread webcamThread;
	std::mutex frameMutex;
};
