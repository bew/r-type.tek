
/**
 * @file ComponentTest.hh
 * @author Alexis.
 * @brief Dummy component for testing purposes.
 *
 */

#pragma once

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

        static const std::string TEST = "test";

        /**
         * Dummy component for testing purpose.
         */
        class ComponentTest : public AComponent
        {
        public:
            /**
             * Constructor.
             */
            ComponentTest();

            /**
             * Destructor.
             */
            ~ComponentTest();

            /**
             * Add 1 to the count.
             */
            void increment();

            /**
             * Return the count.
             * @return The count.
             */
            unsigned getCount() const;

            /**
             * get the type of component
             * @return string that reprents his type
             */
            virtual const std::string &getType() const;

        private:
            /**
             * A dummy data for testing purpose.
             */
            unsigned _count;
        };

    }
}
