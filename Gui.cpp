#include "Gui.h"

/**************************************************************************
********* BUTTON **********************************************************
**************************************************************************/

void gui::Button::initVariables(sf::Color idleColor, sf::Color hoverColor, sf::Color pressedColor, sf::Color outlineColor, float outlineThickness)
{
	this->isButtonReleased = false;
	this->isImage = false;
	this->buttonState = this->BUTTON_IDLE;
	this->textSize = 14;

	this->outlineColor = outlineColor;
	this->outlineThickness = outlineThickness;

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->pressedColor = pressedColor;

	this->idleTextColor = sf::Color::White;
	this->hoverTextColor = sf::Color::White;
	this->pressedTextColor = sf::Color::White;
}

void gui::Button::initShape(float x, float y, float width, float height)
{
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(this->idleColor);
	this->shape.setOutlineColor(this->outlineColor);
	this->shape.setOutlineThickness(this->outlineThickness);
}

void gui::Button::initText(sf::Font * font, std::string text)
{
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(this->idleTextColor);
	this->text.setCharacterSize(this->textSize);
	this->text.setPosition(
		(int)(this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - (this->text.getGlobalBounds().width / 2.f)),
		(int)(this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - (this->text.getGlobalBounds().height / 2.f) - 3)
	);
}

void gui::Button::initTexture(std::string textureLocationIdle, std::string textureLocationHover, std::string textureLocationPressed)
{
	if (!this->textureIdle.loadFromFile(textureLocationIdle))
		throw("ERROR: Coudld not load image");

	if (!this->textureHover.loadFromFile(textureLocationHover))
		throw("ERROR: Coudld not load image");

	if (!this->texturePressed.loadFromFile(textureLocationPressed))
		throw("ERROR: Coudld not load image");
}

gui::Button::Button(float x, float y, std::string text, sf::Font * font)
{
	this->initVariables(sf::Color::Color(45, 45, 45, 255), sf::Color::Color(50, 50, 50, 255),
						sf::Color::Color(55, 55, 55, 255), sf::Color::Color(40, 40, 40, 255), 1.f);
	this->initShape(x, y, 80.f, 25.f);
	this->initText(font, text);
}

gui::Button::Button(float x, float y, float width, float height, std::string text, sf::Font * font)
{
	this->initVariables(sf::Color::Color(45, 45, 45, 255), sf::Color::Color(50, 50, 50, 255),
						sf::Color::Color(55, 55, 55, 255), sf::Color::Color(40, 40, 40, 255), 1.f);
	this->initShape(x, y, width, height);
	this->initText(font, text);
}

gui::Button::Button(float x, float y, float width, float height, sf::Font * font, std::string text, 
	sf::Color idleColor, sf::Color hoverColor, sf::Color pressedColor, sf::Color outlineColor, float outlineThickness)
{
	this->initVariables(idleColor, hoverColor, pressedColor, outlineColor, outlineThickness);
	this->initShape(x, y, width, height);
	this->initText(font, text);
}

gui::Button::Button(float x, float y, float width, float height, sf::Font * font, std::string text,
	unsigned int textSize, sf::Color idleTextColor, sf::Color hoverTextColor, sf::Color pressedTextColor, 
	sf::Color idleColor, sf::Color hoverColor, sf::Color pressedColor, sf::Color outlineColor, float outlineThickness)
{
	this->initVariables(idleColor, hoverColor, pressedColor, outlineColor, outlineThickness);
	this->textSize = textSize;
	this->idleTextColor = idleTextColor;
	this->hoverTextColor = hoverTextColor;
	this->pressedTextColor = pressedTextColor;
	this->initShape(x, y, width, height);
	this->initText(font, text);
}

gui::Button::Button(float x, float y, sf::Color outlineColor, float outlineThickness, 
	std::string textureLocationIdle, std::string textureLocationHover, std::string textureLocationPressed)
{
	this->isImage = true;
	this->initTexture(textureLocationIdle, textureLocationHover, textureLocationPressed);
	this->buttonState = this->BUTTON_IDLE;
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setTexture(&this->textureIdle);
	this->shape.setSize(sf::Vector2f((float)this->textureIdle.getSize().x, (float)this->textureIdle.getSize().y));
	this->shape.setOutlineColor(outlineColor);
	this->shape.setOutlineThickness(outlineThickness);
}

gui::Button::~Button()
{
}

sf::Vector2f gui::Button::getPosition()
{
	return this->shape.getPosition();
}

sf::Color gui::Button::getIdleTextColor()
{
	return this->idleTextColor;
}

void gui::Button::setSize(float x, float y)
{
	this->shape.setSize(sf::Vector2f(x, y));
}

