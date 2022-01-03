/************************************************************************************
 * @file Page.h
 *
 * @brief Base class for every page
 *
 * @author Vladimir Milivojevic
 *
 ************************************************************************************/

#ifndef PAGE_H
#define PAGE_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <stack>


#include "Gui.h"
#include "Titlebar.h"


class Page
{
protected:
	std::deque<Page*>* pages;
	std::vector<std::string>* dbLocation;

	sf::RenderWindow* window;
	sf::Event* ev;
	sf::Vector2f mousePositionView;
	sf::Font font;
	
	bool quit;
public:
	Page(sf::RenderWindow* window, sf::Event* ev, std::deque<Page*>* pages, std::vector<std::string>* dbLocation);
	virtual ~Page();

	const bool& getQuit() const;
	void setQuit(bool quit);

	void initFonts();

	virtual void checkQuit();
	virtual void updateMousePositions();

	virtual void endState() = 0;
	virtual void updateInput() = 0;
	virtual void update() = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

#endif



