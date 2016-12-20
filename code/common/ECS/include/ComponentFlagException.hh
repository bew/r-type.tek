/**
 * @file ComponentFlagException.hh
 * @author Tookie
 * @brief class for compponents flags exception.
 */

#pragma once

#include <stdexcept>

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
         * Representation of components flags exception
         */
        class ComponentFlagException : public std::runtime_error
        {
        public:
            /**
             * Constructor of ComponentFlagException
             * @param error: message of the exception
             */
            ComponentFlagException(const std::string &error);
        };

    }

}