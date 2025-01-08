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
	delete webcamImage;
	delete webcamTexture;
	delete webcamSprite;
}

FrameDetail::FrameDetail(sf::RenderWindow& window, sf::Font* font)
{
	backButton = Button();
	backButton.setButtonColor(sf::Color::Red);
	backButton.setButtonSize(sf::Vector2f(250, 100));
	backButton.setButtonPosition(sf::Vector2f(10, 10));
	backButton.setButtonFont(font);
	backButton.setButtonTextColor(sf::Color::White);
	backButton.setButtonText("Retour");
	backButton.setButtonTextSize(60);

	webcamImage = new sf::Image();
	webcamTexture = new sf::Texture();
	webcamSprite = new sf::Sprite();
	webcamSprite->setScale(0.7f, 0.7f);
	webcamSprite->setRotation(-90);

	grayImage = new sf::Image();
	grayTexture = new sf::Texture();
	graySprite = new sf::Sprite();
	graySprite->setScale(0.7f, 0.7f);
	graySprite->setRotation(-90);

	blurImage = new sf::Image();
	blurTexture = new sf::Texture();
	blurSprite = new sf::Sprite();
	blurSprite->setScale(0.7f, 0.7f);
	blurSprite->setRotation(-90);

	cannyImage = new sf::Image();
	cannyTexture = new sf::Texture();
	cannySprite = new sf::Sprite();
	cannySprite->setScale(0.7f, 0.7f);
	cannySprite->setRotation(-90);

	webcamText.setFont(*font);
	webcamText.setString("Image de sortie de la caméra.\nAjout d'une grille pour calibrage.");
	webcamText.setCharacterSize(35);
	webcamText.setFillColor(sf::Color::White);

	grayText.setFont(*font);
	grayText.setString("Image après convertion \nen niveau de gris.");
	grayText.setCharacterSize(35);
	grayText.setFillColor(sf::Color::White);

	blurText.setFont(*font);
	blurText.setString("Image après application d'un \nfiltre Gaussien. Lisse l'image \n(réduit le \"bruit\" de l'image).");
	blurText.setCharacterSize(35);
	blurText.setFillColor(sf::Color::White);

	cannyText.setFont(*font);
	cannyText.setString("Image après application d'un \nfiltre de Canny. Fait ressortir \nles contours des objets.");
	cannyText.setCharacterSize(35);
	cannyText.setFillColor(sf::Color::White);
}

void FrameDetail::draw(sf::RenderWindow& window)
{
	sf::Vector2u windowSize = window.getSize();

	// Update the webcam feed size and position according to the window size
	if (webcamTexture->getSize().x > 0 && webcamTexture->getSize().y > 0)
	{
		float scaleX = windowSize.x / webcamTexture->getSize().x * 0.4f;
		float scaleY = windowSize.y / webcamTexture->getSize().y * 0.4f;
		float scale = std::min(scaleX, scaleY);
		webcamSprite->setScale(scale, scale);
	}
	webcamSprite->setPosition(sf::Vector2f(((float)windowSize.x - backButton.getButtonSize().x) / 2 - webcamSprite->getGlobalBounds().width / 2 - 10, ((float)windowSize.y - 10) / 2));
	
	if (grayTexture->getSize().x > 0 && grayTexture->getSize().y > 0)
	{
		float scaleX = windowSize.x / grayTexture->getSize().x * 0.4f;
		float scaleY = windowSize.y / grayTexture->getSize().y * 0.4f;
		float scale = std::min(scaleX, scaleY);
		graySprite->setScale(scale, scale);
	}
	graySprite->setPosition(sf::Vector2f(((float)windowSize.x - backButton.getButtonSize().x) / 2 + graySprite->getGlobalBounds().width / 2 + 10,  ((float)windowSize.y - 10) / 2));
	
	if (blurTexture->getSize().x > 0 && blurTexture->getSize().y > 0)
	{
		float scaleX = windowSize.x / blurTexture->getSize().x * 0.4f;
		float scaleY = windowSize.y / blurTexture->getSize().y * 0.4f;
		float scale = std::min(scaleX, scaleY);
		blurSprite->setScale(scale, scale);
	}
	blurSprite->setPosition(sf::Vector2f((windowSize.x - backButton.getButtonSize().x) / 2 - blurSprite->getGlobalBounds().width / 2 - 10, webcamSprite->getPosition().y + blurSprite->getGlobalBounds().width + 20));
	if (cannyTexture->getSize().x > 0 && cannyTexture->getSize().y > 0)
	{
		float scaleX = windowSize.x / cannyTexture->getSize().x * 0.4f;
		float scaleY = windowSize.y / cannyTexture->getSize().y * 0.4f;
		float scale = std::min(scaleX, scaleY);
		cannySprite->setScale(scale, scale);
	}
	cannySprite->setPosition(sf::Vector2f((windowSize.x - backButton.getButtonSize().x) / 2 + cannySprite->getGlobalBounds().width / 2 + 10, graySprite->getPosition().y + cannySprite->getGlobalBounds().width + 20));

	// Update the webcam text size and position according to the webcame sprite position
	webcamText.setPosition(sf::Vector2f(webcamSprite->getPosition().x - webcamText.getGlobalBounds().width - 20, webcamSprite->getPosition().y - (webcamSprite->getGlobalBounds().height / 2)));
	grayText.setPosition(sf::Vector2f(graySprite->getPosition().x + graySprite->getGlobalBounds().width + 20, graySprite->getPosition().y - (graySprite->getGlobalBounds().height / 2)));
	blurText.setPosition(sf::Vector2f(blurSprite->getPosition().x - blurText.getGlobalBounds().width - 20, blurSprite->getPosition().y - (blurSprite->getGlobalBounds().height / 2)));
	cannyText.setPosition(sf::Vector2f(cannySprite->getPosition().x + cannySprite->getGlobalBounds().width + 20, cannySprite->getPosition().y - (cannySprite->getGlobalBounds().height / 2)));

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

StateMachine::State FrameDetail::handleEvent(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (backButton.mouseIsInsideButton(sf::Vector2f(float(event.mouseButton.x), float(event.mouseButton.y))))
		{
			std::cout << "Back button pressed" << std::endl;
			backButton.setButtonColor(sf::Color::Red);
			return StateMachine::State::MainMenu;
		}
	}
	if (event.type == sf::Event::MouseMoved)
	{
		if (backButton.mouseIsInsideButton(sf::Vector2f(float(event.mouseMove.x), float(event.mouseMove.y))))
		{
			backButton.setButtonColor(sf::Color::Green);
		}
		else
		{
			backButton.setButtonColor(sf::Color::Red);
		}
	}
	return StateMachine::State::FrameDetail;
}