void gui::Button::setCharacterSize(unsigned int size)
{
	this->text.setCharacterSize(size);
}

void gui::Button::setText(std::string text)
{
	this->text.setString(text);
}

void gui::Button::setTextColor(sf::Color idle, sf::Color hover, sf::Color pressed)
{
	this->idleTextColor = idle;
	this->hoverTextColor = hover;
	this->pressedTextColor = pressed;
}

const bool gui::Button::isPressed()
{
	if (this->buttonState == this->BUTTON_PRESSED)
		return true;
	return false;
}

const bool gui::Button::isReleased()
{
	if (this->buttonState == this->BUTTON_RELEASED)
		return true;
	return false;
}

int gui::Button::getButtonState()
{
	return this->buttonState;
}

sf::Vector2f gui::Button::getSize()
{
	return this->shape.getSize();
}


void gui::Button::setPos(float x, float y)
{
	this->shape.setPosition(sf::Vector2f(x, y));
}

void gui::Button::setBackgroundColor(sf::Color idle, sf::Color hover, sf::Color pressed)
{
	this->idleColor = idle;
	this->hoverColor = hover;
	this->pressedColor = pressed;
}

void gui::Button::setOutlineColor(sf::Color color)
{
	this->shape.setOutlineColor(color);
}

void gui::Button::setOutlineThickness(float thickness)
{
	this->shape.setOutlineThickness(thickness);
}

// Called from event loop trought updateInput() in parent
void gui::Button::updateEvent(sf::Event * ev, sf::Vector2f mousePosition)
{
	if (this->shape.getGlobalBounds().contains(mousePosition) && ev->mouseButton.button == sf::Mouse::Left)
		this->isButtonReleased = true;	
}

void gui::Button::update(sf::Vector2f mousePosition)
{	
	if (this->shape.getGlobalBounds().contains(mousePosition))
	{
		this->buttonState = this->BUTTON_HOVER;

		if (this->shape.getGlobalBounds().contains(mousePosition) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			this->buttonState = this->BUTTON_PRESSED;

		if (this->isButtonReleased)
		{
			this->buttonState = this->BUTTON_RELEASED;
			this->isButtonReleased = false;
		}	
	}
	else
		this->buttonState = this->BUTTON_IDLE;


	switch (buttonState)
	{
	case this->BUTTON_IDLE:
		if (!this->isImage)
		{
			this->shape.setFillColor(this->idleColor);
			this->text.setFillColor(this->idleTextColor);
		}
			
		else
			this->shape.setTexture(&this->textureIdle);
		break;

	case this->BUTTON_HOVER:
		if (!this->isImage)
		{
			this->shape.setFillColor(this->hoverColor);
			this->text.setFillColor(this->hoverTextColor);
		}
		else
			this->shape.setTexture(&this->textureHover);
		break;

	case this->BUTTON_PRESSED:
		if (!this->isImage)
		{
			this->shape.setFillColor(this->pressedColor);
			this->text.setFillColor(this->pressedTextColor);
		}
		else
			this->shape.setTexture(&this->texturePressed);
		break;

	default:
		if (!this->isImage)
		{
			this->shape.setFillColor(this->idleColor);
			this->text.setFillColor(this->idleTextColor);
		}	
		else
			this->shape.setTexture(&this->textureIdle);
		break;
	}
}

void gui::Button::render(sf::RenderTarget * target)
{
	target->draw(this->shape);
	target->draw(this->text);
}

/**************************************************************************
********* LABEL ***********************************************************
**************************************************************************/

gui::Label::Label(sf::Font * font, std::string text)
{
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
}

gui::Label::Label(float x, float y, sf::Font * font, std::string text, int size, sf::Color color)
{
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setCharacterSize(size);
	this->text.setFillColor(color);
	this->text.setPosition(x, y);
}

gui::Label::~Label()
{
}

void gui::Label::setPosition(float x, float y)
{
	this->text.setPosition(x, y);
}

void gui::Label::setText(std::string text)
{
	this->text.setString(text);
}

void gui::Label::setTextColor(sf::Color color)
{
	this->text.setFillColor(color);
}

void gui::Label::setCharacterSize(unsigned int size)
{
	this->text.setCharacterSize(size);
}

sf::Vector2f gui::Label::getPos()
{
	return this->text.getPosition();
}

void gui::Label::render(sf::RenderTarget * target)
{
	target->draw(this->text);
}

/**************************************************************************
********* TEXTBOX *********************************************************
**************************************************************************/

void gui::TextBox::initCursor()
{
	this->cursor.setPosition(sf::Vector2f(this->text.getGlobalBounds().width + this->shape.getPosition().x + 5, this->shape.getPosition().y + 1));
	this->cursor.setSize(sf::Vector2f(1.f, this->height - 2));
	this->cursor.setFillColor(sf::Color::White);
}

void gui::TextBox::initVariables()
{
	this->textboxState = this->TEXTBOX_IDLE;
	this->isSelected = false;
	this->width = 80;
	this->height = 20;

	this->outlineIdleThickness = 1;
	this->outlineSelectedThickness = 2;

	this->outlineIdleColor = sf::Color(34, 30, 31, 255);
	this->outlineSelectedColor = sf::Color(0, 93, 233, 255);

	this->idledColor = sf::Color(51, 51, 51, 255);
	this->hoverColor = sf::Color(51, 51, 51, 255);
	this->selectedColor = sf::Color(51, 51, 51, 255);

	this->textIdleColor = sf::Color::White;
	this->textHoverColor = sf::Color::White;
	this->textSelectedColor = sf::Color::White;
}

void gui::TextBox::initShape(float x, float y)
{
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(this->width, this->height));
	this->shape.setFillColor(sf::Color(51, 51, 51, 255));
	this->shape.setOutlineThickness(1);
	this->shape.setOutlineColor(sf::Color::Color(34, 30, 31, 255));
}

