#pragma once

#include <iostream>
#include <stdbool.h>
#include <SFML/Graphics.hpp>
#include <iomanip>
#include <fstream>
#include <iostream>


#include "Menu.h"
#include "Painter.h"
#include "Constants.h"
#include "Board.h"
#include "Location.h"



using std::vector;

class Controller {
public:
	Controller();
	void run();

	bool mouseOverBoard(int x, int y) const;
	Location getCellIndexes(int x, int y) const;

private:

    void handleMouseMove(sf::Sprite& mouseSprite,
                                     sf::RectangleShape& highlightRect, int menu_item, sf::Vector2f& location);

	void handleMouseClick(sf::Event& event,int &menu_item, sf::Sprite& mouseSprite, bool& loadedmap, sf::Vector2f location, 
		sf::RenderWindow& m_window) ;

	Menu m_menu;
	Painter m_painter;
	Board m_board;

	// the size in PIXELS
	int m_window_height;
	int m_window_width;

	Location getBoardSize() const;
};