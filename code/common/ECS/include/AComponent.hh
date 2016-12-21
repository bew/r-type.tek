
/**
 * @file AComponent.hh
 * @author Alexis.
 * @brief This abstract class is destinated to manipulate the components.
 *
 */

#pragma once

#include <string>
#include <map>
#include "BSON/Document.hh"

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
         * represents a component flag exception, he's throw when flag error occured
         */
        using ComponentFlagException = std::runtime_error;

        /**
         * Mask for test if a componenet is serializable
         */
        static const short SERIALIZABLE_MASK = 1 << 0;

        /**
         * Abstract class for components.
         */
        class AComponent
        {
        public:
            /**
             * Constructor
             * @param flags The flags of the component.
             */
            AComponent(short flags = 0);

            /**
             * Virtual destructor.
             */
            virtual ~AComponent();

            /**
             * Getter for the component type.
             * @return the component type.
             */
            virtual const std::string &getType() const = 0;

            /**
             * Test if a component has a flag or not
             * @param mask the mask for test the flag
             * @return true if the component has this flag else false
             */
            bool hasFlag(short mask) const;

            /**
             * add flag to a component
             * @param flag flag to add
             */
            void addFlag(short flag);

            /**
             * delete flag to a component
             * @param flag flag to delete
             */
            void unFlag(short flag);

            /**
             * serialize the component
             * @return document contains component's attributes
             * @throw ComponentFlagException if the component is not serialisable or if the component does not override this method
             */
            virtual bson::Document serialize() const;

            /**
             * desialize a component by the document
             * @param document that contains all attributes of the component
             * @throw ComponentFlagException if the component is not serialisable or if the component does not override this method
             */
            virtual void deserialize(const bson::Document& document);
            /**
             * flags of the component
             */
            short _flags;
        };

    }

}
