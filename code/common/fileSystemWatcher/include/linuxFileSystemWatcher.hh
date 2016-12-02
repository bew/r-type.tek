//
// Created by Pierre Rousselle on 18/11/2016.
//

#ifndef CONCEPTION_RTYPE_LINUXFILESYSTEMWATCHER_HPP
#define CONCEPTION_RTYPE_LINUXFILESYSTEMWATCHER_HPP

#include <sys/types.h>
#include <dirent.h>

class LinuxFileSystemWatcher;

#include "AFileSystemWatcher.hh"

/**
 * See AFileSystemWatcher
 */
class LinuxFileSystemWatcher : public AFileSystemWatcher {
public:
  /**
   * Construct and begin the process of reading filesystem event
   *
   * @throw FileSystemWatcherException
   * @param dirName The name of the directory to watch for change
   */
  LinuxFileSystemWatcher(const std::string &dirName);
  
  virtual std::vector<std::pair<std::string, AFileSystemWatcher::Event>> processEvents(void);
  
private:
  std::vector<std::string> _files;
};

#endif //CONCEPTION_RTYPE_LINUXFILESYSTEMWATCHER_HPP_
