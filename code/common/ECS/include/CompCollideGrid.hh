/**
 * @file CompCollideGrid.hh
 * @author Alexis.
 * @brief A collide grid in the system entity, used to check the collisions
 * only between near components.
 */

#pragma once

#include <vector>
#include "AComponent.hh"

/**
 * Namespace of ECS.
 */
namespace ECS {

  /**
   * Namespace of components.
   */
  namespace Component {


      
    /**
     * Component to optimize collision calculation.
     */
    class CompCollideGrid : public AComponent {
    public:
        CompCollideGrid();
        ~CompCollideGrid();

        std::array<std::array<std::vector<Entity::Entity *>, 16>, 16>   _grid;
    };

  }
}
