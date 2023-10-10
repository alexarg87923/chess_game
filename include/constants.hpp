#pragma once

#include <map>
#include <SFML/System/Vector2.hpp>

#include "types.hpp"

inline const unsigned short BOARD_ROW = 8;
inline const unsigned short BOARD_COL = 8;
inline const unsigned short BOARD_SIZE = 64;

inline std::map<Position, sf::Vector2f> COORDINATES;
inline sf::Vector2f SIZE;