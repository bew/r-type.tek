/**
 * @file Room.cpp
 * @author Benoit de Chezelles
 * @brief Class for a Room
 */

#include "Room.hpp"

Room::~Room()
{
    if (game != nullptr) {
        delete game;
    }
}
