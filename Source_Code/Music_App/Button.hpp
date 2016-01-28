#pragma once

#include <SFML\Graphics.hpp>

class Button {
public:
	Button();
	~Button();

	void init(std::string, std::string, sf::Vector2f, sf::Vector2f);
	bool collision(sf::Vector2i);
	sf::Sprite getButton();
private:
	sf::Texture buttonTexture;
	sf::Texture buttonHoverTexture;
	sf::Sprite buttonSprite;

	sf::Vector2f size;

	bool hover;
};