/************************************************************************************
 * @file PageSearch.h
 *
 * @brief Finds data for specific date
 *
 * @author Vladimir Milivojevic
 *
 ************************************************************************************/

#ifndef PAGE_SEARCH_H
#define PAGE_SEARCH_H

#include "Page.h"
#include "Database.h"

class PageSearch :
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
		PageSearch(sf::RenderWindow* window, sf::Event* ev, std::deque<Page*>* pages, std::vector<std::string>* dbLocation);
		virtual ~PageSearch();

		void searchDB();
		void endState();
		void initGUI();
		void updateGUI();
		void updateInput();	// Called from pollEvents() in Application
		void update();
		void renderGUI(sf::RenderTarget * target);
		void render(sf::RenderTarget* target = nullptr);
};
#endif


