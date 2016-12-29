/**
 * @file CompType.hh
 * @author Alexis.
 * @brief This component is a simple information about the type of an entity.
 */

#include "CompType.hh"

/**
 * Namespace of ECS.
 */
namespace ECS
{
    /**
     * Namespace of components.
     */
    namespace Component
    {
        CompType::CompType(CompType::Type type)
            : _type(type)
        {
        }

        CompType::~CompType()
        {
        }

        const std::string       &CompType::getType() const
        {
            return TYPE;
        }
    }
}
