/**
 * @file linuxLibraryLoader.cpp
 * @brief Implementation for linux dynamic library loading
 * @author Nekhot
 */

#include "linuxLibraryLoader.hh"

LinuxLibraryLoader::LinuxLibraryLoader(const std::string &libName) : _libName(libName) {
    _handle = dlopen(_libName.c_str(), RTLD_LAZY);
    if (_handle == nullptr)
      throw LibraryLoaderException("Unable to load library \'" + _libName + "' : " + std::string(dlerror()));
    _factory = reinterpret_cast<IGenerator *(*)(void)>(dlsym(_handle, EXPAND_STRING(EXPORT_SYMBOL_NAME)));
    if (_factory == nullptr)
      throw LibraryLoaderException("Unable to find export symbol " + std::string(dlerror()));
};

IGenerator *LinuxLibraryLoader::newInstance(void) const {
    return _factory();
};

LinuxLibraryLoader::~LinuxLibraryLoader(void) {
  dlclose(_handle);
};