void gui::TextBox::initText(sf::Font * font)
{
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString("");
	this->text.setCharacterSize(12);
	this->text.setFillColor(sf::Color::White);
	this->text.setPosition(
		this->shape.getPosition().x + this->TEXT_OFFSET_X,
		this->shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f - this->TEXT_OFFSET_Y
	);
}

gui::TextBox::TextBox(float x, float y, sf::Font * font, bool isInput)
{
	this->isInput = isInput;
	this->initVariables();
	this->initShape(x, y);
	this->initText(font);
	this->initCursor();
}

gui::TextBox::TextBox(float x, float y, float width, float height, sf::Font * font, bool isInput)
{
	this->isInput = isInput;
	this->initVariables();
	this->width = width;
	this->height = height;
	this->initShape(x, y);
	this->initText(font);
	this->initCursor();
}

gui::TextBox::TextBox(float x, float y, float width, float height, sf::Font * font, bool isInput,
	sf::Color tIdle, sf::Color tHover, sf::Color tSelected, 
	sf::Color bIdle, sf::Color bHover, sf::Color bSelected, 
	sf::Color oIdle, sf::Color oHover, sf::Color oSelected, 
	float outlineIdleThickness, float outlineSelectedThickness)
{
	this->initVariables();
	this->isInput = isInput;
	this->width = width;
	this->height = height;
	this->initShape(x, y);
	this->initText(font);
	this->initCursor();

	this->outlineIdleColor = oIdle;
	this->outlineHoverColor = oHover;
	this->outlineSelectedColor = oSelected;

	this->idledColor = bIdle;
	this->hoverColor = bHover;
	this->selectedColor = bSelected;

	this->textIdleColor = tIdle;
	this->textHoverColor = tHover;
	this->textSelectedColor = tSelected;

	this->outlineIdleThickness = outlineIdleThickness;
	this->outlineSelectedThickness = outlineSelectedThickness;
}


gui::TextBox::~TextBox()
{
}

const bool gui::TextBox::getPressed() const
{
	if (this->textboxState == this->TEXTBOX_PRESSED)
		return true;
	return false;
}

const bool gui::TextBox::getSelected() const
{
	return this->isSelected;
}

std::string gui::TextBox::getText()
{
	return this->text.getString();
}

sf::Vector2f gui::TextBox::getPosition()
{
	return this->shape.getPosition();
}

sf::Vector2f gui::TextBox::getSize()
{
	return this->shape.getSize();
}

void gui::TextBox::setText(std::string text)
{
	this->s = text;
	this->text.setString(text);
}

void gui::TextBox::setTextColor(sf::Color idle, sf::Color hover, sf::Color selected)
{
	this->textIdleColor = idle;
	this->textHoverColor = hover;
	this->textSelectedColor = selected;
}

void gui::TextBox::setBackgroundColor(sf::Color idle, sf::Color hover, sf::Color selected)
{
	this->idledColor = idle;
	this->hoverColor = hover;
	this->selectedColor = selected;
}

void gui::TextBox::setOutlineColor(sf::Color idle, sf::Color hover, sf::Color selected)
{
	this->outlineIdleColor = idle;
	this->outlineHoverColor = hover;
	this->outlineSelectedColor = selected;
}

void gui::TextBox::setOutlineThickness(float thickness)
{
	this->shape.setOutlineThickness(thickness);
}

void gui::TextBox::setPos(float x, float y)
{
	this->shape.setPosition(x, y);
}

