/**
 * @file CompBlueprint.hh
 * @author Nekhot
 * @brief Component for holding entity blueprint (for projectile and monster)
 */

#pragma once

#include <string>
#include <unordered_map>

#include "AComponent.hh"
#include "CompMovement.hh"
#include "Entity.hh"

namespace ECS {
  namespace Component {

    /**
     * The type of the asset component
     */
    static const std::string BLUEPRINT = "blueprint";

    /**
     * Component for holding system entity standard asset.
     */
    class CompBlueprint : public AComponent {
    public:

      /**
       * Default constructor
       *
       * @param offset The base id to begin with. Default to 5 (0 s reserved by systemEntity, 1, 2, 3, 4 are reserved for player
       */
      CompBlueprint(int offset = 5);

      /**
       * Default virtual destructor
       */
      ~CompBlueprint(void);
      
      /**
       * Store each blueprint by name
       */
      std::unordered_map<std::string, std::vector<ECS::Component::AComponent *>> blueprints;

      /**
       * @return nextID and post increment it
       */
      int getNextID();
      
      /**
       * @return ECS::Component::BLUEPRINT
       */
      virtual const std::string &getType() const;

      /**
       * Helper function
       *
       * @param name Name of the blueprint to spawn
       * @param owner Optionnal owner.
       * @return The new entity
       * @throw ComponentFlagException if the entity couldn't be spawn
       */
      Entity::Entity *spawn(const std::string &name, Entity::Entity *owner = nullptr);

    protected:
      
      int nextID;
    };
  }
}
