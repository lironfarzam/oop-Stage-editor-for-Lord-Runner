#pragma once
#include "Board.h"

// do we need to write the map size??
bool Board::saveMap() const
{
	std::ofstream my_file(BOARD_FILE);
	if (my_file.is_open())
	{
		my_file << m_board_size_cols << " " << m_board_size_rows << std::endl;
		for (int i = 0; i < m_board_size_rows; i++) {
			for (int j = 0; j < m_board_size_cols; j++)
				my_file << m_chars[i][j];
			my_file << std::endl;
		}
		my_file.close();
		return true;
	}
	else
		return false;
}


// need to check if we have to write the map size in file??
bool Board::loadMap()
{
	std::ifstream my_file(BOARD_FILE);

	if (my_file)
	{
		my_file >> m_board_size_cols;
		my_file >> m_board_size_rows;
		my_file.ignore(1, '\n');

		m_chars.clear();

		m_chars.resize(m_board_size_rows);
		for (int i = 0; i < m_board_size_rows; i++)
			m_chars[i].resize(m_board_size_cols);


		for (int i = 0; i < m_board_size_rows; i++)
		{
			for (int j = 0; j < m_board_size_cols; j++)
			{
				my_file >> std::noskipws >> m_chars[i][j];
				if (m_chars[i][j] == PLAYER)
					setPlayerLocation(i, j);
			}
			my_file.ignore(1, '\n');
		}

		my_file.close();
		return true;
	}
	return false;
}

void Board::resetMap(int r, int c)
{
	//getBoardSize(); // get from user m_board_cols/m_board_rows

	setSizeRows(r); 
	setSizeCols(c);

	// initialize board of chars
	m_chars.resize(m_board_size_rows);
	for (int i = 0; i < m_board_size_rows; i++)
		m_chars[i].resize(m_board_size_cols);

	for (int i = 0; i < m_board_size_rows; i++) {
		for (int j = 0; j < m_board_size_cols; j++)
		{
			m_chars[i][j] = EMPTY;
		}
	}
}

int Board::getSizeCols() const
{
	return m_board_size_cols;
}

int Board::getSizeRows() const
{
	return m_board_size_rows;
}

void Board::setSizeCols(int s)
{
	m_board_size_cols = s;
}

void Board::setSizeRows(int s)
{
	m_board_size_rows = s;
}



char Board::getCell(int i, int j) const
{
	return m_chars[i][j];
}

void Board::setCell(int i, int j, char c) {
	m_chars[i][j] = c ;
}

void Board::eraseCell(int i, int j)
{
	m_chars[i][j] = EMPTY;
}

bool Board::isPlayerOnBoard() const
{
	return (m_player_location.x >= 0);
}

Location Board::getPlayerLocation() const
{
	return Location(m_player_location.x, m_player_location.y);
}

void Board::setPlayerLocation(int x, int y)
{
	m_player_location.x = x;
	m_player_location.y = y;
}

