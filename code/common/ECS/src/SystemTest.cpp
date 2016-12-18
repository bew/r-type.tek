
/**
 * @file SystemTest.cpp
 * @author Alexis.
 * @brief Dummy system for testing purposes.
 *
 */

#include "AComponent.hh"
#include "ComponentTest.hh"
#include "SystemTest.hh"
#include "World.hh"

namespace ECS {
    namespace System {

	SystemTest::SystemTest()
	{}
	
	SystemTest::~SystemTest()
	{}

	void	SystemTest::update(WorldData &data)
	{
	    for (auto &entity : data._gameEntities)
	    {
		Component::ComponentTest *comp = static_cast<Component::ComponentTest *>(
		    entity->getComponent(Component::TEST));

		if (comp != nullptr)
		    comp->increment();
	    }
	}

    }
}
