/**
 * @file CompType.hh
 * @author Alexis.
 * @brief This component is a simple information about the type of an entity.
 */

#pragma once

#include <string>
#include "AComponent.hh"

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
        /**
         * Component type id.
         */
        static const std::string TYPE = "type";
        
        /**
         * Component featuring the type. 
         */
        class CompType : public AComponent {
        public:
            /**
             * Types of entity.
             */
            enum Type
            {
                PLAYER,
                ENEMY,
                PLAYER_SHOOT,
                ENEMY_SHOOT,
                SYSTEM
            };

            /**
             * Constructor.
             * @param type The type of the entity which will possess this component.
             */
            CompType(Type type);
            /**
             * Destructor.
             */
            ~CompType();

            /**
             * Getter for the component type.
             * @return the component type.
             */
            virtual const std::string &getType() const;

            /**
             * Type of the entity.
             */
            const Type  _type;
        };
    }
}