void gui::TextBox::setSize(float x, float y)
{
	this->shape.setSize(sf::Vector2f(x, y));
}

void gui::TextBox::setCharacterSize(unsigned int size)
{
	this->text.setCharacterSize(size);
}

void gui::TextBox::updateCursor()
{
	this->cursor.setPosition(
		sf::Vector2f(this->text.getGlobalBounds().width + this->shape.getPosition().x + 5, 
		this->shape.getPosition().y + 1)
	);
}

// Called from event loop, pollEvents() in Application
void gui::TextBox::updateText(sf::Event* ev)
{
	if (this->isInput)
	{
		// Prints out pressed key as asci code
		//if (this->getSelected())
		//	std::cout << "key pressed code: " << ev->text.unicode << std::endl;
		
		// If textbox is selected and key pressed is accepted input, add text to textbox if it's lenght is not too large
		if (this->getSelected() && ev->text.unicode < 128 && ev->text.unicode > 2 && text.getGlobalBounds().width < this->width - 12 
			&& ev->text.unicode != this->BACKSPACE_KEY && ev->text.unicode != this->ENTER_KEY && ev->text.unicode != this->TAB_KEY 
			&& ev->text.unicode != 22 && ev->text.unicode != 3) // ctrl + v = 22 | ctrl + c = 3
		{
			this->s += static_cast<char>(ev->text.unicode);
		}// Delete key
		else if (this->getSelected() && ev->text.unicode == this->BACKSPACE_KEY && s.size() != 0)
			s.pop_back();

		// Paste
		if (this->getSelected() && ev->text.unicode == 22)
		{
			// Checks whether the length of the textbox would be exceeded
			std::string clipboard = sf::Clipboard::getString();
			std::string temp = this->s;

			this->text.setString(temp += clipboard);

			if (text.getGlobalBounds().width < this->width - 12)
				this->s += clipboard;
			else
				std::cerr << "Error: Clipboard text length exceeded textbox length" << std::endl;
			
			this->text.setString(temp);
		}

		// Copy
		if (this->getSelected() && ev->text.unicode == 3)
			sf::Clipboard::setString(this->text.getString());

		this->text.setString(this->s);
	}
	
}

void gui::TextBox::update(sf::Vector2f mousePosition)
{
	if (this->getSelected())
	{
		this->updateCursor();
		this->shape.setFillColor(this->selectedColor);
		this->shape.setOutlineThickness(this->outlineSelectedThickness);
		this->shape.setOutlineColor(this->outlineSelectedColor);
	}
	else
	{
		if (this->textboxState == this->TEXTBOX_HOVER)
		{
			this->shape.setFillColor(this->hoverColor);
			this->shape.setOutlineColor(this->outlineHoverColor);
			this->shape.setOutlineThickness(this->outlineIdleThickness);
			this->text.setFillColor(this->textHoverColor);
		}
		else
		{
			this->shape.setFillColor(this->idledColor);
			this->shape.setOutlineColor(this->outlineIdleColor);
			this->shape.setOutlineThickness(this->outlineIdleThickness);
			this->text.setFillColor(this->textIdleColor);
		}
	}

	this->textboxState = this->TEXTBOX_IDLE;

	if (this->shape.getGlobalBounds().contains(mousePosition))
	{
		this->textboxState = this->TEXTBOX_HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->textboxState = this->TEXTBOX_PRESSED;
			this->isSelected = true;
		}
	}
	else
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->textboxState = this->TEXTBOX_IDLE;
			this->isSelected = false;
		}
	}
}

void gui::TextBox::render(sf::RenderTarget * target)
{
	target->draw(this->shape);
	target->draw(this->text);

	if (getSelected())
		target->draw(this->cursor);
}


/**************************************************************************
********* IMAGE **********************************************************
**************************************************************************/

void gui::Image::initTexture(std::string textureLocation)
{
	if (!this->texture.loadFromFile(textureLocation))
	{
		throw("ERROR: Coudld not load image");
	}
}

gui::Image::Image(std::string textureLocation, float x, float y)
{
	this->initTexture(textureLocation);
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setTexture(&this->texture);
	this->shape.setSize(sf::Vector2f((float)this->texture.getSize().x, (float)this->texture.getSize().y));
}

gui::Image::Image(std::string textureLocation, float x, float y, float width, float height)
{
	this->initTexture(textureLocation);
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setTexture(&this->texture);
}

gui::Image::~Image()
{
}

void gui::Image::setPosition(float x, float y)
{
	this->shape.setPosition(sf::Vector2f(x, y));
}

