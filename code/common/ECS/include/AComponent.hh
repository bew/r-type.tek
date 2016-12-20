
/**
 * @file AComponent.hh
 * @author Alexis.
 * @brief This abstract class is destinated to manipulate the components.
 *
 */

#pragma once

#include <string>
#include <map>

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
         * Abstract class for components.
         */
        class AComponent
        {
        public:
            /**
             * Constructor
             * @param type The type of the component.
             */
            AComponent();

            /**
             * Virtual destructor.
             */
            virtual ~AComponent();

            /**
             * Getter for the component type.
             * @return the component type.
             */
            virtual const std::string &getType() const = 0;
        };

    }
}
