#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <opencv2/opencv.hpp>
#include "Button.h"
#include "StateMachine.h"
#include "Camera.h"

static std::atomic<bool> webcamThreadRunningFrame = true;

/// <summary>
/// This class is responsible for the frame details. It will display the different states of the  webcame frame during the image processing.
/// </summary>
class FrameDetail
{
public:
	FrameDetail();

	/// <summary>
	/// Terminate the webcam thread and free the memory.
	/// </summary>
	~FrameDetail();

	/// <summary>
	/// Initialise the frame details with the given font.
	/// </summary>
	/// <param name="window">The window where is the FrameDetail.</param>
	/// <param name="font">The font to use for the texts.</param>
	FrameDetail(sf::RenderWindow& window, sf::Font* font);

	/// <summary>
	/// Draw the frame details and all his components on the given window.
	/// </summary>
	/// <param name="window">The window to draw the game UI on.</param>
	void draw(sf::RenderWindow& window);

	/// <summary>
	/// Get the camera frame and update the webcam frame.
	/// </summary>
	/// <param name="frame">The camera frame to update the webcam frame with.</param>
	void getCameraFrame(cv::Mat frame);

	/// <summary>
	/// Get the gray frame and update the gray frame.
	/// </summary>
	/// <param name="frame">The camera frame to update the gray frame with.</param>
	void getGrayFrame(cv::Mat frame);

	/// <summary>
	/// Get the blur frame and update the blur frame.
	/// </summary>
	/// <param name="frame">The camera frame to update the blur frame with.</param>
	void getBlurFrame(cv::Mat frame);

	/// <summary>
	/// Get the canny frame and update the canny frame.
	/// </summary>
	/// <param name="frame">The camera frame to update the canny frame with.</param>
	void getCannyFrame(cv::Mat frame);

	/// <summary>
	/// Get the pixels of a given frame
	/// </summary>
	sf::Uint8* getFramePixel(cv::Mat frame);

	/// <summary>
	/// Get if the frame detail is displayed or not
	/// </summary>
	/// <return>Displayed or not</return>
	bool getDisplayed();

	/// <summary>
	/// Set if the frame detail is displayed or not
	/// </summary>
	/// <param name="state">Displayed or not</param>
	void setDisplayed(bool state);

	/// <summary>
	/// Handle the given event (Mopuse click, Mouse move, ...)
	/// </summary>
	/// <param name="event">The event to handle.</param>
	StateMachine::State handleEvent(sf::Event event);

private:
	Button backButton;

	std::thread* webcamThread = nullptr;

	// FrameDetail displayed or not
	bool displayed = false;

	// Frame states
	sf::Image* webcamImage;
	sf::Texture* webcamTexture;
	sf::Sprite* webcamSprite;

	sf::Image* grayImage;
	sf::Texture* grayTexture;
	sf::Sprite* graySprite;

	sf::Image* blurImage;
	sf::Texture* blurTexture;
	sf::Sprite* blurSprite;

	sf::Image* cannyImage;
	sf::Texture* cannyTexture;
	sf::Sprite* cannySprite;

	// Description text
	sf::Text webcamText;
	sf::Text grayText;
	sf::Text blurText;
	sf::Text cannyText;
};

