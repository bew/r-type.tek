//
// Created by Pierre Rousselle on 18/11/2016.
//

#ifndef CONCEPTION_RTYPE_FILESYSTEMWATCHER_HPP
#define CONCEPTION_RTYPE_FILESYSTEMWATCHER_HPP

#include <string>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>
#include <algorithm>

/**
 * Abstarct base class for filesystemwatcher
 */
class AFileSystemWatcher {
public:
  enum Event {
    Add,
    Change,
    Remove
  };
  /*
   * Construct a filesystemwatcher for specific directory
   *
   * @param directoryName: name of directory to watch
   */
  AFileSystemWatcher(const std::string &directoryName);
  virtual ~AFileSystemWatcher(void);

  /*
   * synchronously process list of event that happend to 
   *
   * @return: a vector of event, each event being a pair of filename and event
   * @throw: FileSystemWAtcherException
   */
  virtual std::vector<std::pair<std::string, Event>> processEvents(void) = 0;

protected:
  std::string _directoryName;
};

/**
 * Exception thrown by FileSystemWatcher
 */
class FileSystemWatcherException : public std::runtime_error {
public:
    FileSystemWatcherException(const std::string &error);
};

/**
 * Allow user to write plateform independent code.
 *
 * Exemple:
 *  #include "AFileSystemWatcher.hpp"
 *  FileSystemWatcher exemple("some params");
 *
 *  Be carefull to compile only the target os corresponding implementation, if there is one
 */
#ifdef __linux__
    #include "linuxFileSystemWatcher.hh"
    typedef LinuxFileSystemWatcher FileSystemWatcher;
#elif defined _WIN32
    #include "windowsFileSystemWatcher.hh"
    typedef  WindowsFileSystemWatcher FileSystemWatcher;
#endif

#endif //CONCEPTION_RTYPE_FILESYSTEMWATCHER_HPP
