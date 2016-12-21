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

        CompLife::CompLife(unsigned int maxLife) : AComponent(),
                                                   _maxLife(maxLife), _currentLife(_maxLife)
        {

        }

        CompLife::CompLife(unsigned int maxLife, unsigned int currentLife) : AComponent(),
                                                                             _maxLife(maxLife),
                                                                             _currentLife(currentLife)
        {

        }

        CompLife::~CompLife()
        {

        }

        const std::string	&CompLife::getType() const
        {
            return Component::LIFE;
        }

    }

}
