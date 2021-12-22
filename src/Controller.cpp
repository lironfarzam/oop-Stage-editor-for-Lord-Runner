#include "Controller.h"

Controller::Controller():m_window_height(500), m_window_width(500) , 
		m_menu (Location(0, 0)), m_painter(m_menu )
{
}

void Controller::run() {
	int menu_item = -1;

	bool loadedmap = m_board.loadMap();

	// compute and store window size in Pixels (includes menu and board together)
	m_window_width = ICON_WIDTH + (m_board.getSizeCols() * ICON_WIDTH); // leave space for menu
	m_window_height = std::max(m_board.getSizeRows() * ICON_WIDTH, NUM_IMAGES * ICON_HEIGHT);

	// create the window
	sf::RenderWindow m_window = sf::RenderWindow(sf::VideoMode(1024, 767), "David&Liron's Loderunner map editor");

    m_window.setView(sf::View(sf::FloatRect(0, 0, (float)m_window_width, (float)m_window_height)));
    m_window.setSize(sf::Vector2u(m_window_width, m_window_height));

	sf::Sprite mouseSprite; 
	mouseSprite.setPosition(sf::Vector2f(-ICON_HEIGHT, -ICON_HEIGHT));

	// outlining a cell on board
	sf::RectangleShape highlightRect (sf::Vector2f(ICON_WIDTH, ICON_HEIGHT));
	highlightRect.setPosition(-ICON_HEIGHT, -ICON_HEIGHT);
	highlightRect.setOutlineThickness(2);
	highlightRect.setFillColor(sf::Color::Transparent);
	highlightRect.setOutlineColor(sf::Color::Red);
	
	auto location = m_window.mapPixelToCoords({ 0, 20 });

	while (m_window.isOpen())
	{
		m_window.clear();

		if (!loadedmap) {

			m_painter.printCover(m_window);

			Location loc = getBoardSize(); // get user input

			m_board.resetMap(loc.x, loc.y);

			// reinitialize window size and update window on screen
			m_window_width = ICON_WIDTH + (m_board.getSizeCols() * ICON_WIDTH); // leave space for menu
			m_window_height = std::max(m_board.getSizeRows() * ICON_WIDTH, NUM_IMAGES * ICON_HEIGHT);
			m_window.setView(sf::View(sf::FloatRect(0, 0, (float)m_window_width, (float)m_window_height)));
			m_window.setSize(sf::Vector2u(m_window_width, m_window_height));

			loadedmap = true;
		}
		else {
			m_menu.draw(m_window); // draw menu
			m_painter.printMap(m_window, m_board); // print the board
			m_window.draw(mouseSprite); // draw mouse cursor
			m_window.draw(highlightRect); // draw bouding rect with eraser tool
			m_window.display();
			
			for (auto event = sf::Event{}; m_window.pollEvent(event); )
			{
				highlightRect.setPosition(-ICON_WIDTH, -ICON_HEIGHT); // reset bounding rect off screen

				switch (event.type)
				{
				case sf::Event::Closed:
					m_window.close();
					break;

				case sf::Event::MouseMoved:
                    location = m_window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });
					handleMouseMove(mouseSprite, highlightRect, menu_item, location);
					break;

				case sf::Event::MouseButtonReleased:
                    handleMouseClick(event, menu_item, mouseSprite, loadedmap, location, m_window);
					break;

				default:
					break;
				}

			}
		}
	}
}



// check if we clicked on the board
bool Controller::mouseOverBoard(int x, int y) const
{
	if (x >= ICON_WIDTH && y <= m_board.getSizeRows() * ICON_HEIGHT)
		return true;

	return false;
}

// this function convert mouse coordinates 
// and returns the row/cols of the board
Location Controller::getCellIndexes(int x, int y) const
{
	Location result(0,0);
	result.x = (x - ICON_WIDTH) / ICON_WIDTH;
	result.y = y / ICON_HEIGHT;
    if (result.y >= m_board.getSizeRows())
        result.y = m_board.getSizeRows() - 1;
    if (result.x >= m_board.getSizeCols())
        result.x = m_board.getSizeCols() - 1;
	return result;
}
// input values from user 
// minimum (2,2)
// maximum : what the screen size can display (based on ICON size)
Location Controller::getBoardSize() const {

    // limit to a max value based on display size
    int max_x = sf::VideoMode::getDesktopMode().width / ICON_WIDTH;
    int max_y = sf::VideoMode::getDesktopMode().height / ICON_HEIGHT;

	Location loc(0,0);
	std::cout << "please enter window height: ";
	std::cin >> loc.x;
    if (loc.x > max_x)
        loc.x = max_x;
    else
        if (loc.x < 2)
            loc.x = 2;

	std::cout << "please enter window width: ";
	std::cin >> loc.y; 
    if (loc.y > max_y)
        loc.y = max_y;
    else
        if (loc.y < 2)
            loc.y = 2;

	return loc;
}

