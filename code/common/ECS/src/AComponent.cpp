/**
 * @file AComponent.cpp
 * @author Alexis.
 * @brief This abstract class is destinated to manipulate the components.
 *
 */

#include "AComponent.hh"
#include "ComponentFlagException.hh"

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
            _flags &= ~flag;
        }

        bson::Document AComponent::serialize() const
        {
            if (this->isFlagged(SERIALIZABLE_MASK))
                throw ComponentFlagException("Component does not override this method");
            else
                throw ComponentFlagException("Component is not serializable");
        }

        void AComponent::deserialize(const bson::Document& document)
        {
            if (this->isFlagged(SERIALIZABLE_MASK))
                throw ComponentFlagException("Component does not override this method");
            else
                throw ComponentFlagException("Component is not serializable");
        }
    }
}
