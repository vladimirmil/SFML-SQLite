#include "PageHome.h"

void PageHome::initBackground()
{
	this->background.setSize(sf::Vector2f((float)window->getSize().x, (float)window->getSize().y));
	this->background.setFillColor(sf::Color(46, 62, 68, 255));
}

void PageHome::initDB()
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

PageHome::PageHome(sf::RenderWindow* window, sf::Event* ev, std::deque<Page*>* pages, std::vector<std::string>* dbLocation) : Page(window, ev, pages, dbLocation)
{
	if (!this->pages->empty())
		this->pages->back()->endState();

	this->initBackground();
	this->initDB();
	this->initGUI();
}

PageHome::~PageHome()
{
	for (auto i = this->buttons.begin(); i != this->buttons.end(); i++)
		delete i->second;

	for (auto i = this->labels.begin(); i != this->labels.end(); i++)
		delete i->second;

	for (auto i = this->graphs.begin(); i != this->graphs.end(); i++)
		delete i->second;
	
	delete db;
}

void PageHome::endState()
{
	this->quit = true;
}

void PageHome::loadDatabaseData()
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
			this->Y1.push_back(std::stof(data[2].second));
			this->Y2.push_back(std::stof(data[3].second));
			this->Y3.push_back(std::stof(data[4].second));
			this->Y4.push_back(std::stof(data[5].second));
		}
	}
}

void PageHome::initGUI()
{
	
	this->graphs["GRAPH_TEMP"] = new gui::Graph(&this->font, "Temperature [ �C ]", this->strX, this->Y1, 60.f, -20.f, 235.f, 60.f, 460.f, 300.f, 20.f);
	this->graphs["GRAPH_LUMI"] = new gui::Graph(&this->font, "Ambient light intensity [ mW/cm2 ]", this->strX, this->Y2, 300.f, 0.f, 710.f, 60.f, 459.5f, 300.f, 20.f);
	this->graphs["GRAPH_AHUM"] = new gui::Graph(&this->font, "Air humidity [ % ]", this->strX, this->Y3, 100.f, 0.f, 235.f, 380.f, 460.f, 300.f, 20.f);
	this->graphs["GRAPH_SHUM"] = new gui::Graph(&this->font, "Soil humidity [ % ]", this->strX, this->Y4, 100.f, 0.f, 710.f, 380.f, 459.5f, 300.f, 20.f);
	
	this->graphs["GRAPH_TEMP"]->setGraphColor(sf::Color(240, 0, 85, 255), sf::Color(240, 0, 85, 255));
	this->graphs["GRAPH_LUMI"]->setGraphColor(sf::Color(240, 0, 85, 255), sf::Color(240, 0, 85, 255));
	this->graphs["GRAPH_AHUM"]->setGraphColor(sf::Color(240, 0, 85, 255), sf::Color(240, 0, 85, 255));
	this->graphs["GRAPH_SHUM"]->setGraphColor(sf::Color(240, 0, 85, 255), sf::Color(240, 0, 85, 255));
}

void PageHome::updateGUI()
{
	for (auto &i : this->buttons)
		i.second->update(this->mousePositionView);
}

// Called from pollEvents() in Application
void PageHome::updateInput()
{
	for (auto &i : this->buttons)
		i.second->updateEvent(this->ev, this->mousePositionView);

	for (auto &i : this->graphs)
		i.second->updateEvent(this->ev, this->mousePositionView);
}


void PageHome::updateData()
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
				this->graphs["GRAPH_TEMP"]->updatePoints(std::stof(data[2].second));
				this->graphs["GRAPH_LUMI"]->updatePoints(std::stof(data[3].second));
				this->graphs["GRAPH_AHUM"]->updatePoints(std::stof(data[4].second));
				this->graphs["GRAPH_SHUM"]->updatePoints(std::stof(data[5].second));
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

void PageHome::update()
{
	this->checkQuit();
	this->updateMousePositions();
	this->updateGUI();
	this->updateData();

}

void PageHome::renderGUI(sf::RenderTarget * target)
{

	for (auto &i : this->buttons)
		i.second->render(target);

	for (auto &i : this->labels)
		i.second->render(target);

	for (auto &i : this->graphs)
		i.second->render(target);
}

void PageHome::render(sf::RenderTarget * target)
{
	if (!target)
		target = this->window;
	target->clear();
	target->draw(this->background);
	this->renderGUI(target);
}