void gui::Image::setSize(float x, float y)
{
	this->shape.setSize(sf::Vector2f(x, y));
}

sf::Vector2f gui::Image::getPosition()
{
	return this->shape.getPosition();
}

sf::Vector2f gui::Image::getSize()
{
	return this->shape.getSize();
}

void gui::Image::render(sf::RenderTarget * target)
{
	target->draw(this->shape);
}

/**************************************************************************
********* GRAPH ***********************************************************
**************************************************************************/

void gui::Graph::initVariables(float x, float y, float height, float width, float margin, std::vector<float> inputVectorX, std::vector<float> inputVectorY)
{
	this->x = x;
	this->y = y;
	this->height = height;
	this->width = width;
	this->margin = margin;
	this->inputVectorX = inputVectorX;
	this->inputVectorY = inputVectorY;
	this->origY = inputVectorY;
	this->origX = inputVectorX;
	this->lineColor = sf::Color::Color::White;
	this->pointsColor = sf::Color::Color::White;
	this->isPointBackgroundVisible = true;
}


void gui::Graph::initBackground(sf::Color color1, sf::Color color2)
{
	this->background.setSize(sf::Vector2f(this->width, this->height));
	this->background.setFillColor(color1);
	this->background.setPosition(sf::Vector2f(this->x, this->y));

	this->background2.setSize(sf::Vector2f(this->width - 2 * this->margin, this->height - 2 * this->margin));
	this->background2.setFillColor(color2);
	this->background.setOutlineThickness(2);
	this->background.setOutlineColor(sf::Color(38, 54, 64, 255));
	this->background2.setPosition(sf::Vector2f(this->x + this->margin, this->y + this->margin));

	this->pointsTextBackground.setFillColor(sf::Color(30, 30, 30, 150));
}

void gui::Graph::initText(sf::Font * font, std::string text)
{
	this->font = font;
	this->pointText.setFont(*this->font);
	for (unsigned int i = 0; i < 5; i++)
	{
		this->text.push_back(new sf::Text);
		this->text[i]->setFont(*this->font);
		this->text[i]->setFillColor(sf::Color::White);
		this->text[i]->setCharacterSize(10);
	}
	this->text[0]->setString(text);
	this->text[0]->setPosition(
		this->background.getPosition().x + (int)(this->background.getGlobalBounds().width / 2) - (int)this->text[0]->getGlobalBounds().width / 2 - 3,
		this->background.getPosition().y + (this->margin / 4)
	);
	
	this->text[1]->setString(std::to_string((int)this->minX));
	this->text[1]->setPosition(
		this->background.getPosition().x + this->margin,
		this->background.getPosition().y + this->background.getGlobalBounds().height - (int)(4 * this->margin / 5)
	);
	this->text[2]->setString(std::to_string((int)this->maxX));
	this->text[2]->setPosition(
		this->background.getPosition().x + this->background.getGlobalBounds().width - this->margin - (int)this->text[2]->getLocalBounds().width,
		this->background.getPosition().y + this->background.getGlobalBounds().height - (int)(4 * this->margin / 5)
	);
	this->text[3]->setString(std::to_string((int)this->minY));
	this->text[3]->setPosition(
		this->background.getPosition().x,
		this->background.getPosition().y + this->background.getGlobalBounds().height - this->margin - (int)(6 * this->text[2]->getLocalBounds().height / 4)
	);
	this->text[4]->setString(std::to_string((int)this->maxY));
	this->text[4]->setPosition(
		this->background.getPosition().x,
		this->background.getPosition().y + this->margin
	);
}

void gui::Graph::initGraphSingleInput(float min, float max)
{
	if (this->inputVectorY.size() != 0)
	{
		this->numberOfPoints = this->inputVectorY.size();
		this->spacing = (this->width - 2 * this->margin) / (this->numberOfPoints - 1);
		this->minY = min;
		this->maxY = max;

		//init lines 
		this->lines = sf::VertexArray(sf::LineStrip, this->numberOfPoints);

		for (int i = 0; i < this->numberOfPoints; i++)
		{
			// add new point
			this->points.push_back(new sf::CircleShape);
			// populate vector
			this->pointsPositions.push_back(sf::Vector2f(0, 0));
			// normalize input vectors 0-1
			this->inputVectorY[i] = ((this->inputVectorY[i] - this->minY) / (this->maxY - this->minY));
			// scale values. 1 being the maximum. top left is 0,0 so 1-(...) at Y to invert it
			this->pointsPositions[i].y = ((1 - this->inputVectorY[i])) * (this->height - 2 * margin) + this->y + margin;
			// equal distance from points at x axis
			this->pointsPositions[i].x = this->spacing * i + this->x + this->margin;

			this->points[i]->setPosition(this->pointsPositions[i]);
			this->points[i]->setRadius(4.f);
			this->points[i]->setFillColor(this->pointsColor);
			this->points[i]->setPointCount(50);

			this->lines[i].color = this->lineColor;
			this->lines[i].position = sf::Vector2f(this->pointsPositions[i].x + 2.f, this->pointsPositions[i].y + 2.f);
		}
	}
}

