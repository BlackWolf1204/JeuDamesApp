#include "FrameDetail.h"

FrameDetail::FrameDetail()
{
	blurImage = nullptr;
	blurSprite = nullptr;
	blurTexture = nullptr;
	cannyImage = nullptr;
	cannySprite = nullptr;
	cannyTexture = nullptr;
	grayImage = nullptr;
	graySprite = nullptr;
	grayTexture = nullptr;
	webcamImage = nullptr;
	webcamSprite = nullptr;
	webcamTexture = nullptr;
}

FrameDetail::~FrameDetail()
{
	if (webcamThread != nullptr)
	{
		webcamThreadRunningFrame = false;
		webcamThread->join();
		delete webcamThread;
		webcamThread = nullptr;
	}
	delete blurTexture;
	delete blurImage;
	delete blurSprite;
	delete cannyImage;
	delete cannySprite;
	delete cannyTexture;
	delete grayImage;
	delete graySprite;
	delete grayTexture;
	delete webcamImage;
	delete webcamTexture;
	delete webcamSprite;
}

FrameDetail::FrameDetail(sf::RenderWindow& window, sf::Font* font)
{
	backButton = Button();
	backButton.setDefaultButtonColor();
	backButton.setButtonSize(sf::Vector2f(250, 100));
	backButton.setButtonPosition(sf::Vector2f(10, 10));
	backButton.setButtonFont(font);
	backButton.setButtonText("Retour");
	backButton.setButtonTextSize(60);

	webcamImage = new sf::Image();
	webcamTexture = new sf::Texture();
	webcamSprite = new sf::Sprite();
	webcamSprite->setScale(0.45f, 0.45f);
	webcamSprite->setRotation(-90);

	grayImage = new sf::Image();
	grayTexture = new sf::Texture();
	graySprite = new sf::Sprite();
	graySprite->setScale(0.45f, 0.45f);
	graySprite->setRotation(-90);

	blurImage = new sf::Image();
	blurTexture = new sf::Texture();
	blurSprite = new sf::Sprite();
	blurSprite->setScale(0.45f, 0.45f);
	blurSprite->setRotation(-90);

	cannyImage = new sf::Image();
	cannyTexture = new sf::Texture();
	cannySprite = new sf::Sprite();
	cannySprite->setScale(0.45f, 0.45f);
	cannySprite->setRotation(-90);

	webcamText.setFont(*font);
	webcamText.setString("-  Image de sortie de la caméra.\n   Ajout d'une grille pour calibrage.");
	webcamText.setFillColor(sf::Color::White);

	grayText.setFont(*font);
	grayText.setString("-  Image après convertion en niveau de gris.");
	grayText.setCharacterSize(35);
	grayText.setFillColor(sf::Color::White);

	blurText.setFont(*font);
	blurText.setString("-  Image après application d'un filtre Gaussien.\n   Lisse l'image (réduit le \"bruit\" de l'image).");
	blurText.setCharacterSize(35);
	blurText.setFillColor(sf::Color::White);

	cannyText.setFont(*font);
	cannyText.setString("-  Image après application d'un filtre de Canny.\n   Fait ressortir les contours des objets.");
	cannyText.setCharacterSize(35);
	cannyText.setFillColor(sf::Color::White);
}

void FrameDetail::draw(sf::RenderWindow& window)
{
	sf::Vector2u windowSize = window.getSize();

	// Update the webcam feed size and position according to the window size
	webcamSprite->setPosition(sf::Vector2f(((float)windowSize.x / 2) - webcamSprite->getGlobalBounds().width - 5, webcamSprite->getGlobalBounds().height + 20));
	graySprite->setPosition(sf::Vector2f(webcamSprite->getPosition().x + webcamSprite->getGlobalBounds().width + 10, webcamSprite->getPosition().y));
	blurSprite->setPosition(sf::Vector2f(webcamSprite->getPosition().x, webcamSprite->getPosition().y + webcamSprite->getGlobalBounds().height + 10));
	cannySprite->setPosition(sf::Vector2f(webcamSprite->getPosition().x + webcamSprite->getGlobalBounds().height + 10, webcamSprite->getPosition().y + webcamSprite->getGlobalBounds().height + 10));

	// Update the webcam text size and position according to the webcame sprite position
	webcamText.setCharacterSize(windowSize.x / 35);
	grayText.setCharacterSize(windowSize.x / 35);
	blurText.setCharacterSize(windowSize.x / 35);
	cannyText.setCharacterSize(windowSize.x / 35);

	int maxWidth = std::max(webcamText.getGlobalBounds().width, blurText.getGlobalBounds().width);
	int maxHeight = std::max(webcamText.getGlobalBounds().height, grayText.getGlobalBounds().height);
	webcamText.setPosition(sf::Vector2f(((float)windowSize.x / 2) - maxWidth - 20, blurSprite->getPosition().y + 50));
	grayText.setPosition(sf::Vector2f(((float)windowSize.x / 2) + 20, webcamText.getPosition().y));
	blurText.setPosition(sf::Vector2f(((float)windowSize.x / 2) - maxWidth - 20, webcamText.getPosition().y + maxHeight + 30));
	cannyText.setPosition(sf::Vector2f(((float)windowSize.x / 2) + 20, webcamText.getPosition().y + maxHeight + 30));

	window.draw(webcamText);
	window.draw(grayText);
	window.draw(blurText);
	window.draw(cannyText);
	window.draw(*webcamSprite);
	window.draw(*graySprite);
	window.draw(*blurSprite);
	window.draw(*cannySprite);

	backButton.draw(window);
}

