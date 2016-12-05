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
  const std::string _libName;
  HMODULE _handle;
  IGenerator *(*_factory)(void);
};

#endif //CONCEPTION_RTYPE_WINDOWSLIBRARYLOADER_HPP
