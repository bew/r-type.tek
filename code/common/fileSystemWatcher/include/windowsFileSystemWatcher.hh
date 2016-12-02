//
// Created by Pierre Rousselle on 18/11/2016.
//

#ifndef CONCEPTION_RTYPE_WINDOWSFILESYSTEMWATCHER_HPP
#define CONCEPTION_RTYPE_WINDOWSFILESYSTEMWATCHER_HPP

#include <windows.h>
#include <winbase.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

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
   * @param diName The name of the directory to watch change from
   * @return
   */
  WindowsFileSystemWatcher(const std::string &dirName);
  
  virtual std::vector<std::pair<std::string, AFileSystemWatcher::Event>> processEvents(void);

private:
    std::vector<std::string> _files;
};

#endif //CONCEPTION_RTYPE_WINDOWSFILESYSTEMWATCHER_HPP
