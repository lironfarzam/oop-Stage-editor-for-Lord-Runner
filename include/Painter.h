#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "Board.h"
#include "Menu.h"

using std::vector;

class Painter {

public:

	Painter( Menu&);

	void printMap(sf::RenderWindow &, Board &) const;
	void printCover(sf::RenderWindow&) const;
	void showSaved(sf::RenderWindow& m_window) const;

private:

    Menu& m_menu;
	sf::Texture m_cover;
	sf::Texture m_saved;
};