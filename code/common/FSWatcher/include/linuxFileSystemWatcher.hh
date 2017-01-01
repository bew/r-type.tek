/**
 * @file linuxFileSystemWatcher.hh
 * @brief Header for linux file system watcher class
 * @author Nekhot
 */

#pragma once

#include <sys/types.h>
#include <dirent.h>

/**
 * Forward declaration
 */
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

  /**
   * @return A vector of pair filename / event
   */
  virtual std::vector<std::pair<std::string, AFileSystemWatcher::Event>> processEvents(void);

  /**
   * list the current files in the watcher directory
   */
  std::vector<std::string> _files;
};
