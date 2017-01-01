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

	  static const int FILTER_TEAM = 0b1 << 0;
	  static const int ENEMY = 0b1 << 0;//can hurt player
	  static const int PLAYER = 0b0 << 0;//can hurt enemy
	  
	  static const int FILTER_TYPE = 0b1 << 1;
	  static const int PROJECTILE = 0b0 << 1;//kill on pv < 0
	  static const int CHARACTER = 0b1 << 1;//kill on contact
	  
	  
	  
            /**
             * Constructor.
             * @param type The type of the entity which will possess this component.
             */
            CompType(int type);
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
             * @return A pointer to a new CompSprite with a state similar to this
             */
            virtual AComponent *clone(void) const;

            /**
             * @return a document describing the component state
             */
            virtual bson::Document serialize() const;

            /**
             * @param document State to write into the component
             */
            virtual void deserialize(const bson::Document& document);

            /**
             * Type of the entity.
             */
            int  _type;
        };
    }
}
