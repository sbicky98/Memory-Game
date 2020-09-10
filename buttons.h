/************************
Student Name:           Bikramjeet Singh
Student No:				040955651
Assignment name:		Memory Game
Course Name and Number:	C++ Programming  CST8219
Lab Section:			302
Professor Name:         Eric Torunski
Due Date:				7th August 2020
Submission Date:		7th August 2020
File:                   buttons.h
***********************/
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
class Button {
	sf::Texture Idle;
	sf::Texture Hover;
	sf::Texture Click;
	sf::Font Font;
	float x = 0;
	float y = 0;
	float x2 = 0;
	float y2 = 0;
	int fineAdjust = 0;
public:
	sf::Sprite Sprite;
	sf::Text Label;
	bool hover = false;
	bool press = false;
	bool click = false;
	string label = "Button";
	string clickLabel = label;
	string hoverLabel = label;
	void Create() {
		Idle.loadFromFile("res/button/btn_idle.png");
		Hover.loadFromFile("res/button/btn_hover.png");
		Click.loadFromFile("res/button/btn_click.png");
		Font.loadFromFile("res/arial.ttf");
		Label.setFont(Font);
		Label.setCharacterSize(24);
		Label.setFillColor(sf::Color::Black);
		setLabel(label);
		Sprite.setTexture(Idle);
		if (Label.getLocalBounds().height <= 18) { fineAdjust = 0; }
		if (Label.getLocalBounds().height >= 23) { fineAdjust = 5; }
		Label.setOrigin(sf::Vector2f(((Sprite.getLocalBounds().width - Label.getLocalBounds().width) / 2) * (-1), ((Sprite.getLocalBounds().height - (Label.getLocalBounds().height - fineAdjust) * 1.7) / 2) * (-1)));
	}
	void setState(string type) {
		if (type == "Idle") {
			Sprite.setTexture(Idle);
		}
		else if (type == "Hover") {
			Sprite.setTexture(Hover);
		}
		else if (type == "Click") {
			Sprite.setTexture(Click);
		}
	}
	void setPosition(float newX, float newY) {
		x = newX;
		y = newY;
		x2 = newX + Sprite.getLocalBounds().width;
		y2 = newY + Sprite.getLocalBounds().height;
		Sprite.setPosition(sf::Vector2f(newX, newY));
		Label.setPosition(sf::Vector2f(newX, newY));
	}
	void setLabel(string x) {
		string oldLabel = label;
		string oldClickLabel = clickLabel;
		if (x != clickLabel && x != hoverLabel) {
			label = x;
		}
		if (clickLabel == oldLabel && x != hoverLabel) {
			clickLabel = x;
		}
		if (hoverLabel == oldLabel && x != oldClickLabel) {
			hoverLabel = x;
		}
		Label.setString(x);
		if (Label.getLocalBounds().height <= 18) { fineAdjust = 0; }
		if (Label.getLocalBounds().height >= 23) { fineAdjust = 5; }
		Label.setOrigin(sf::Vector2f(((Sprite.getLocalBounds().width - Label.getLocalBounds().width) / 2) * (-1), ((Sprite.getLocalBounds().height - (Label.getLocalBounds().height - fineAdjust) * 1.7) / 2) * (-1)));
	}
	int height() { return Sprite.getLocalBounds().height; }
	int width() { return Sprite.getLocalBounds().width; }
	bool withinBounds(int coorX, int coorY) {
		if (coorX > x && coorX < x2 && coorY > y && coorY < y2) {
			if (press != true) {
				Sprite.setTexture(Hover);
				setLabel(hoverLabel);
			}
			hover = true;
			return true;
		}
		else {
			if (press != true) {
				Sprite.setTexture(Idle);
				setLabel(label);
			}
			hover = false;
			return false;
		}
	}
	bool isPressed(int x = 1) {
		if (hover == true && press == false && x == 1) {
			Sprite.setTexture(Click);
			setLabel(clickLabel);
			press = true;
			return true;
		}
		else if (hover == true && x == 2) {
			Sprite.setTexture(Hover);
			setLabel(hoverLabel);
			press = false;
			return true;
		}
		else if (hover == false && press == true && x == 2) {
			Sprite.setTexture(Idle);
			setLabel(label);
			press = false;
			return false;
		}
		else {
			return false;
		}
	}
	void draw(sf::RenderWindow window) {
		window.draw(Sprite);
		window.draw(Label);
	}
};