void FrameDetail::getCameraFrame(cv::Mat frame)
{
	if (frame.empty())
	{
		return;
	}
	sf::Uint8* pixels = getFramePixel(frame);

	int frameWidth = frame.cols;
	int frameHeight = frame.rows;

	webcamImage->create(frameHeight, frameHeight, pixels);
	delete[] pixels;
	webcamTexture->loadFromImage(*webcamImage);
	webcamSprite->setTexture(*webcamTexture);
}

void FrameDetail::getGrayFrame(cv::Mat frame)
{
	if (frame.empty())
	{
		return;
	}

	sf::Uint8* pixels = getFramePixel(frame);

	int frameWidth = frame.cols;
	int frameHeight = frame.rows;

	grayImage->create(frameHeight, frameHeight, pixels);
	delete[] pixels;
	grayTexture->loadFromImage(*grayImage);
	graySprite->setTexture(*grayTexture);
}

void FrameDetail::getBlurFrame(cv::Mat frame)
{
	if (frame.empty())
	{
		return;
	}

	sf::Uint8* pixels = getFramePixel(frame);

	int frameWidth = frame.cols;
	int frameHeight = frame.rows;

	blurImage->create(frameHeight, frameHeight, pixels);
	delete[] pixels;
	blurTexture->loadFromImage(*blurImage);
	blurSprite->setTexture(*blurTexture);
}

void FrameDetail::getCannyFrame(cv::Mat frame)
{
	if (frame.empty())
	{
		return;
	}

	sf::Uint8* pixels = getFramePixel(frame);

	int frameWidth = frame.cols;
	int frameHeight = frame.rows;

	cannyImage->create(frameHeight, frameHeight, pixels);
	delete[] pixels;
	cannyTexture->loadFromImage(*cannyImage);
	cannySprite->setTexture(*cannyTexture);
}

sf::Uint8* FrameDetail::getFramePixel(cv::Mat frame)
{
	int frameWidth = frame.cols;
	int frameHeight = frame.rows;
	// cut the left and right sides of the frame
	int diff = (frameWidth - frameHeight) / 2;
	sf::Uint8* pixels = new sf::Uint8[4 * frameHeight * frameHeight];
	for (int i = 0; i < frameHeight; i++)
	{
		for (int j = 0; j < frameHeight; j++)
		{
			cv::Vec3b color = frame.at<cv::Vec3b>(j, i + diff);
			pixels[(i + j * frameHeight) * 4] = color[2];
			pixels[(i + j * frameHeight) * 4 + 1] = color[1];
			pixels[(i + j * frameHeight) * 4 + 2] = color[0];
			pixels[(i + j * frameHeight) * 4 + 3] = 255;
		}
	}

	return pixels;
}

bool FrameDetail::getDisplayed()
{
	return displayed;
}

void FrameDetail::setDisplayed(bool state)
{
	displayed = state;
}

StateMachine::State FrameDetail::handleEvent(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (backButton.mouseIsInsideButton(sf::Vector2f(float(event.mouseButton.x), float(event.mouseButton.y))))
		{
			std::cout << "Back button pressed" << std::endl;
			backButton.setDefaultButtonColor();
			return StateMachine::State::MainMenu;
		}
	}
	if (event.type == sf::Event::MouseMoved)
	{
		if (backButton.mouseIsInsideButton(sf::Vector2f(float(event.mouseMove.x), float(event.mouseMove.y))))
		{
			backButton.setSelectedButtonColor();
		}
		else
		{
			backButton.setDefaultButtonColor();
		}
	}
	return StateMachine::State::FrameDetail;
}
