#include "Rules.h"

Rules::Rules(sf::RenderWindow& window, sf::Font* font)
{
	backButton = Button();
	backButton.setDefaultButtonColor();
	backButton.setButtonSize(sf::Vector2f(250, 100));
	backButton.setButtonPosition(sf::Vector2f(10, 10));
	backButton.setButtonFont(font);
	backButton.setButtonText("Retour");
	backButton.setButtonTextSize(60);

	versionText.setFont(*font);
	versionText.setString("Jeu de dame anglais :");
	versionText.setFillColor(sf::Color::White);

	rulesText.setFont(*font);
	rulesText.setString("-   Les déplacements se font en diagonale sur les cases sombres.\n-   Les pions ne vont que vers l'avant, les dames peuvent aller dans toutes les directions.\n-   Les pions et les dames se déplacent d'une seule case et mangent les pions directement voisins.\n-   Obligation de manger si possible. Possiblité de manger plusieurs pions.\n-   Pas de priorité sur les rafles.");
	rulesText.setFillColor(sf::Color::White);
}

void Rules::draw(sf::RenderWindow& window)
{
	sf::Vector2u windowSize = window.getSize();

	versionText.setCharacterSize(windowSize.x / 25);
	rulesText.setCharacterSize(windowSize.x / 31);
	versionText.setPosition(sf::Vector2f(windowSize.x / 2 - versionText.getLocalBounds().width / 2, windowSize.y / 4));
	rulesText.setPosition(sf::Vector2f(windowSize.x / 2 - rulesText.getLocalBounds().width / 2, windowSize.y * 2 / 5));

	window.draw(versionText);
	window.draw(rulesText);
	backButton.draw(window);
}

StateMachine::State Rules::handleEvent(sf::Event event)
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
	return StateMachine::State::Rules;
}
