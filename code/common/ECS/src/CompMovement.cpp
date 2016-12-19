
/**
 * @file CompMovement.hh
 * @author Alexis.
 * @brief Component implementing the movement for game entities.
 *
 */

#include "AComponent.hh"
#include "CompMovement.hh"

namespace ECS {
    namespace Component {

        CompMovement::CompMovement()
            : AComponent(MOVEMENT), _coo(0, 0), _dir(0.f, 0.f), _speed(0.f), _advance(0.f, 0.f)
        {}

        CompMovement::~CompMovement()
        {}
    }
}
