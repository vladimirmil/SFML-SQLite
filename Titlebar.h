/************************************************************************************
 * @file Titlebar.h
 *
 * @brief Titlebar with drag feature and an exit button
 *
 * @author Vladimir Milivojevic
 *
 ************************************************************************************/

#ifndef TITLEBAR_H
#define TITLEBAR_H

#include "Gui.h"

class Titlebar
{
private:
	gui::Button* exitButton;
	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text title;
	sf::Vector2i grabbedOffset;
	bool isPressed;

public:
	Titlebar(sf::RenderWindow* window, sf::Font* font);
	Titlebar(sf::RenderWindow* window, sf::Font* font, std::string title);
	~Titlebar();


	void setPressed(bool value);
	const bool getPressed();
	void updateInput(sf::Event * ev, sf::Vector2f mousePositionView); // Called from pollEvents() in Application
	void updateMouse(sf::RenderWindow* window, sf::Event* ev, sf::Vector2f mousePosition); // Called from pollEvents() in Application
	void updateWindowPosition(sf::RenderWindow* window); // Called from pollEvents() in Application
	void update(sf::Vector2f mousePosition, sf::RenderWindow* window);
	void render(sf::RenderTarget* target);
};

#endif // !TITLEBAR_H



