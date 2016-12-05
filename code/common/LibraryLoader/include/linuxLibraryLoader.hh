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
   * @throw LibraryLoaderException
   * @param libName The name of the mibrary to load
   * @return
   */
  LinuxLibraryLoader(const std::string &);
  /**
   * @return A new instance of the class exported by the library specified in constructor.
   *         Caller is responsible for destruction of said instance.
   */
  IGenerator *newInstance(void) const;
  ~LinuxLibraryLoader(void);
private:
  const std::string _libName;
  void *_handle;
  IGenerator *(*_factory)(void);
};

#endif //CONCEPTION_RTYPE_LINUXLIBRARYLOADER_HPP
