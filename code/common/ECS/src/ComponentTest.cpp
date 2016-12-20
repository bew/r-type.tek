
/**
 * @file ComponentTest.cpp
 * @author Alexis.
 * @brief Dummy component for testing purposes.
 *
 */

#include "AComponent.hh"
#include "ComponentTest.hh"
#include <iostream>

namespace ECS
{
    namespace Component
    {

        ComponentTest::ComponentTest()
                : AComponent(), _count(0)
        {}

        ComponentTest::~ComponentTest()
        {}

        void ComponentTest::increment()
        {
            _count++;
            std::cout << "J'incremente ! le compte est maintenant a :" << _count << std::endl;
        }

        unsigned ComponentTest::getCount() const
        {
            return _count;
        }

        const std::string	&ComponentTest::getType() const
        {
            return Component::TEST;
        }
    }
}