void gui::Graph::initGraphDoubleFloatInput()
{
	if (this->inputVectorX.size() == this->inputVectorY.size() && this->inputVectorX.size() != 0)
	{
		this->numberOfPoints = this->inputVectorX.size();

		//find min and max of input vectors
		const auto minmaxX = std::minmax_element(this->inputVectorX.begin(), this->inputVectorX.end());
		const auto minmaxY = std::minmax_element(this->inputVectorY.begin(), this->inputVectorY.end());
		this->minX = *minmaxX.first;
		this->maxX = *minmaxX.second;
		this->minY = *minmaxY.first;
		this->maxY = *minmaxY.second;
		//init lines 
		this->lines = sf::VertexArray(sf::LineStrip, this->numberOfPoints);

		for (int i = 0; i < this->numberOfPoints; i++)
		{
			//add new point
			this->points.push_back(new sf::CircleShape);
			//populate vector
			this->pointsPositions.push_back(sf::Vector2f(0, 0));
			//normalize input vectors 0-100
			this->inputVectorY[i] = ((this->inputVectorY[i] - this->minY) / (this->maxY - this->minY));
			this->inputVectorX[i] = ((this->inputVectorX[i] - this->minX) / (this->maxX - this->minX));
			//scale values. 1 being the maximum. top left is 0,0 so 1-(...) at Y to invert it
			this->pointsPositions[i].y = (1 - (this->inputVectorY[i])) * (this->height - 2 * this->margin) + this->y + this->margin;
			this->pointsPositions[i].x = this->inputVectorX[i] * (this->width - 2 * this->margin) + this->x + this->margin;

			this->points[i]->setPosition(this->pointsPositions[i]);
			this->points[i]->setRadius(3.f);
			this->points[i]->setFillColor(this->lineColor);
			this->points[i]->setPointCount(50);
			this->lines[i].color = this->lineColor;
			this->lines[i].position = sf::Vector2f(this->pointsPositions[i].x + 2.f, this->pointsPositions[i].y + 2.f);
		}
	}
}

gui::Graph::Graph(sf::Font * font, std::string title, std::vector<float> inputVectorY, float max, float min, float x, float y, float width, float height, float margin)
{
	this->isXNumeric = false;
	this->isPointBackgroundVisible = true;
	this->x = x;
	this->y = y;
	this->height = height;
	this->width = width;
	this->margin = margin;
	this->inputVectorY = inputVectorY;
	this->origY = inputVectorY;
	this->lineColor = sf::Color::Color::White;
	this->pointsColor = sf::Color::Color::White;

	this->initBackground(sf::Color(36, 52, 62, 255), sf::Color(38, 54, 64, 255));
	this->initGraphSingleInput(min, max);
	this->updatePointsBackground();
	this->initText(font, title);
}

gui::Graph::Graph(sf::Font * font, std::string title, std::vector<std::string> inputVectorX, std::vector<float> inputVectorY, 
	float max, float min, float x, float y, float width, float height, float margin)
{
	this->isXNumeric = false;
	this->isHoveringPoint = false;
	this->isPointBackgroundVisible = true;
	this->x = x;
	this->y = y;
	this->height = height;
	this->width = width;
	this->margin = margin;
	this->inputVectorY = inputVectorY;
	this->stringAxisX = inputVectorX;
	this->origY = inputVectorY;
	this->lineColor = sf::Color::Color::White;
	this->pointsColor = sf::Color::Color::White;

	this->initBackground(sf::Color(36, 52, 62, 255), sf::Color(38, 54, 64, 255));
	this->initGraphSingleInput(min, max);
	this->updatePointsBackground();
	this->initText(font, title);
}

gui::Graph::Graph(sf::Font * font, std::string title, std::vector<float> inputVectorX, std::vector<float> inputVectorY, float x, float y,
				float width, float height, float margin)
{
	this->isXNumeric = true;
	this->initVariables(x, y, height, width, margin, inputVectorX, inputVectorY);
	this->initBackground(sf::Color(36, 52, 62, 255), sf::Color(38, 54, 64, 255));
	this->initGraphDoubleFloatInput();
	this->updatePointsBackground();
	this->initText(font, title);
}

