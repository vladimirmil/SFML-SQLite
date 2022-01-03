#include "Sidebar.h"

Sidebar::Sidebar(sf::RenderWindow * window, sf::Font* font)
{
	this->window = window;
	this->shape.setSize(sf::Vector2f(200.f, (float)window->getSize().y));
	this->shape.setPosition(sf::Vector2f(0.f, 0.f));
	this->shape.setFillColor(sf::Color(36, 52, 62, 255));
	this->shape.setOutlineThickness(1);
	this->shape.setOutlineColor(sf::Color(50, 50, 61, 255));
	this->font = *font;

	this->selectedButton.setSize(sf::Vector2f(5.f, 50.f));
	this->selectedButton.setPosition(sf::Vector2f(0, 100.f));
	this->selectedButton.setFillColor(sf::Color(240, 0, 85, 255));


	this->initGUI();
}

Sidebar::~Sidebar()
{
	for (auto i = this->buttons.begin(); i != this->buttons.end(); i++)
		delete i->second;
}

void Sidebar::initGUI()
{
	this->buttons["BUTTON_DBS"] = new gui::Button(0.f, 100.f, this->shape.getSize().x, 50.f, &this->font, 
		"Setup Database", 16, sf::Color::White, sf::Color(240, 0, 85, 255), sf::Color(240, 0, 85, 255), 
		sf::Color(36, 52, 62, 255), sf::Color(38, 54, 64, 255), sf::Color(40, 56, 66, 255), sf::Color::Red, 0.f);

	this->buttons["BUTTON_HOME"] = new gui::Button(0.f, 150.f, this->shape.getSize().x, 50.f, &this->font, 
		"Home", 16, sf::Color::White, sf::Color(240, 0, 85, 255), sf::Color(240, 0, 85, 255), 
		sf::Color(36, 52, 62, 255), sf::Color(38, 54, 64, 255), sf::Color(40, 56, 66, 255), sf::Color::Red, 0.f);

	this->buttons["BUTTON_TEMP"] = new gui::Button(0.f, 200.f, this->shape.getSize().x, 50.f, &this->font, 
		"Temperature", 16, sf::Color::White, sf::Color(240, 0, 85, 255), sf::Color(240, 0, 85, 255), 
		sf::Color(36, 52, 62, 255), sf::Color(38, 54, 64, 255), sf::Color(40, 56, 66, 255), sf::Color::Red, 0.f);

	this->buttons["BUTTON_LUM"] = new gui::Button(0.f, 250.f, this->shape.getSize().x, 50.f, &this->font, 
		"Ambient light", 16, sf::Color::White, sf::Color(240, 0, 85, 255), sf::Color(240, 0, 85, 255), 
		sf::Color(36, 52, 62, 255), sf::Color(38, 54, 64, 255), sf::Color(40, 56, 66, 255), sf::Color::Red, 0.f);

	this->buttons["BUTTON_HUM_AIR"] = new gui::Button(0.f, 300.f, this->shape.getSize().x, 50.f, &this->font, 
		"Air humidity", 16, sf::Color::White, sf::Color(240, 0, 85, 255), sf::Color(240, 0, 85, 255), 
		sf::Color(36, 52, 62, 255), sf::Color(38, 54, 64, 255), sf::Color(40, 56, 66, 255), sf::Color::Red, 0.f);

	this->buttons["BUTTON_HUM_SOIL"] = new gui::Button(0.f, 350.f, this->shape.getSize().x, 50.f, &this->font, 
		"Soil humidity", 16, sf::Color::White, sf::Color(240, 0, 85, 255), sf::Color(240, 0, 85, 255), 
		sf::Color(36, 52, 62, 255), sf::Color(38, 54, 64, 255), sf::Color(40, 56, 66, 255), sf::Color::Red, 0.f);

	this->buttons["BUTTON_SEARCH"] = new gui::Button(0.f, 400.f, this->shape.getSize().x, 50.f, &this->font,
		"Search", 16, sf::Color::White, sf::Color(240, 0, 85, 255), sf::Color(240, 0, 85, 255), 
		sf::Color(36, 52, 62, 255), sf::Color(38, 54, 64, 255), sf::Color(40, 56, 66, 255), sf::Color::Red, 0.f);

	this->buttons["BUTTON_DBS"]->setTextColor(sf::Color(240, 0, 85, 255), sf::Color(240, 0, 85, 255), sf::Color(240, 0, 85, 255));
}

// Called from pollEvents() in Application
void Sidebar::updateInput(sf::Event * ev)
{
	for (auto &i : this->buttons)
		i.second->updateEvent(ev, this->mousePositionView);
}

