#include "PageSoilHum.h"

void PageSoilHum::initBackground()
{
	this->background.setSize(sf::Vector2f((float)window->getSize().x, (float)window->getSize().y));
	this->background.setFillColor(sf::Color(46, 62, 68, 255));
}

void PageSoilHum::initDB()
{
	// Makes sure that the database input ends with ".db"
	if (dbLocation->at(0).size() >= 3)
		if (dbLocation->at(0)[dbLocation->at(0).size() - 1] == 'b' &&
			dbLocation->at(0)[dbLocation->at(0).size() - 2] == 'd' &&
			dbLocation->at(0)[dbLocation->at(0).size() - 3] == '.')
		{
			this->lastIndex = db->getCount(dbLocation->at(0).c_str(), dbLocation->at(1).c_str());
			this->loadDatabaseData();
		}
		else
			std::cerr << "Error: Invalid input" << std::endl;
}

PageSoilHum::PageSoilHum(sf::RenderWindow* window, sf::Event* ev, std::deque<Page*>* pages, std::vector<std::string>* dbLocation) : Page(window, ev, pages, dbLocation)
{
	if (!this->pages->empty())
		this->pages->back()->endState();

	this->initBackground();
	this->initDB();
	this->initGUI();
	
}

PageSoilHum::~PageSoilHum()
{
	for (auto i = this->buttons.begin(); i != this->buttons.end(); i++)
		delete i->second;

	for (auto i = this->labels.begin(); i != this->labels.end(); i++)
		delete i->second;

	for (auto i = this->graphs.begin(); i != this->graphs.end(); i++)
		delete i->second;

	delete db;
}

void PageSoilHum::endState()
{
	this->quit = true;
}

void PageSoilHum::loadDatabaseData()
{
	std::vector<std::pair<std::string, std::string>> data;
	if (db->getCount(dbLocation->at(0).c_str(), dbLocation->at(1).c_str()) != -1 &&
		db->getCount(dbLocation->at(0).c_str(), dbLocation->at(1).c_str()) >= this->DATA_COUNT)
	{
		for (int i = db->getCount(dbLocation->at(0).c_str(), dbLocation->at(1).c_str()) - this->DATA_COUNT; i <= db->getCount(dbLocation->at(0).c_str(), dbLocation->at(1).c_str()); i++)
		{
			std::string temp = "ID=";
			temp.append(std::to_string(i));
			db->selectData(dbLocation->at(0).c_str(), data, dbLocation->at(1).c_str(), temp);
			this->strX.push_back(data[0].second);
			this->Y.push_back(std::stof(data[5].second));
		}
	}
}

void PageSoilHum::initGUI()
{
	this->graphs["GRAPH"] = new gui::Graph(&this->font, "Soil humidity [ % ]", this->strX, this->Y, 100.f, 0.f, 235.f, 60.f, 934.f, 620.f, 20.f);
	this->graphs["GRAPH"]->setGraphColor(sf::Color(240, 0, 85, 255), sf::Color(240, 0, 85, 255));
}

void PageSoilHum::updateGUI()
{
	for (auto &i : this->buttons)
		i.second->update(this->mousePositionView);
}

// Called from pollEvents() in Application
void PageSoilHum::updateInput()
{
	for (auto &i : this->buttons)
		i.second->updateEvent(this->ev, this->mousePositionView);

	for (auto &i : this->graphs)
		i.second->updateEvent(this->ev, this->mousePositionView);
}

void PageSoilHum::updateData()
{
	this->time = clock.getElapsedTime();

	std::vector<std::pair<std::string, std::string>> data;
	std::string temp = dbLocation->at(2);
	std::string id = "ID=";

	std::replace(temp.begin(), temp.end(), ',', '.');
	// Id of newest data to be used in db->select()
	id.append(std::to_string(this->lastIndex + 1));

	try
	{
		if (this->time.asSeconds() >= std::stof(temp))
		{
			// Look for new data, set data
			db->selectData(dbLocation->at(0).c_str(), data, dbLocation->at(1).c_str(), id);
			// If data is empty, no new data exists
			if (data.empty())
				this->clock.restart();
			else
			{
				this->graphs["GRAPH"]->updatePoints(std::stof(data[5].second));
				this->lastIndex++;
				this->clock.restart();
			}
		}
	}
	catch (...)
	{
		std::cerr << "Error: updateData(), Temperature page" << std::endl;
	}
}

void PageSoilHum::update()
{
	this->checkQuit();
	this->updateMousePositions();
	this->updateGUI();
	this->updateData();
}

void PageSoilHum::renderGUI(sf::RenderTarget * target)
{

	for (auto &i : this->buttons)
		i.second->render(target);

	for (auto &i : this->labels)
		i.second->render(target);

	for (auto &i : this->graphs)
		i.second->render(target);
}

void PageSoilHum::render(sf::RenderTarget * target)
{
	if (!target)
		target = this->window;
	target->clear();
	target->draw(this->background);
	this->renderGUI(target);
}
