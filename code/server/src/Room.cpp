/**
 * @file Room.cpp
 * @author Benoit de Chezelles
 * @brief Class for a Room
 */

#include "Room.hpp"

Room::~Room()
{
    if (game != nullptr) {
        if (!game->isDone()) {
            //TODO : handle if the game is already start ? Possible ?
        }
        else
            delete game;
    }
}
