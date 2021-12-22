#include "Painter.h"


Painter::Painter(Menu &m) :m_menu(m)
{
    m_cover.loadFromFile("cover.png");
    m_saved.loadFromFile("filesaved.png");
}

// draw the map on window
// params: the board of chars and the window
void Painter::printMap(sf::RenderWindow& window, Board& m_board) const {

    sf::RectangleShape rect(sf::Vector2f((float)m_board.getSizeCols() *ICON_WIDTH, (float)(ICON_HEIGHT)* m_board.getSizeRows()));
    rect.setPosition(ICON_HEIGHT, 0);
    rect.setFillColor(sf::Color::Black);
    rect.setOutlineThickness(2);
    rect.setOutlineColor(sf::Color(150, 150, 150));
    window.draw(rect);

    for (int i = 0; i < m_board.getSizeRows(); i++) {
        for (int j = 0; j < m_board.getSizeCols(); j++)
        {
            if (m_board.getCell(i,j)!= EMPTY) {
                sf::Sprite sp = m_menu.convertCharToSprite(m_board.getCell(i, j));
                sp.setPosition((float) ICON_WIDTH + (j * ICON_WIDTH), (float) i * ICON_WIDTH );
                window.draw(sp);
            }
        }
    }
}

// print the welcome screen for entering map size
void Painter::printCover(sf::RenderWindow& m_window) const {

    m_window.setView(sf::View(sf::FloatRect(0, 0, COVER_WIDTH, COVER_HEIGHT)));
    m_window.setSize(sf::Vector2u(COVER_WIDTH, COVER_HEIGHT));
    m_window.clear();

    sf::Sprite sp = sf::Sprite(m_cover);
    sp.setPosition(sf::Vector2f(0, 0));

    m_window.draw(sp);
    m_window.display();
    
}

void Painter::showSaved(sf::RenderWindow& m_window) const {

    sf::Sprite sp = sf::Sprite(m_saved);
    sp.setPosition(sf::Vector2f(ICON_WIDTH, 0));

    m_window.draw(sp);
    m_window.display();
    // show message for 2 seconds
    sf::sleep(sf::milliseconds(2000));
}
