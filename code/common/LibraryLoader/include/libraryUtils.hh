//
// Created by Pierre Rousselle on 17/11/2016.
//

#ifndef CONCEPTION_RTYPE_LIB_H
#define CONCEPTION_RTYPE_LIB_H

#include <type_traits>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "ALibraryLoader.hh"

/**
 * Placeholder class for entity
 */
class Entity {};
/**
 * Placeholder class for storing game status
 */
class EngineStatus {
  /*
    TO UPDATE
    Hold informations like time since begining of level,
    choosen difficulty (idk)
    frame counter,
    maybe the server log ... things like that
  */
};

/**
 * Base interface from which every dynamically loaded class must inherit
 */
class IGenerator {
public:
  IGenerator(void) {};
  virtual ~IGenerator(void) {};

  /**
   * Method to access the name of the generator.
   *
   * @return The name of the generator.
   */
  virtual const std::string &getName(void) const = 0;
  
  /**
   * This take the current entity, and return a list of new entity to add.
   * The pupose is to generate a whole level. It should be called each n frame. 
   * It should not add or edit player entity.
   *
   * @return Vector of new entity to add
   * @param Vector of current entity
   */
  virtual std::vector<Entity>process(std::vector<Entity> &, EngineStatus &) = 0;
};

/**
 * What does it do:
 * STRING(test) => "test"
 * #define ANOTHER_MACRO test
 * STRING(ANOTHER_MACRO) => "ANOTHER_MACRO"
 */
#define STRING(s) #s

/**
 * What does it do:
 * #define ANOTHER_MACRO test
 * EXPAND_STRING(ANOTHER_MACRO) => "test"
 */
#define EXPAND_STRING(s) STRING(s)


/**
 * The name of the exported symbols
 */
#define EXPORT_SYMBOL_NAME export_library_factory

/**
 * Usefull for code factorisation issue.
 * See macro EXPORT
 */
#ifdef _WIN32
    #define EXPORT_DECORATOR __declspec(dllexport)
#elif defined __linux__
    #define EXPORT_DECORATOR
#endif

/**
 * Macro for exporting the dynamically loaded class, to add in the library implementation once.
 *
 * Exemple:
 *  class libhello : public IGenerator {...};
 *  EXPORT(libhello);
 *
 *  Target must have a default constructor.
 */
#define EXPORT(TARGET)                                                                      \
extern "C" {                                                                                \
  EXPORT_DECORATOR IGenerator *EXPORT_SYMBOL_NAME(void) {				    \
    static_assert(std::is_default_constructible<TARGET>::value,				    \
      "Exported type must have a public default constructor");				    \
    return new TARGET();  								    \
  }                                                                                         \
}                                                                                           \

#endif //CONCEPTION_RTYPE_LIB_H
