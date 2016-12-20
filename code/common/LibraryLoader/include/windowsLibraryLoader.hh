/**
 * @file windowsLibraryLoader.hh
 * @brief Header for windows dynamic library loading
 * @author Nekhot
 */

#pragma once

#include <string>
#include <windows.h>
#include <stdexcept>

/**
 * Forward declaration
 */
class WindowsLibraryLoader;

#include "ALibraryLoader.hh"

/**
 * Class for loading dynamic library
 */
class WindowsLibraryLoader : public ALibraryLoader {
public:

  /**
   * Open the library
   *
   * @throw LibraryLoaderException
   * @param libName The name of the library to load
   * @return
   */
  WindowsLibraryLoader(const std::string &libName);

  /**
   * @return A new instance of the class exported by the library specified in constructor.
   *         Caller is responsible for destruction of said instance.
   */
  IGenerator *newInstance(void) const;
  
  /**
   * Close the library
   */
  ~WindowsLibraryLoader(void);

private:

  /**
   * File name of the dll to load
   */
  const std::string _libName;

  /**
   * Handl of the openened dll
   */
  HMODULE _handle;

  /**
   * Adress of factory function exported by the loaded dll
   */
  IGenerator *(*_factory)(void);
};
