/**
 * @file linuxLibraryLoader.hh
 * @brief Header for linux dynamic library loading
 * @author Nekhot
 */

#pragma once

#include <string>
#include <dlfcn.h>
#include <stdexcept>

/**
 * Forward declaration
 */
class LinuxLibraryLoader;

#include "ALibraryLoader.hh"

/**
 * Class for loading dynamic library
 */
class LinuxLibraryLoader : public ALibraryLoader {
public:
  
  /**
   * Open the library and load symbols 
   *
   * @throw LibraryLoaderException
   * @param libName The name of the library to load
   * @return
   */
  LinuxLibraryLoader(const std::string &);
  
  /**
   * @return A new instance of the class exported by the library specified in constructor.
   *         Caller is responsible for destruction of said instance.
   */
  IGenerator *newInstance(void) const;

  /**
   * Close the library
   */
  ~LinuxLibraryLoader(void);

private:
  /**
   * Name of the file of library to load
   */
  const std::string _libName;

  /**
   * Result of dlopen
   */
  void *_handle;

  /**
   * Adress of the factory function exported in the library
   */
  IGenerator *(*_factory)(void);
};