void Controller::handleMouseMove(sf::Sprite& mouseSprite,
                                 sf::RectangleShape& highlightRect, int menu_item, sf::Vector2f& location) {


    if (mouseOverBoard((int)location.x, (int)location.y)) {

        Location loc = getCellIndexes((int)location.x, (int)location.y);

        location.x = (float) ICON_WIDTH + loc.x * ICON_WIDTH;
        location.y = (float) loc.y * ICON_HEIGHT;

        if (loc.x < m_board.getSizeCols() && loc.y < m_board.getSizeRows() && m_board.getCell(loc.y, loc.x) == EMPTY) {
            // we are on board, empty cell - show sprite
            mouseSprite.setPosition(location.x, location.y);
        }
        else {
            if (menu_item == ERASER_TOOL) { // show eraser everywhere on map
                mouseSprite.setPosition(location.x, location.y);
                // outline board cell if there is something
                if (m_board.getCell(loc.y, loc.x) != EMPTY)
                    highlightRect.setPosition(location.x, location.y);

            }
            else // hide mouse sprite
                mouseSprite.setPosition(-ICON_HEIGHT, -ICON_HEIGHT);
        }
    }
    else {
        // we are not on board, hide the mouse sprite
        mouseSprite.setPosition(-ICON_HEIGHT, -ICON_HEIGHT);
    }
}

void Controller::handleMouseClick (sf::Event& event,int &menu_item, sf::Sprite& mouseSprite, bool& loadedmap, 
    sf::Vector2f location, sf::RenderWindow& m_window) {
    if (mouseOverBoard((int)location.x, (int)location.y))
    {
        Location l = getCellIndexes(event.mouseButton.x, event.mouseButton.y);

        if (menu_item != -1)
        {
            if (menu_item == ERASER_TOOL) // eraser tool
            {
                m_board.eraseCell(l.y, l.x);
            }
            else if (l.x < m_board.getSizeCols() && l.y < m_board.getSizeRows() && m_board.getCell(l.y, l.x) == EMPTY)
            {
                if (menu_item == PLAYER_TOOL)
                {
                    if (m_board.isPlayerOnBoard())
                    {
                        // erase previous player position
                        Location pl = m_board.getPlayerLocation();
                        m_board.eraseCell(pl.x, pl.y);
                    }
                    m_board.setPlayerLocation(l.y, l.x);

                }

                sf::Texture texture = sf::Texture(m_menu.getTexture(m_menu.getCurrentMenuItem()));
                m_board.setCell(l.y, l.x, m_menu.convertSpriteToChar(m_menu.getCurrentMenuItem()));
            }
        }
    }
    else {
        int save = menu_item;
        menu_item = m_menu.getToolIndex(event.mouseButton.x, event.mouseButton.y);
        if (menu_item >= 0) {
            Location l = getCellIndexes(event.mouseButton.x, event.mouseButton.y);

            if (menu_item == RESET_TOOL)
            {
                // resize map command
                loadedmap = false;
                // hide mouse
                mouseSprite.setPosition(sf::Vector2f(-ICON_HEIGHT, -ICON_HEIGHT));

            }
            else if (menu_item == SAVE_TOOL)
            {
                m_board.saveMap();
                /* show saved screen */
                m_painter.showSaved(m_window);
            }
            else {
                // user choose a menu tool
                m_menu.setCurrentMenuItem(menu_item);
                // change mouse cursor
                mouseSprite = m_menu.buildTransparentCursor(m_menu.getCurrentMenuItem());
                mouseSprite.setPosition(sf::Vector2f(-ICON_HEIGHT, -ICON_HEIGHT));
            }
        }
        else
            menu_item = save;
    }
}

