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
        CompType::CompType(int type)
            : AComponent(CLONABLE_MASK | SERVER_SERIALIZABLE_MASK), _type(type)
        {
        }

        CompType::~CompType()
        {
        }

        const std::string       &CompType::getType() const
        {
            return TYPE;
        }

        AComponent *CompType::clone(void) const {
	        return new CompType(_type);
        }

        bson::Document CompType::serialize() const {
            bson::Document doc;
            doc << u8"type" << _type;
            return doc;
        };

        void  CompType::deserialize(const bson::Document& document) {
            document[u8"type"] >> _type;
        }
    }
}
