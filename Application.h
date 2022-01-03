/************************************************************************************
 * @file Application.h
 *
 * @brief Everything gets called from here
 *
 * @author Vladimir Milivojevic
 *
 ************************************************************************************/

#ifndef APPLICATION_H
#define APPLICATION_H

#include "Page.h"
#include "Sidebar.h"
#include "PageDBSetup.h"
#include "PageHome.h"
#include "PageTemperature.h"
#include "PageLight.h"
#include "PageAirHum.h"
#include "PageSoilHum.h"

constexpr auto WINDOW_WIDTH = 1200;
constexpr auto WINDOW_HEIGHT = 700;
constexpr auto FRAMERATE_LIMIT = 60;

class Application
{
private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	sf::Font font;
	sf::Vector2f mousePositionView;
	std::deque<Page*> pages;
	std::vector<std::string> dbLocation;
	
	Titlebar* titlebar;
	Sidebar* sidebar;
	
	bool hasFocus;
	void initVariables();
	void initWindow();
	void initStates();
	void initFonts();
	void initMenu();
public:
	Application();
	virtual ~Application();

	const bool isRunning() const;

	void pollEvents();
	//void updateMenu();
	void update();
	void render();
	void run();

};

#endif



