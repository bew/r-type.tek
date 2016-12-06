//
// Created by Pierre Rousselle on 18/11/2016.
//

#ifndef CONCEPTION_RTYPE_WINDOWSLIBRARYLOADER_HPP
#define CONCEPTION_RTYPE_WINDOWSLIBRARYLOADER_HPP

#include <string>
#include <windows.h>
#include <stdexcept>

class WindowsLibraryLoader;

#include "ALibraryLoader.hh"

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

#endif //CONCEPTION_RTYPE_WINDOWSLIBRARYLOADER_HPP
