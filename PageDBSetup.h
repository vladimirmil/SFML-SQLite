/************************************************************************************
 * @file PageDBSetup.h
 *
 * @brief Page for setting up database info
 *
 * @author Vladimir Milivojevic
 *
 ************************************************************************************/

#ifndef PAGE_DB_SETUP_H
#define PAGE_DB_SETUP_H

#include "Page.h"
#include "Database.h"

class PageDBSetup :
	public Page
{
private:
	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, gui::Label*> labels;
	std::map<std::string, gui::TextBox*> textboxes;

	sf::RectangleShape background;

	Database* db;

	void initBackground();
public:

	PageDBSetup(sf::RenderWindow* window, sf::Event* ev, std::deque<Page*>* pages, std::vector<std::string>* dbLocation);
	virtual ~PageDBSetup();

	void setDB();

	void endState();
	void initGUI();
	void updateGUI();
	void updateInput();	// Called from pollEvents() in Application
	void update();
	void renderGUI(sf::RenderTarget * target);
	void render(sf::RenderTarget* target = nullptr);
};
#endif

