/**
 * @file AComponent.cpp
 * @author Alexis.
 * @brief This abstract class is destinated to manipulate the components.
 *
 */

#include "AComponent.hh"

namespace ECS
{
    namespace Component
    {

        AComponent::AComponent(short flags): _flags(flags)
        {}

        AComponent::~AComponent()
        {}

        bool AComponent::isFlagged(short mask) const
        {
            return ((_flags & mask) == mask);
        }

        void AComponent::addFlag(short flag)
        {
            _flags |= flag;
        }

        void AComponent::unFlag(short flag)
        {
            _flags &= flag;
        }
    }
}
