#include "Page.h"

Page::Page(sf::RenderWindow* window, sf::Event* ev, std::deque<Page*>* pages, std::vector<std::string>* dbLocation)
{
	this->window = window;
	this->ev = ev;
	this->quit = false;
	this->initFonts();
	this->pages = pages;
	this->dbLocation = dbLocation;
}

Page::~Page()
{
}

const bool & Page::getQuit() const
{
	return this->quit;
}

void Page::setQuit(bool quit)
{
	this->quit = quit;
}

void Page::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Roboto-Regular.ttf"))
	{
		throw("ERROR: Coudld not load font");
	}
}

void Page::checkQuit()
{
}

void Page::updateMousePositions()
{
	//this->mousePositionScreen = sf::Mouse::getPosition();
	//this->mousePositionWindow = sf::Mouse::getPosition(*this->window);
	this->mousePositionView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}
