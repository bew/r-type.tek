//
// Created by Pierre Rousselle on 17/11/2016.
//

#ifndef CONCEPTION_RTYPE_LINUXLIBRARYLOADER_HPP
#define CONCEPTION_RTYPE_LINUXLIBRARYLOADER_HPP

#include <string>
#include <dlfcn.h>
#include <stdexcept>

class LinuxLibraryLoader;

#include "ALibraryLoader.hh"

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

#endif //CONCEPTION_RTYPE_LINUXLIBRARYLOADER_HPP
