#include "PageSearch.h"

void PageSearch::initBackground()
{
	this->background.setSize(sf::Vector2f((float)window->getSize().x, (float)window->getSize().y));
	this->background.setFillColor(sf::Color(46, 62, 68, 255));
}

PageSearch::PageSearch(sf::RenderWindow* window, sf::Event* ev, std::deque<Page*>* pages, std::vector<std::string>* dbLocation) : Page(window, ev, pages, dbLocation)
{
	if (!this->pages->empty())
		this->pages->back()->endState();

	this->initBackground();
	this->initGUI();
}

PageSearch::~PageSearch()
{
	for (auto i = this->buttons.begin(); i != this->buttons.end(); i++)
		delete i->second;

	for (auto i = this->labels.begin(); i != this->labels.end(); i++)
		delete i->second;

	for (auto i = this->textboxes.begin(); i != this->textboxes.end(); i++)
		delete i->second;

	delete db;
}

void PageSearch::searchDB()
{
	std::vector<std::pair<std::string, std::string>> data;
	std::string date = "DATE='";

	date += textboxes["TEXTBOX_YEAR"]->getText() + "-";

	// MONTH
	if (textboxes["TEXTBOX_MONTH"]->getText().size() == 1)
		date += "0" + textboxes["TEXTBOX_MONTH"]->getText() + "-";
	else
		date += textboxes["TEXTBOX_MONTH"]->getText() + "-";

	// DAY
	if (textboxes["TEXTBOX_DAY"]->getText().size() == 1)
		date += "0" + textboxes["TEXTBOX_DAY"]->getText() + " ";
	else
		date += textboxes["TEXTBOX_DAY"]->getText() + " ";

	// HOUR
	if (textboxes["TEXTBOX_HOUR"]->getText().size() == 1)
		date += "0" + textboxes["TEXTBOX_HOUR"]->getText() + ":";
	else
		date += textboxes["TEXTBOX_HOUR"]->getText() + ":";

	// MINUTE
	if (textboxes["TEXTBOX_MINUTE"]->getText().size() == 1)
		date += "0" + textboxes["TEXTBOX_MINUTE"]->getText() + ":";
	else
		date += textboxes["TEXTBOX_MINUTE"]->getText() + ":";

	// SECOND
	if (textboxes["TEXTBOX_SECOND"]->getText().size() == 1)
		date += "0" + textboxes["TEXTBOX_SECOND"]->getText() + "'";
	else
		date += textboxes["TEXTBOX_SECOND"]->getText() + "'";
	
	// Makes sure that the database input end with ".db"
	if(dbLocation->at(0).size() >= 3)
		if (dbLocation->at(0)[dbLocation->at(0).size() - 1] == 'b' &&
			dbLocation->at(0)[dbLocation->at(0).size() - 2] == 'd' &&
			dbLocation->at(0)[dbLocation->at(0).size() - 3] == '.')
		{
			db->selectData(dbLocation->at(0).c_str(), data, dbLocation->at(1).c_str(), date);
		}
		else
			std::cerr << "Error: Invalid input, searchDB()" << std::endl;

	// set textboxes
	if (!data.empty())
	{
		this->textboxes["TEXTBOX_TEMP"]->setText(data[2].second);
		this->textboxes["TEXTBOX_LUMI"]->setText(data[3].second);
		this->textboxes["TEXTBOX_AHUM"]->setText(data[4].second);
		this->textboxes["TEXTBOX_SHUM"]->setText(data[5].second);
	}
	else
	{
		this->textboxes["TEXTBOX_TEMP"]->setText("Not found");
		this->textboxes["TEXTBOX_LUMI"]->setText("Not found");
		this->textboxes["TEXTBOX_AHUM"]->setText("Not found");
		this->textboxes["TEXTBOX_SHUM"]->setText("Not found");
	}
}

void PageSearch::endState()
{
	this->quit = true;
}

