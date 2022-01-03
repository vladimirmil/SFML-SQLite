#include "PageDBSetup.h"

void PageDBSetup::initBackground()
{
	this->background.setSize(sf::Vector2f((float)window->getSize().x, (float)window->getSize().y));
	this->background.setFillColor(sf::Color(46, 62, 68, 255));
}

PageDBSetup::PageDBSetup(sf::RenderWindow* window, sf::Event* ev, std::deque<Page*>* pages, std::vector<std::string>* dbLocation) : Page(window, ev, pages, dbLocation)
{
	if (!this->pages->empty())
		this->pages->back()->endState();

	this->initBackground();
	this->initGUI();
}

PageDBSetup::~PageDBSetup()
{
	for (auto i = this->buttons.begin(); i != this->buttons.end(); i++)
		delete i->second;

	for (auto i = this->labels.begin(); i != this->labels.end(); i++)
		delete i->second;

	for (auto i = this->textboxes.begin(); i != this->textboxes.end(); i++)
		delete i->second;

	delete db;
}

void PageDBSetup::setDB()
{
	dbLocation->at(0) = this->textboxes["TEXTBOX_DB_URL"]->getText();
	dbLocation->at(1) = this->textboxes["TEXTBOX_DB_TABLE"]->getText();
	dbLocation->at(2) = this->textboxes["TEXTBOX_UPDATE_TIME"]->getText();
}

void PageDBSetup::endState()
{
	this->quit = true;
}

void PageDBSetup::initGUI()
{
	this->buttons["BUTTON_OK"] = new gui::Button(364.f, 218.f, 80.f, 25.f, &this->font, "Ok", 14, sf::Color::White, sf::Color::White, 
		sf::Color::White, sf::Color(36, 52, 62, 255), sf::Color(38, 54, 64, 255), sf::Color(40, 56, 66, 255), sf::Color(34, 50, 60, 255), 1.f);
	this->buttons["BUTTON_CLEAR"] = new gui::Button(874.f, 138.f, 55.f, 25.f, &this->font, "Clear", 14, sf::Color::White, sf::Color::White,
		sf::Color::White, sf::Color(36, 52, 62, 255), sf::Color(38, 54, 64, 255), sf::Color(40, 56, 66, 255), sf::Color(34, 50, 60, 255), 1.f);
	
	this->textboxes["TEXTBOX_DB_URL"] = new gui::TextBox(364.f, 140.f, 500.f, 20.f, &this->font, true, sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color(36, 52, 62, 255), sf::Color(36, 52, 62, 255), sf::Color(36, 52, 62, 255), sf::Color(40, 56, 66, 255), sf::Color(40, 56, 66, 255), sf::Color(240, 0, 85, 255), 1.f, 2.f);
	this->textboxes["TEXTBOX_DB_TABLE"] = new gui::TextBox(364.f, 165.f, 250.f, 20.f, &this->font, true, sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color(36, 52, 62, 255), sf::Color(36, 52, 62, 255), sf::Color(36, 52, 62, 255), sf::Color(40, 56, 66, 255), sf::Color(40, 56, 66, 255), sf::Color(240, 0, 85, 255), 1.f, 2.f);
	this->textboxes["TEXTBOX_UPDATE_TIME"] = new gui::TextBox(364.f, 190.f, 100.f, 20.f,&this->font, true, sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color(36, 52, 62, 255), sf::Color(36, 52, 62, 255), sf::Color(36, 52, 62, 255), sf::Color(40, 56, 66, 255), sf::Color(40, 56, 66, 255), sf::Color(240, 0, 85, 255), 1.f, 2.f);

	this->labels["TEXTBOX_DB_URL"] = new gui::Label(265.f, 140.f, &this->font, "Database", 14, sf::Color::White);
	this->labels["TEXTBOX_DB_TABLE"] = new gui::Label(265.f, 165.f, &this->font, "Table", 14, sf::Color::White);
	this->labels["TEXTBOX_UPDATE_TIME"] = new gui::Label(265.f, 190.f, &this->font, "Update [ s ]", 14, sf::Color::White);
	
	this->textboxes["TEXTBOX_DB_URL"]->setText(dbLocation->at(0));
	this->textboxes["TEXTBOX_DB_TABLE"]->setText(dbLocation->at(1));
	this->textboxes["TEXTBOX_UPDATE_TIME"]->setText(dbLocation->at(2));
}

void PageDBSetup::updateGUI()
{
	for (auto &i : this->buttons)
		i.second->update(this->mousePositionView);

	for (auto &i : this->textboxes)
		i.second->update(this->mousePositionView);

	if (this->buttons["BUTTON_OK"]->isReleased())
		setDB();

	if (this->buttons["BUTTON_CLEAR"]->isReleased())
	{
		this->textboxes["TEXTBOX_DB_URL"]->setText("");
		this->textboxes["TEXTBOX_DB_URL"]->updateCursor();
	}
}

// Called from pollEvents() in Application
void PageDBSetup::updateInput()
{
	for (auto &i : this->buttons)
		i.second->updateEvent(this->ev, this->mousePositionView);

	for (auto &i : this->textboxes)
		i.second->updateText(this->ev);
}


void PageDBSetup::update()
{
	this->checkQuit();
	this->updateMousePositions();
	this->updateGUI();
}

void PageDBSetup::renderGUI(sf::RenderTarget * target)
{

	for (auto &i : this->buttons)
		i.second->render(target);

	for (auto &i : this->labels)
		i.second->render(target);

	for (auto &i : this->textboxes)
		i.second->render(target);

}

void PageDBSetup::render(sf::RenderTarget * target)
{
	if (!target)
		target = this->window;
	target->clear();
	target->draw(this->background);
	this->renderGUI(target);
}
