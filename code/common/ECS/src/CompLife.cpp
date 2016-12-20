/**
 * @file CompLife.cpp
 * @author Tookie
 * @brief Component implementing the life for game entities.
 *
 */

#include "CompLife.hh"

namespace ECS
{
    namespace Component
    {

        CompLife::CompLife(unsigned int maxLife) : AComponent(LIFE),
                                                   MAX_LIFE(maxLife), _currentLife(MAX_LIFE)
        {

        }

        CompLife::CompLife(unsigned int maxLife, unsigned int currentLife) : AComponent(LIFE),
                                                                             MAX_LIFE(maxLife),
                                                                             _currentLife(currentLife)
        {

        }

        CompLife::~CompLife()
        {

        }

        unsigned int CompLife::getCurrentLife() const
        {
            return _currentLife;
        }

        void CompLife::setCurrentLife(unsigned int life)
        {
            _currentLife = life;
        }

    }

}
