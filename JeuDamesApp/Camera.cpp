#include "Camera.h"


Camera::Camera()
{
	frame = new cv::Mat();
	startWebcamThread();
}

Camera::~Camera()
{
	webcamThreadRunning = false;
	webcamThread.join();
	delete frame;
}

void Camera::startWebcamThread()
{
	webcamThreadRunning = true;
	webcamThread = std::thread(&Camera::getWebcamImage, this, frame);
}

cv::Mat Camera::getFrame()
{
	frameMutex.lock();
	cv::Mat tempFrame = frame->clone();
	frameMutex.unlock();
	return tempFrame;
}

void Camera::getWebcamImage(cv::Mat* frame)
{
	if (frame == nullptr)
		return;

	std::cout << "Begin connection camera" << std::endl;
	cv::VideoCapture cap(0);
	std::cout << "Camera connected !" << std::endl;
	if (!cap.isOpened())
		return;

	while (webcamThreadRunning)
	{
		cv::Mat tempFrame;
		cap >> tempFrame;
		frameMutex.lock();
		*frame = tempFrame;
		frameMutex.unlock();
	}
}