gui::Graph::~Graph()
{
	for (unsigned int i = 0; i < this->points.size(); i++)
		delete points[i];

	for (unsigned int i = 0; i < this->pointsBackground.size(); i++)
		delete pointsBackground[i];

	for (unsigned int i = 0; i < this->text.size(); i++)
		delete text[i];
}

sf::Vector2f gui::Graph::getPosition()
{
	return this->background.getPosition();
}

bool gui::Graph::getPointBackgroundVisibility()
{
	return this->isPointBackgroundVisible;
}

void gui::Graph::setPosition(float x, float y)
{
	this->background.setPosition(sf::Vector2f(x, y));
}

void gui::Graph::setBackgroundColor(sf::Color background, sf::Color margin)
{
}

void gui::Graph::setGraphColor(sf::Color line, sf::Color points)
{
	this->pointsColor = points;
	this->lineColor = line;

	for (int i = 0; i < this->numberOfPoints; i++)
	{
		this->points[i]->setFillColor(this->pointsColor);
		this->lines[i].color = this->lineColor;
	}
}

void gui::Graph::setPointBackgroundVisibility(bool value)
{
	this->isPointBackgroundVisible = value;
}

void gui::Graph::setOutline(sf::Color outline, float thickness)
{
	this->background.setOutlineColor(outline);
	this->background.setOutlineThickness(thickness);
}

void gui::Graph::clearGraph()
{
	for (unsigned int i = 0; i < this->points.size(); i++)
		delete points[i];
	this->lines.clear();
	this->points.clear();
	this->pointsPositions.clear();
	this->inputVectorX.clear();
	this->inputVectorY.clear();
	this->origY.clear();
}

void gui::Graph::updatePoints(float newPoint)
{	
	// Shift every value by 1 to the left
	int j = 1;
	for (unsigned int i = 0; i < this->inputVectorY.size() - 1; i++)
	{
		this->inputVectorY[i] = this->inputVectorY[j];
		this->origY[i] = this->origY[j];
		j++;
	}

	// Normalize new value and replace last value of the input vector with this new value
	this->inputVectorY[this->inputVectorY.size() - 1] = ((newPoint - this->minY) / (this->maxY - this->minY));
	this->origY[this->origY.size() - 1] = newPoint;

	// Update points
	for (int i = 0; i < this->numberOfPoints; i++)
	{
		// Scale values. 1 being the maximum. top left is 0,0 so 1-(...) at Y to invert it
		this->pointsPositions[i].y = ((1 - this->inputVectorY[i])) * (this->height - 2 * this->margin) + this->y + this->margin;
		// Equal distance from points at x axis
		this->pointsPositions[i].x = this->spacing * i + this->x + this->margin;

		this->points[i]->setPosition(this->pointsPositions[i]);
		this->points[i]->setRadius(3.f);
		this->points[i]->setFillColor(this->pointsColor);
		this->points[i]->setPointCount(50);

		this->lines[i].color = this->lineColor;
		this->lines[i].position = sf::Vector2f(this->pointsPositions[i].x + 2.f, this->pointsPositions[i].y + 2.f);
	}

	this->updatePointsBackground();
}

void gui::Graph::updatePointsBackground()
{
	// that background thingy bellow graph lines
	for (int i = 0; i < this->numberOfPoints - 1; i++)
	{
		this->pointsBackground.push_back(new sf::ConvexShape);
		this->pointsBackground[i]->setPointCount(4);
		this->pointsBackground[i]->setFillColor(sf::Color(220, 0, 45, 20));

		//*.
		//..
		this->pointsBackground[i]->setPoint(0, sf::Vector2f(
			this->pointsPositions[i].x,
			this->pointsPositions[i].y + 5
		));

		//.*
		//..
		this->pointsBackground[i]->setPoint(1, sf::Vector2f(
			this->pointsPositions[i + 1].x,
			this->pointsPositions[i + 1].y + 5
		));

		//..
		//.*
		this->pointsBackground[i]->setPoint(2, sf::Vector2f(
			this->pointsPositions[i + 1].x,
			this->y + this->background.getSize().y - this->margin
		));

		//..
		//*.
		this->pointsBackground[i]->setPoint(3, sf::Vector2f(
			this->pointsPositions[i].x,
			this->y + this->background.getSize().y - this->margin
		));
	}
}

