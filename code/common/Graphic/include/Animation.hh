#ifndef ANIMATION_HH
#define ANIMATION_HH

#include <string>

namespace graphic {

  /**
   * This class is holding the state of a single animation.
   * This is one of the member of an hypothetic AnimatedSprite Component.
   */
  class Animation {
  public:
    
    /**
     * Constructor for animation
     *
     * @param name: the name of the animation
     * @param tick: the curent tick
     */
    Animation(const std::string &name, int tick);
    
    /**
     * The name of the animation
     */
    const std::string animationName;

    /**
     * The tick at which tha animation was set
     */
    const int tickOffset;
  };

}

#endif
