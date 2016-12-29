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

        bool AComponent::hasFlag(short mask) const
        {
            return (bool(_flags & mask));
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
            if (this->hasFlag(SERIALIZABLE_MASK))
                throw ComponentFlagException(std::string("Component ") + this->getType() + " does not override serialize method");
            else
                throw ComponentFlagException(std::string("Component ") + this->getType() + " is not serializable");
        }

        void AComponent::deserialize(const bson::Document& document)
        {
            if (this->hasFlag(SERIALIZABLE_MASK))
                throw ComponentFlagException(std::string("Component ") + this->getType() + " does not override deserialize method");
            else
                throw ComponentFlagException(std::string("Component ") + this->getType() + " is not serializable");
        }
      
      AComponent *AComponent::clone(void) const {
	if (this->hasFlag(CLONABLE_MASK))
	  throw ComponentFlagException(std::string("Component ") + this->getType() + " does not override clone method");
	else
	  throw ComponentFlagException(std::string("Component ") + this->getType() + " is not clonable");
      }
      
    }
}
