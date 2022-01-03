#include "Titlebar.h"

Titlebar::Titlebar(sf::RenderWindow* window, sf::Font * font)
{
	this->isPressed = false;

	this->shape.setSize(sf::Vector2f((float)window->getSize().x, 40));
	this->shape.setPosition(sf::Vector2f(0, 0));
	this->shape.setFillColor(sf::Color::Color(36, 48, 57, 255));
	this->shape.setOutlineThickness(1);
	this->shape.setOutlineColor(sf::Color(50, 50, 61, 255));

	this->font = font;
	this->title.setFont(*this->font);

	this->exitButton = new gui::Button(this->shape.getSize().x - 45, 5, 30.f, 30.f, this->font, "X", 
		sf::Color(36, 52, 62, 255), sf::Color(240, 0, 85, 255), sf::Color(240, 0, 95, 255), sf::Color(34, 50, 60, 255), 1.f);
}

Titlebar::Titlebar(sf::RenderWindow* window, sf::Font * font, std::string title)
{
	this->isPressed = false;

	this->shape.setSize(sf::Vector2f((float)window->getSize().x, 40));
	this->shape.setPosition(sf::Vector2f(0, 0));
	this->shape.setFillColor(sf::Color::Color(33, 33, 33, 255));

	this->font = font;
	this->title.setFont(*this->font);
	this->title.setCharacterSize(12);
	this->title.setString(title);
	this->title.setFillColor(sf::Color::White);
	this->title.setPosition((float)window->getSize().x / 2.f - (int)this->title.getGlobalBounds().width / 2, 15);

	this->exitButton = new gui::Button(this->shape.getSize().x - 45, 5, 30.f, 30.f, this->font, "X ", sf::Color::Color(33, 33, 33, 255),
		sf::Color::Color(245, 54, 5, 255), sf::Color::Color(213, 47, 4, 255), sf::Color::Black, 0.f);

}


Titlebar::~Titlebar()
{
	delete this->exitButton;
}

void Titlebar::setPressed(bool value)
{
	this->isPressed = value;
}

const bool Titlebar::getPressed()
{
	if (this->isPressed)
		return true;
	return false;
}

// Called from pollEvents() in Application
void Titlebar::updateInput(sf::Event * ev, sf::Vector2f mousePositionView)
{
	this->exitButton->updateEvent(ev, mousePositionView);
}

// Called from pollEvents() in Application
void Titlebar::updateMouse(sf::RenderWindow* window, sf::Event * ev, sf::Vector2f mousePosition)
{
	if (this->shape.getGlobalBounds().contains(mousePosition) && ev->mouseButton.button == sf::Mouse::Left)
	{
		this->setPressed(true);
		this->grabbedOffset = window->getPosition() - sf::Mouse::getPosition();
	}
}

// Called from pollEvents() in Application
void Titlebar::updateWindowPosition(sf::RenderWindow* window)
{
	if (this->getPressed())
		window->setPosition(sf::Mouse::getPosition() + this->grabbedOffset);
}

void Titlebar::update(sf::Vector2f mousePosition, sf::RenderWindow* window)
{
	this->exitButton->update(mousePosition);
	
	if (this->exitButton->isReleased())
		window->close();
}

void Titlebar::render(sf::RenderTarget * target)
{
	target->draw(this->shape);
	target->draw(this->title);
	this->exitButton->render(target);
}
