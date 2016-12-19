
/**
 * @file AComponent.cpp
 * @author Alexis.
 * @brief This abstract class is destinated to manipulate the components.
 *
 */

#include "AComponent.hh"

namespace ECS {
    namespace Component {

	AComponent::AComponent(const std::string &type)
	    : _type(type)
	{}

	AComponent::~AComponent()
	{}
	
        const std::string	&AComponent::getType() const
	{
	    return _type;
	}
    }
}
