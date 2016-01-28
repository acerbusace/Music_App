#include "Button.hpp"

Button::Button() {
	hover = false;
}

Button::~Button() {

}

void Button::init(std::string buttonTexturePath, std::string buttonHoverTexturePath, sf::Vector2f pos, sf::Vector2f size) {
	buttonTexture.loadFromFile(buttonTexturePath);
	buttonHoverTexture.loadFromFile(buttonHoverTexturePath);
	buttonTexture.setSmooth(true);
	buttonHoverTexture.setSmooth(true);

	buttonTexture.getSize();

	buttonSprite.setTexture(buttonTexture);
	buttonSprite.setPosition(sf::Vector2f(pos.x, pos.y));

	this->size.x = size.x;
	this->size.y = size.y;

	buttonSprite.setScale(sf::Vector2f(size.x / buttonTexture.getSize().x, size.y / buttonTexture.getSize().y));
}

bool Button::collision(sf::Vector2i pos) {
	if (pos.x > buttonSprite.getPosition().x && pos.x < buttonSprite.getPosition().x + size.x && pos.y > buttonSprite.getPosition().y && pos.y < buttonSprite.getPosition().y + size.y) {
		buttonSprite.setTexture(buttonHoverTexture);
		return true;
	}
	buttonSprite.setTexture(buttonTexture);
	return false;
}

sf::Sprite Button::getButton() {
	return buttonSprite;
}