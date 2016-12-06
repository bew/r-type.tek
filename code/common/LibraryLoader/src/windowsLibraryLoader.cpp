//
// Created by Pierre Rousselle on 18/11/2016.
//
#include <iostream>
#include "windowsLibraryLoader.hh"

WindowsLibraryLoader::WindowsLibraryLoader(const std::string &libName) : _libName(libName) {
    _handle = LoadLibraryEx(_libName.c_str(), nullptr, LOAD_LIBRARY_SEARCH_APPLICATION_DIR);
    if (_handle == nullptr)
        throw LibraryLoaderException("Unable to load library \'" + _libName + "'");
    _factory = reinterpret_cast<IGenerator *(*)(void)>(GetProcAddress(_handle, EXPAND_STRING(EXPORT_SYMBOL_NAME)));
    if (_factory == nullptr)
        throw LibraryLoaderException("Unable to find '" + std::string(STRING(EXPORT_SYMBOL_NAME)) + "' symbol");
};

IGenerator *WindowsLibraryLoader::newInstance(void) const {
    return _factory();
};

WindowsLibraryLoader::~WindowsLibraryLoader(void) {
    FreeLibrary(_handle);
};
