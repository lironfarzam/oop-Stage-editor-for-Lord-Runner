#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "Location.h"

using std::vector;

const int NUM_IMAGES = 9;
const int ERASER_TOOL = 6;
const int RESET_TOOL = 7;
const int SAVE_TOOL = 8;
const int PLAYER_TOOL = 1;
const int OUTLINER = 50;



class Menu {
public:

	Menu(Location);

	void draw( sf::RenderWindow& window) const;

	int getToolIndex(int x, int y) const; // returns the menu index with mouse x/y, -1 if NONE
	sf::Texture getTexture(int index) const; // get the current texture

	sf::Sprite buildTransparentCursor(int index) const;

	char convertSpriteToChar(int index) const;
	sf::Sprite convertCharToSprite(char c) const;

	int getCurrentMenuItem();
    void setCurrentMenuItem(int n);

private:
    int m_curmenu_item = -1; // the user choice index in m_menu_items

	std::vector<char> m_menu_items; // the board of characters for output file
	std::vector<sf::Texture> m_textures; // loading the images

	Location m_loc; // location of the menu for draw function
};
