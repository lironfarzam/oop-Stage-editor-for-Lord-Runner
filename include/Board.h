#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>

#include "Constants.h"
#include "Location.h"

using std::vector;

// a class to manage the board of characters
// independent from graphics
//
class Board {
public:
	bool saveMap() const;
	bool loadMap();
	void resetMap(int, int);

	int getSizeCols() const;
	int getSizeRows() const;

	void setSizeCols(int);
	void setSizeRows(int);


	char getCell(int i, int j) const;
	void setCell(int i, int j, char c) ;
	void eraseCell(int, int);

	bool isPlayerOnBoard() const;
	Location getPlayerLocation() const;
	void setPlayerLocation(int,int);

private:

	vector <vector<char>> m_chars;
	int m_board_size_cols = 0; // number of cols
	int m_board_size_rows = 0; // number of rows

	Location m_player_location{ -1,-1 }; // player initial location

};