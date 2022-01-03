/************************************************************************************
 * @file Gui.h
 *
 * @brief GUI for SFML using C++
 *
 * @author Vladimir Milivojevic
 *
 ************************************************************************************/

#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Clipboard.hpp>
#include <iostream>

namespace gui
{
	class Button
	{
	private:
		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;
		sf::Color idleColor, hoverColor, pressedColor, 
			idleTextColor, hoverTextColor, pressedTextColor, outlineColor;
		sf::Texture textureIdle, textureHover, texturePressed;
		float outlineThickness, isButtonReleased;
		unsigned int textSize;
		bool isImage;
		short unsigned buttonState;

		enum button_state {
			BUTTON_IDLE = 0,
			BUTTON_HOVER,
			BUTTON_PRESSED,
			BUTTON_RELEASED,
		};
		// Init
		void initVariables(sf::Color idleColor, sf::Color hoverColor, sf::Color pressedColor, sf::Color outlineColor, float outlineThickness);
		void initShape(float x, float y, float width, float height);
		void initText(sf::Font* font, std::string text);
		void initTexture(std::string textureLocationIdle, std::string textureLocationHover, std::string textureLocationPressed);

	public:
		// pos, font, text
		Button(float x, float y, std::string text, sf::Font* font);
		// pos, size, font, text
		Button(float x, float y, float width, float height, std::string text, sf::Font* font);
		// pos, size, font, text, background color, outline color, outline thickness
		Button(float x, float y, float width, float height,
			sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor,
			sf::Color pressedColor, sf::Color outlineColor, float outlineThickness);
		// pos, size, font, text, text size, text color, background color, outline color, outline thickness
		Button(float x, float y, float width, float height, sf::Font* font, std::string text, 
			unsigned int textSize, sf::Color idleTextColor, sf::Color hoverTextColor, sf::Color pressedTextColor,
			sf::Color idleColor, sf::Color hoverColor, sf::Color pressedColor, sf::Color outlineColor, float outlineThickness);
		// Texture button -> pos, outline color, outline thickness, idle/hover/pressed texture
		Button(float x, float y, sf::Color outlineColor, float outlineThickness,
			std::string textureLocationIdle, std::string textureLocationHover, std::string textureLocationPressed);
		virtual ~Button();

		
		// Set
		void setSize(float x, float y);
		void setCharacterSize(unsigned int size);
		void setText(std::string text);
		void setTextColor(sf::Color idle, sf::Color hover, sf::Color pressed);
		void setPos(float x, float y);
		void setBackgroundColor(sf::Color idle, sf::Color hover, sf::Color pressed);
		void setOutlineColor(sf::Color color);
		void setOutlineThickness(float thickness);

		// Get
		sf::Vector2f getPosition();
		sf::Color getIdleTextColor();
		sf::Vector2f getSize();
		int getButtonState();

		const bool isPressed();
		const bool isReleased();
		
		// Needs to be called from event loop
		void updateEvent(sf::Event* ev, sf::Vector2f mousePosition);

		// Update, Render
		void update(sf::Vector2f mousePosition);
		void render(sf::RenderTarget* target);
	};

	class Label
	{
	private:
		sf::Font* font;
		sf::Text text;
	public:
		// font, text
		Label(sf::Font * font, std::string text);
		// pos, font, text, text size, text color
		Label(float x, float y, sf::Font * font, std::string text, int size, sf::Color color);
		virtual ~Label();

		// Set
		void setPosition(float x, float y);
		void setText(std::string text);
		void setTextColor(sf::Color color);
		void setCharacterSize(unsigned int size);

		// Get
		sf::Vector2f getPos();
		
		// Render
		void render(sf::RenderTarget* target);
	};

	class TextBox
	{
	private:
		sf::RectangleShape shape, cursor;
		sf::Font* font;
		sf::Text text;
		sf::Color idledColor, hoverColor, selectedColor,
			textIdleColor, textHoverColor, textSelectedColor,
			outlineIdleColor, outlineHoverColor, outlineSelectedColor;

		std::string s/*, s_keys[2] = {"", ""}*/;
		float width, height, outlineIdleThickness, outlineSelectedThickness;
		bool isSelected, isInput;
		
		const int TEXT_OFFSET_X = 5;
		const int TEXT_OFFSET_Y = 8;
		const int BACKSPACE_KEY = 8;
		const int ENTER_KEY = 9;
		const int TAB_KEY = 13;

		short unsigned textboxState;
		enum textbox_state {
			TEXTBOX_IDLE,
			TEXTBOX_HOVER,
			TEXTBOX_PRESSED,
		};
		
