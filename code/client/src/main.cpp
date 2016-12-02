//
// Created by Pierre Rousselle on 18/11/2016.
//

#include <iostream>
#include <string>
#include <unistd.h>

#include "ALibraryLoader.hh"
#include "Dependent_ptr.hpp"
#include "AFileSystemWatcher.hh"

Dependent_ptr<IGenerator, LibraryLoader> my_safe_factory(const std::string &path) {
  // We create a LibraryLoader, inside a shared ptr.
  std::shared_ptr<LibraryLoader> module(new LibraryLoader(path));
  // We create a instance of the library, but dependent of the previous libraryLoader.
  Dependent_ptr<IGenerator, LibraryLoader> instance(module->newInstance(), module);
  // We return the instance. Please note that c++ should delete the LibraryLoader. So instance (whose code is stored inside the library) should cause segfault everytime we dare touching it
  return instance;
}

void handleLib(std::string file, FileSystemWatcher::Event event, std::string path) {
 
  if (event == FileSystemWatcher::Add) {

    //HOW TO USE, CLEAN AND NICE EXEMPLE:
    //Safe and easyly prevent memory leak

    try {
      Dependent_ptr<IGenerator, LibraryLoader> instance = my_safe_factory(path + "/" + file);
      // Here we have no more reference on the library, but the instance still work :
      std::cout << "Loaded module : '" << instance->getName() << "'" << std::endl;
      // Deleting the instance (or the last one if there is multiple) will destroy the said instance AND the loader.
      // Here it's deleted automatically when exiting block
    }
    catch (const LibraryLoaderException &error) {
      std::cerr << "LibraryLoaderException : " << error.what() << std::endl;
    }

    // HOW TO USE, LAZY EXEMPLE:
    // This work but you have to be extra carefull not to cause sagfault and/or memeory leak.
    
     try {
       LibraryLoader module(path + "/" + file);
       IGenerator *instance = module.newInstance();
       std::cout << "Lazilly Loaded module : '" << instance->getName() << "'" << std::endl;
       // Here you have to delete instance BEFORE module. Really. Else it will explode.
       delete instance;
     }
     catch (const LibraryLoaderException &error) {
       std::cerr << "LibraryLoaderException : " << error.what() << std::endl;
     }  
  }
}

int main(int ac, char**av) {
  char stop = 0;
  FileSystemWatcher watcher("./modules");
  std::vector<std::pair<std::string, AFileSystemWatcher::Event>> events; 

  puts("Hit enter to stop the program");
  while (stop != '\n') {
    events = watcher.processEvents();
    for (auto i = events.begin(); i < events.end(); i++) {
      handleLib((*i).first, (*i).second, "./modules");
    }
    read(0, &stop, 1);
  }
};
