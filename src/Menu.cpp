#include "Menu.h"


const char game_chars[NUM_IMAGES] = { WALL, PLAYER, ENEMY, LADDER, POLE, COIN };
const char* game_images[NUM_IMAGES] = { "wall.png", "player.png", "enemy.png", "ladder.png", "pole.png", "coin.png", "eraser.png", "resize.png", "save.png" };


// this class loads textures for sprites and builds the toolbar for
// the app. 
Menu::Menu(Location loc) :m_loc(loc)
{
	// the menu items (ignore the save and eraser)
	for (int i = 0; i < NUM_IMAGES - 3; i++) {
		m_menu_items.push_back(game_chars[i]);
	}

	m_textures.resize(NUM_IMAGES);

	// load images (textures) once in a vector  m_texture
	for (int i = 0; i < NUM_IMAGES; i++) {

		if (!m_textures[i].loadFromFile(game_images[i]))

			std::cout << "failed to load image file:" << game_images[i] << std::endl;

	}

}


// create a transparent sprite
// index: of the item in the menu
sf::Sprite Menu::buildTransparentCursor(int index) const
{
	sf::Sprite sp = sf::Sprite(m_textures[index]);
	sp.setColor(sf::Color(255, 255, 255, 128)); // half transparent
	return sp;
}


// returns the character code of the menu item
char Menu::convertSpriteToChar(int index) const
{

	if (index >=0 && index < ERASER_TOOL)
		return game_chars[index];
	else
		return EMPTY;
}

sf::Sprite Menu::convertCharToSprite(char c) const
{

	sf::Sprite sp = sf::Sprite(m_textures[0]);

	switch (c) {
	case WALL:

		break;
	case PLAYER:
		sp = sf::Sprite(m_textures[1]);
		break;
	case ENEMY:
		sp = sf::Sprite(m_textures[2]);
		break;
	case LADDER:
		sp = sf::Sprite(m_textures[3]);
		break;
	case POLE:
		sp = sf::Sprite(m_textures[4]);
		break;
	case COIN:
		sp = sf::Sprite(m_textures[5]);
		break;
	case EMPTY:
	default:
		std::cout << "unexpected board character!";
	}
	return sp;
}

void Menu::draw(sf::RenderWindow& window) const
{
	Location start = m_loc;

	sf::RectangleShape rect (sf::Vector2f((float)ICON_WIDTH, (float)(ICON_HEIGHT) * m_textures.size()));
	rect.setPosition(0, 0);
	rect.setFillColor(sf::Color(OUTLINER, OUTLINER, OUTLINER));
	rect.setOutlineThickness(1);
	rect.setOutlineColor(sf::Color(150, 150, 150));
	window.draw(rect);

	for (int i = 0; i < m_textures.size(); i++)
	{
		sf::Sprite sp = sf::Sprite(m_textures[i]);
		sp.setPosition(sf::Vector2f((float)start.x , (float)start.y));

		window.draw(sp);

		start.y += ICON_HEIGHT ;
	}
}

// returns the array index of the tool item clicked
int Menu::getToolIndex(int x, int y) const
{
	if (x < ICON_WIDTH) {
		if (y < (NUM_IMAGES * (ICON_HEIGHT)))
			return y / (ICON_HEIGHT) ;
	}

	return -1;
}

sf::Texture Menu::getTexture(int index) const
{
	return m_textures[index];
}

int Menu::getCurrentMenuItem() {
	return m_curmenu_item;
}

void Menu::setCurrentMenuItem(int n) {
	m_curmenu_item = n;
}