void Sidebar::updateGUI(std::deque<Page*>* pages, sf::Event * ev, std::vector<std::string>* dbLocation)
{
	for (auto &i : this->buttons)
		i.second->update(this->mousePositionView);

	if (this->buttons["BUTTON_DBS"]->isReleased())
	{
		pages->push_front(new PageDBSetup(this->window, ev, pages, dbLocation));
		this->selectedButton.setPosition(sf::Vector2f(0, this->buttons["BUTTON_DBS"]->getPosition().y));

		for (auto &i : this->buttons)
			i.second->setTextColor(sf::Color::White, sf::Color::White, sf::Color::White);
			//i.second->setIdleTextColor(sf::Color::White);

		this->buttons["BUTTON_DBS"]->setTextColor(sf::Color(240, 0, 85, 255), sf::Color(240, 0, 85, 255), sf::Color(240, 0, 85, 255)); //setIdleTextColor(sf::Color(240, 0, 85, 255));
	}
		
	if (this->buttons["BUTTON_HOME"]->isReleased())
	{
		pages->push_front(new PageHome(this->window, ev, pages, dbLocation));
		this->selectedButton.setPosition(sf::Vector2f(0, this->buttons["BUTTON_HOME"]->getPosition().y));

		for (auto &i : this->buttons)
			i.second->setTextColor(sf::Color::White, sf::Color::White, sf::Color::White);

		this->buttons["BUTTON_HOME"]->setTextColor(sf::Color(240, 0, 85, 255), sf::Color(240, 0, 85, 255), sf::Color(240, 0, 85, 255));
	}
		
	if (this->buttons["BUTTON_TEMP"]->isReleased())
	{
		pages->push_front(new PageTemperature(this->window, ev, pages, dbLocation));
		this->selectedButton.setPosition(sf::Vector2f(0, this->buttons["BUTTON_TEMP"]->getPosition().y));

		for (auto &i : this->buttons)
			i.second->setTextColor(sf::Color::White, sf::Color::White, sf::Color::White);

		this->buttons["BUTTON_TEMP"]->setTextColor(sf::Color(240, 0, 85, 255), sf::Color(240, 0, 85, 255), sf::Color(240, 0, 85, 255));
	}
		
	if (this->buttons["BUTTON_LUM"]->isReleased())
	{
		pages->push_front(new PageLight(this->window, ev, pages, dbLocation));
		this->selectedButton.setPosition(sf::Vector2f(0, this->buttons["BUTTON_LUM"]->getPosition().y));

		for (auto &i : this->buttons)
			i.second->setTextColor(sf::Color::White, sf::Color::White, sf::Color::White);

		this->buttons["BUTTON_LUM"]->setTextColor(sf::Color(240, 0, 85, 255), sf::Color(240, 0, 85, 255), sf::Color(240, 0, 85, 255));
	}
		
	if (this->buttons["BUTTON_HUM_AIR"]->isReleased())
	{
		pages->push_front(new PageAirHum(this->window, ev, pages, dbLocation));
		this->selectedButton.setPosition(sf::Vector2f(0, this->buttons["BUTTON_HUM_AIR"]->getPosition().y));

		for (auto &i : this->buttons)
			i.second->setTextColor(sf::Color::White, sf::Color::White, sf::Color::White);

		this->buttons["BUTTON_HUM_AIR"]->setTextColor(sf::Color(240, 0, 85, 255), sf::Color(240, 0, 85, 255), sf::Color(240, 0, 85, 255));
	}
		
	if (this->buttons["BUTTON_HUM_SOIL"]->isReleased())
	{
		pages->push_front(new PageSoilHum(this->window, ev, pages, dbLocation));
		this->selectedButton.setPosition(sf::Vector2f(0, this->buttons["BUTTON_HUM_SOIL"]->getPosition().y));

		for (auto &i : this->buttons)
			i.second->setTextColor(sf::Color::White, sf::Color::White, sf::Color::White);

		this->buttons["BUTTON_HUM_SOIL"]->setTextColor(sf::Color(240, 0, 85, 255), sf::Color(240, 0, 85, 255), sf::Color(240, 0, 85, 255));
	}

	if (this->buttons["BUTTON_SEARCH"]->isReleased())
	{
		pages->push_front(new PageSearch(this->window, ev, pages, dbLocation));
		this->selectedButton.setPosition(sf::Vector2f(0, this->buttons["BUTTON_SEARCH"]->getPosition().y));

		for (auto &i : this->buttons)
			i.second->setTextColor(sf::Color::White, sf::Color::White, sf::Color::White);

		this->buttons["BUTTON_SEARCH"]->setTextColor(sf::Color(240, 0, 85, 255), sf::Color(240, 0, 85, 255), sf::Color(240, 0, 85, 255));
	}		
}

void Sidebar::update(std::deque<Page*>* pages, sf::Vector2f mousePositionView, sf::Event * ev, std::vector<std::string>* dbLocation)
{
	this->mousePositionView = mousePositionView;
	this->updateGUI(pages, ev, dbLocation);
}

void Sidebar::renderGUI(sf::RenderTarget * target)
{
	for (auto &i : this->buttons)
		i.second->render(target);
}

void Sidebar::render(sf::RenderTarget * target)
{
	target->draw(this->shape);
	
	this->renderGUI(target);
	target->draw(this->selectedButton);
}
