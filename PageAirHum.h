/************************************************************************************
 * @file PageAirHum.h
 *
 * @brief Displays graph of air humidity
 *
 * @author Vladimir Milivojevic
 *
 ************************************************************************************/

#ifndef PAGE_AIR_HUM_H
#define PAGE_AIR_HUM_H

#include "Page.h"
#include "Database.h"



class PageAirHum :
	public Page
{
private:
	const int DATA_COUNT = 50;

	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, gui::Label*> labels;
	std::map<std::string, gui::Graph*> graphs;
	std::vector<float> Y;
	std::vector<std::string> strX;
	int lastIndex;

	sf::RectangleShape background;
	sf::Clock clock;
	sf::Time time;

	Database* db;

	void initBackground();
	void initDB();
public:

	PageAirHum(sf::RenderWindow* window, sf::Event* ev, std::deque<Page*>* pages, std::vector<std::string>* dbLocation);
	virtual ~PageAirHum();

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

