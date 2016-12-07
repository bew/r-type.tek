//
// Created by Pierre Rousselle on 18/11/2016.
//

#ifndef CONCEPTION_RTYPE_ALIBRARYLOADER_HPP
#define CONCEPTION_RTYPE_ALIBRARYLOADER_HPP

#include <memory>
class IGenerator;

/**
 * Abstract class for all LibraryLoader
 */
class ALibraryLoader {
public:
  /**
   * Construct a instance of the generator on the heap
   *
   * @return A new instance of the IGenerator based class exported into the loaded library
   */
  virtual IGenerator *newInstance(void) const = 0;

  /**
   * Virtual dtor
   */
  virtual ~ALibraryLoader(void) {};
};

/**
 * Allow user to write plateform independent code.
 *
 * Exemple:
 *  #include "ALibraryLoader.hpp"
 *  LibraryLoader exemple("some library");
 *
 *  Be carefull to compile only the target system corresponding implementation
 */
#ifdef __linux__
#include "linuxLibraryLoader.hh"
    typedef LinuxLibraryLoader LibraryLoader;
#elif defined _WIN32
#include "windowsLibraryLoader.hh"
    typedef WindowsLibraryLoader LibraryLoader;
#endif

/**
 * Exception thrown by LibraryLoader
 * in case of failure in constructor
 */
class LibraryLoaderException : public std::runtime_error {
public:
  /**
   * Construct a LibraryLoader EXception with a message
   *
   * @param e The reason taht lead to throwing this exception. It can be accessed through the `what` method
   */
  LibraryLoaderException(const std::string &e) : std::runtime_error(e) {};
};

#include "libraryUtils.hh"

#endif //CONCEPTION_RTYPE_ALIBRARYLOADER_HPP
