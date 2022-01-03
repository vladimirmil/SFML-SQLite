/************************************************************************************
 * @file PageSoilHum.h
 *
 * @brief Displays graph of Soil Humidity
 *
 * @author Vladimir Milivojevic
 *
 ************************************************************************************/

#ifndef PAGE_SOIL_HUM_H
#define PAGE_SOIL_HUM_H

#include "Page.h"
#include "Database.h"



class PageSoilHum :
	public Page
{
private:
	const int DATA_COUNT = 50;

	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, gui::Label*> labels;
	std::map<std::string, gui::Graph*> graphs;
	std::vector<float> Y;
	int lastIndex;

	sf::RectangleShape background;
	sf::Clock clock;
	sf::Time time;

	Database* db;

	void initBackground();
	void initDB();
public:

	PageSoilHum(sf::RenderWindow* window, sf::Event* ev, std::deque<Page*>* pages, std::vector<std::string>* dbLocation);
	virtual ~PageSoilHum();

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

