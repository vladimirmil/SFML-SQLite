/************************************************************************************
 * @file Sidebar.h
 *
 * @brief Navigation
 *
 * @author Vladimir Milivojevic
 *
 ************************************************************************************/

#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <stack>
#include "Gui.h"
#include "Page.h"
#include "PageDBSetup.h"
#include "PageHome.h"
#include "PageTemperature.h"
#include "PageLight.h"
#include "PageAirHum.h"
#include "PageSoilHum.h"
#include "PageSearch.h"

class Sidebar
{
private:
	sf::RenderWindow* window;
	sf::Font font;
	sf::RectangleShape shape, selectedButton;
	sf::Vector2f mousePositionView;

	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, gui::Label*> labels;
public:
	Sidebar(sf::RenderWindow* window, sf::Font* font);
	virtual ~Sidebar();

	void initGUI();
	void updateInput(sf::Event * ev);
	//void updateMouseMov();
	void updateGUI(std::deque<Page*>* pages, sf::Event * ev, std::vector<std::string>* dbLocation);
	void update(std::deque<Page*>* pages, sf::Vector2f mousePositionView, sf::Event * ev, std::vector<std::string>* dbLocation);
	void renderGUI(sf::RenderTarget * target);
	void render(sf::RenderTarget* target);
};

#endif



