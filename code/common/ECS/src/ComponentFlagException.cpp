/**
 * @file ComponentFlagException.hh
 * @author Tookie
 * @brief class for compponents flags exception.
 */


#include "ComponentFlagException.hh"

namespace ECS
{
    namespace Component
    {
        ComponentFlagException::ComponentFlagException(const std::string &error): std::runtime_error(error)
        {}
    }
}