void PageSearch::initGUI()
{
	this->buttons["BUTTON_SEARCH"] = new gui::Button(265.f, 300.f, 180.f, 25.f, &this->font, "Search", 14, sf::Color::White, sf::Color::White,
		sf::Color::White, sf::Color(36, 52, 62, 255), sf::Color(38, 54, 64, 255), sf::Color(40, 56, 66, 255), sf::Color(34, 50, 60, 255), 1.f);

	this->textboxes["TEXTBOX_DAY"] = new gui::TextBox(364.f, 140.f, 80.f, 20.f, &this->font, true, sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color(36, 52, 62, 255), sf::Color(36, 52, 62, 255), sf::Color(36, 52, 62, 255), sf::Color(40, 56, 66, 255), sf::Color(40, 56, 66, 255), sf::Color(240, 0, 85, 255), 1.f, 2.f);
	this->textboxes["TEXTBOX_MONTH"] = new gui::TextBox(364.f, 165.f, 80.f, 20.f, &this->font, true, sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color(36, 52, 62, 255), sf::Color(36, 52, 62, 255), sf::Color(36, 52, 62, 255), sf::Color(40, 56, 66, 255), sf::Color(40, 56, 66, 255), sf::Color(240, 0, 85, 255), 1.f, 2.f);
	this->textboxes["TEXTBOX_YEAR"] = new gui::TextBox(364.f, 190.f, 80.f, 20.f, &this->font, true, sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color(36, 52, 62, 255), sf::Color(36, 52, 62, 255), sf::Color(36, 52, 62, 255), sf::Color(40, 56, 66, 255), sf::Color(40, 56, 66, 255), sf::Color(240, 0, 85, 255), 1.f, 2.f);
	this->textboxes["TEXTBOX_HOUR"] = new gui::TextBox(364.f, 215.f, 80.f, 20.f, &this->font, true, sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color(36, 52, 62, 255), sf::Color(36, 52, 62, 255), sf::Color(36, 52, 62, 255), sf::Color(40, 56, 66, 255), sf::Color(40, 56, 66, 255), sf::Color(240, 0, 85, 255), 1.f, 2.f);
	this->textboxes["TEXTBOX_MINUTE"] = new gui::TextBox(364.f, 240.f, 80.f, 20.f, &this->font, true, sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color(36, 52, 62, 255), sf::Color(36, 52, 62, 255), sf::Color(36, 52, 62, 255), sf::Color(40, 56, 66, 255), sf::Color(40, 56, 66, 255), sf::Color(240, 0, 85, 255), 1.f, 2.f);
	this->textboxes["TEXTBOX_SECOND"] = new gui::TextBox(364.f, 265.f, 80.f, 20.f, &this->font, true, sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color(36, 52, 62, 255), sf::Color(36, 52, 62, 255), sf::Color(36, 52, 62, 255), sf::Color(40, 56, 66, 255), sf::Color(40, 56, 66, 255), sf::Color(240, 0, 85, 255), 1.f, 2.f);
	
	this->textboxes["TEXTBOX_TEMP"] = new gui::TextBox(364.f, 345.f, 80.f, 20.f, &this->font, false, sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color(36, 52, 62, 255), sf::Color(36, 52, 62, 255), sf::Color(36, 52, 62, 255), sf::Color(40, 56, 66, 255), sf::Color(40, 56, 66, 255), sf::Color(240, 0, 85, 255), 1.f, 2.f);
	this->textboxes["TEXTBOX_LUMI"] = new gui::TextBox(364.f, 370.f, 80.f, 20.f, &this->font, false, sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color(36, 52, 62, 255), sf::Color(36, 52, 62, 255), sf::Color(36, 52, 62, 255), sf::Color(40, 56, 66, 255), sf::Color(40, 56, 66, 255), sf::Color(240, 0, 85, 255), 1.f, 2.f);
	this->textboxes["TEXTBOX_AHUM"] = new gui::TextBox(364.f, 395.f, 80.f, 20.f, &this->font, false, sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color(36, 52, 62, 255), sf::Color(36, 52, 62, 255), sf::Color(36, 52, 62, 255), sf::Color(40, 56, 66, 255), sf::Color(40, 56, 66, 255), sf::Color(240, 0, 85, 255), 1.f, 2.f);
	this->textboxes["TEXTBOX_SHUM"] = new gui::TextBox(364.f, 420.f, 80.f, 20.f, &this->font, false, sf::Color::White, sf::Color::White, sf::Color::White,
		sf::Color(36, 52, 62, 255), sf::Color(36, 52, 62, 255), sf::Color(36, 52, 62, 255), sf::Color(40, 56, 66, 255), sf::Color(40, 56, 66, 255), sf::Color(240, 0, 85, 255), 1.f, 2.f);


	this->labels["LABEL_DAY"] = new gui::Label(265.f, 140.f, &this->font, "Day", 14, sf::Color::White);
	this->labels["LABEL_MONTH"] = new gui::Label(265.f, 165.f, &this->font, "Month", 14, sf::Color::White);
	this->labels["LABEL_YEAR"] = new gui::Label(265.f, 190.f, &this->font, "Year", 14, sf::Color::White);
	this->labels["LABEL_HOUR"] = new gui::Label(265.f, 215.f, &this->font, "Hours", 14, sf::Color::White);
	this->labels["LABEL_MINUTE"] = new gui::Label(265.f, 240.f, &this->font, "Minutes", 14, sf::Color::White);
	this->labels["LABEL_SECOND"] = new gui::Label(265.f, 265.f, &this->font, "Seconds", 14, sf::Color::White);
	
	this->labels["LABEL_TEMP"] = new gui::Label(265.f, 345.f, &this->font, "Temperature", 14, sf::Color::White);
	this->labels["LABEL_LUMI"] = new gui::Label(265.f, 370.f, &this->font, "Ambient light", 14, sf::Color::White);
	this->labels["LABEL_AHUM"] = new gui::Label(265.f, 395.f, &this->font, "Air humidity", 14, sf::Color::White);
	this->labels["LABEL_SHUM"] = new gui::Label(265.f, 420.f, &this->font, "Soil humidity", 14, sf::Color::White);

	this->labels["LABEL_TEMP_UNIT"] = new gui::Label(454.f, 345.f, &this->font, "[ °C ]", 13, sf::Color::White);
	this->labels["LABEL_LUMI_UNIT"] = new gui::Label(454.f, 370.f, &this->font, "[ mW/cm2 ]", 13, sf::Color::White);
	this->labels["LABEL_AHUM_UNIT"] = new gui::Label(454.f, 395.f, &this->font, "[ % ]", 13, sf::Color::White);
	this->labels["LABEL_SHUM_UNIT"] = new gui::Label(454.f, 420.f, &this->font, "[ % ]", 13, sf::Color::White);
}

void PageSearch::updateGUI()
{
	for (auto &i : this->buttons)
		i.second->update(this->mousePositionView);

	for (auto &i : this->textboxes)
		i.second->update(this->mousePositionView);

	if (this->buttons["BUTTON_SEARCH"]->isReleased())
		this->searchDB();
}

// Called from pollEvents() in Application
void PageSearch::updateInput()
{
	for (auto &i : this->buttons)
		i.second->updateEvent(this->ev, this->mousePositionView);

	for (auto &i : this->textboxes)
		i.second->updateText(this->ev);
}


void PageSearch::update()
{
	this->checkQuit();
	this->updateMousePositions();
	this->updateGUI();
}

void PageSearch::renderGUI(sf::RenderTarget * target)
{
	for (auto &i : this->buttons)
		i.second->render(target);

	for (auto &i : this->labels)
		i.second->render(target);

	for (auto &i : this->textboxes)
		i.second->render(target);
}

void PageSearch::render(sf::RenderTarget * target)
{
	if (!target)
		target = this->window;
	target->clear();
	target->draw(this->background);
	this->renderGUI(target);
}
