/**
 * @file windowFileSystemWatcher.hh
 * @brief Header for window file system watcher class
 * @author Nekhot
 */

#pragma once

#include <windows.h>
#include <winbase.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

/**
 * Forward Declaration
 */
class WindowsFileSystemWatcher;

#include "AFileSystemWatcher.hh"

/**
 * See AFileSystemWatcher
 */
class WindowsFileSystemWatcher : public AFileSystemWatcher {
public:
  /**
   * Construct and begin th process of reading filesystem event
   * 
   * @throw FileSystemWatcherEcception
   * @param dirName The name of the directory to watch change from
   * @return
   */
  WindowsFileSystemWatcher(const std::string &dirName);

  /**
   * @return A vector of pair filename / event
   */
  virtual std::vector<std::pair<std::string, AFileSystemWatcher::Event>> processEvents(void);

private:
  
  /**
   * list the current files in the watcher directory
   */
  std::vector<std::string> _files;
};