		// Init
		void initCursor();
		void initVariables();
		void initShape(float x, float y);
		void initText(sf::Font * font);

	public:
		// pos, font, is input allowed
		TextBox(float x, float y, sf::Font * font, bool isInput);
		// pos, width, font, size, is input allowed
		TextBox(float x, float y, float width, float height, sf::Font * font, bool isInput);
		// pos, width, font, size, is input allowed, text color, background color, outline color, outline thickness
		TextBox(float x, float y, float width, float height, sf::Font * font, bool isInput,
			sf::Color tIdle, sf::Color tHover, sf::Color tSelected,
			sf::Color bIdle, sf::Color bHover, sf::Color bSelected,
			sf::Color oIdle, sf::Color oHover, sf::Color oSelected, 
			float outlineIdleThickness, float outlineSelectedThickness);
		virtual ~TextBox();

		// Set
		void setText(std::string text);
		void setPos(float x, float y);
		void setSize(float x, float y);
		void setCharacterSize(unsigned int size);
		void setTextColor(sf::Color idle, sf::Color hover, sf::Color selected);
		void setBackgroundColor(sf::Color idle, sf::Color hover, sf::Color selected);
		void setOutlineColor(sf::Color idle, sf::Color hover, sf::Color selected);
		void setOutlineThickness(float thickness);

		// Get
		const bool getPressed() const;
		const bool getSelected() const;
		std::string getText();
		sf::Vector2f getPosition();
		sf::Vector2f getSize();

		// Needs to be called from event loop
		void updateText(sf::Event* ev);

		void updateCursor();

		// Update, Render
		void update(sf::Vector2f mousePosition);
		void render(sf::RenderTarget* target);
	};

	class Image {
	private:
		sf::RectangleShape shape;
		sf::Texture texture;
		// Init
		void initTexture(std::string textureLocation);
	public:
		// texture, pos
		Image(std::string textureLocation, float x, float y);
		// texture, pos, size
		Image(std::string textureLocation, float x, float y, float width, float height);
		virtual ~Image();

		// Set
		void setPosition(float x, float y);
		void setSize(float x, float y);

		// Get
		sf::Vector2f getPosition();
		sf::Vector2f getSize();

		// Render
		void render(sf::RenderTarget* target);
	};

	class Graph {
	private:
		sf::RectangleShape background, background2;
		sf::Font* font;
		sf::VertexArray lines;
		sf::Color lineColor, pointsColor;
		sf::Text loadingText;
		std::vector<sf::Text*> text;
		std::vector<sf::CircleShape*> points;
		std::vector<sf::Vector2f> pointsPositions;
		std::vector<float> inputVectorX, inputVectorY;		
		int numberOfPoints;
		float spacing, margin, minY, maxY, minX, maxX, x, y, width, height;
		bool isLoading;
		// Init
		void initVariables(float x, float y, float height, float width, float margin, std::vector<float> inputVectorX, std::vector<float> inputVectorY);
		void initBackground(sf::Color color, sf::Color color2);
		void initText(sf::Font * font, std::string text);
		void initGraph();
	public:
		// No input, pos, size, margin
		Graph(sf::Font* font, std::string title, float x, float y, float width, float height, float margin);
		// Single input vector, x axis auto, min, max, pos, size, marhin (manual scaling)
		Graph(sf::Font* font, std::string title, std::vector<float> inputVectorY, float max, float min, float x, float y, float width, float height, float margin);
		// Input x and y, pos, size, margin (scaled to min and max of input)
		Graph(sf::Font* font, std::string title, std::vector<float> inputVectorX, std::vector<float> inputVectorY, float x, float y, float width, float height, float margin);
		virtual ~Graph();

		// Set
		void setPosition(float x, float y);
		void setLoading(bool value);
		void setBackgroundColor(sf::Color background, sf::Color margin);
		void setOutline(sf::Color outline, float thickness);
		void setGraphColor(sf::Color line, sf::Color points);

		// Get
		const bool getLoading();
		sf::Vector2f getPosition();
		
		void clearGraph();

		// Update
		void updatePoints(float newPoint);

		// Render
		void render(sf::RenderTarget* target);
	};

	class PopUp {
	private:
		sf::RectangleShape shape, button_shape;
		sf::Font* font;
		sf::Text text, button_text;
		bool visibility;
	public:
		// font, text, pos
		PopUp(sf::Font* font, std::string text, float x, float y);
		virtual ~PopUp();

		// Set
		void setVisibility(bool value);

		// Get
		bool getVisibility();
		
		// Update, Render
		void update(sf::Vector2f mousePosition);
		void render(sf::RenderTarget* target);
	};
}

#endif // !GUI_H