void gui::Graph::updateEvent(sf::Event* ev, sf::Vector2f mousePosition)
{
	std::string temp = "";

	this->pointText.setPosition(sf::Vector2f(
		this->x + this->background.getSize().x - this->margin - this->pointText.getGlobalBounds().width, 
		this->y + this->background.getSize().y - this->margin - this->pointText.getGlobalBounds().height)
	);
	this->pointText.setCharacterSize(12);
	this->pointText.Bold;
	this->pointText.setOutlineThickness(1);
	this->pointText.setOutlineColor(sf::Color::Black);
	this->pointText.setFillColor(sf::Color::White);

	for (unsigned int i = 0; i < this->points.size(); i++)
	{
		if (this->points[i]->getGlobalBounds().contains(mousePosition))
		{
			if (this->isXNumeric)
				temp = std::to_string(this->origY[i]) + "\n" + std::to_string(this->origX[i]);
			else
				temp = std::to_string(this->origY[i]) + "\n" + stringAxisX[i];

			this->pointText.setString(temp);

			this->pointText.setPosition(sf::Vector2f(
				(int)(this->points[i]->getPosition().x - this->pointText.getGlobalBounds().width / 2),
				(int)(this->points[i]->getPosition().y - 1.2 * this->pointText.getGlobalBounds().height)
			));

			this->pointsTextBackground.setPosition(this->pointText.getPosition().x - 4, this->pointText.getPosition().y - 4);
			this->pointsTextBackground.setSize(sf::Vector2f(
				this->pointText.getGlobalBounds().width + 8,
				this->pointText.getGlobalBounds().height + 8
			));

			this->isHoveringPoint = true;

			break;
		}

		if (!this->points[i]->getGlobalBounds().contains(mousePosition))
		{
			this->pointText.setString("");
			this->isHoveringPoint = false;
		}
			

	}
}


void gui::Graph::render(sf::RenderTarget * target)
{
	target->draw(this->background);
	target->draw(this->background2);
	
	for (unsigned int i = 0; i < this->text.size(); i++)
		target->draw(*this->text[i]);

	for (unsigned int i = 0; i < this->points.size(); i++)
	{
		target->draw(*this->points[i]);
		target->draw(this->lines);
	}
	
	if (isPointBackgroundVisible)
		for (unsigned int i = 0; i < this->pointsBackground.size(); i++)
			target->draw(*pointsBackground[i]);
	
	if (this->isHoveringPoint)
	{
		target->draw(this->pointsTextBackground);
		target->draw(this->pointText);
	}
	
}

/**************************************************************************
********* PopUp ***********************************************************
**************************************************************************/

gui::PopUp::PopUp(sf::Font* font, std::string text, float x, float y)
{
	this->visibility = false;

	this->font = font;

	this->button_text.setFont(*this->font);
	this->button_text.setCharacterSize(12);
	this->button_text.setFillColor(sf::Color::Color::White);
	this->button_text.setString("Ok");

	this->text.setFont(*this->font);
	this->text.setCharacterSize(12);
	this->text.setFillColor(sf::Color::Color::White);
	this->text.setString(text);

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(this->text.getGlobalBounds().width + 20.f, this->text.getGlobalBounds().height + 60.f));
	this->text.setPosition(sf::Vector2f(this->shape.getPosition().x + 10, this->shape.getPosition().y + 10));
	this->shape.setFillColor(sf::Color(51, 51, 51, 255));
	this->shape.setOutlineColor(sf::Color(40, 40, 40, 255));
	this->shape.setOutlineThickness(2);

	this->button_shape.setSize(sf::Vector2f(30.f, 25.f));
	this->button_shape.setPosition(sf::Vector2f(
		this->shape.getPosition().x + this->shape.getSize().x / 2.f - this->button_shape.getSize().x / 2.f,
		this->text.getPosition().y + this->text.getGlobalBounds().height + 20.f
	));
	this->button_shape.setFillColor(sf::Color(60, 60, 60, 255));
	this->button_shape.setOutlineColor(sf::Color(45, 45, 45, 255));
	this->button_shape.setOutlineThickness(1);

	this->button_text.setPosition(sf::Vector2f(
		this->button_shape.getPosition().x + (int)(this->button_shape.getSize().x / 2) - (int)(this->button_text.getGlobalBounds().width / 2.f),
		this->button_shape.getPosition().y + (int)(this->button_shape.getSize().y / 2) - (int)(this->button_text.getGlobalBounds().height / 2.f) - 2.f
	));
}

gui::PopUp::~PopUp()
{
}

bool gui::PopUp::getVisibility()
{
	return visibility;
}

void gui::PopUp::setVisibility(bool value)
{
	this->visibility = value;
}

void gui::PopUp::update(sf::Vector2f mousePosition)
{
	if (this->button_shape.getGlobalBounds().contains(mousePosition) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		this->visibility = false;
}

void gui::PopUp::render(sf::RenderTarget * target)
{
	target->draw(this->shape);
	target->draw(this->text);
	target->draw(this->button_shape);
	target->draw(this->button_text);
}
