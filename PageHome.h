/************************************************************************************
 * @file PageHome.h
 *
 * @brief Displays graphs of temperature, luminosity air and soil humidity
 *
 * @author Vladimir Milivojevic
 *
 ************************************************************************************/

#ifndef PAGE_HOME_H
#define PAGE_HOME_H

#include "Page.h"
#include "Database.h"

class PageHome :
	public Page
{
private:
	const int DATA_COUNT = 20;

	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, gui::Label*> labels;
	std::map<std::string, gui::Graph*> graphs;
	std::vector<float> Y1, Y2, Y3, Y4;
	int lastIndex;

	sf::RectangleShape background;
	sf::Clock clock;
	sf::Time time;

	Database* db;

	void initBackground();
	void initDB();
public:

	PageHome(sf::RenderWindow* window, sf::Event* ev, std::deque<Page*>* pages, std::vector<std::string>* dbLocation);
	virtual ~PageHome();

	void endState();
	void loadDatabaseData();
	void initGUI();
	void updateGUI();
	void updateInput();	// Called from pollEvents() in Application
	void updateData();
	void update();
	void renderGUI(sf::RenderTarget * target);
	void render(sf::RenderTarget* target = nullptr);
};
#endif