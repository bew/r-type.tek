/**
 * @file AFileSystemWatcher.cpp
 * @brief Implementation for abstract file system watcher class
 * @author Nekhot
 */

#include "AFileSystemWatcher.hh"

AFileSystemWatcher::AFileSystemWatcher(const std::string &directoryName) :
  _directoryName(directoryName)
{}

AFileSystemWatcher::~AFileSystemWatcher(void)
{}

FileSystemWatcherException::FileSystemWatcherException(const std::string &e) :
  std::runtime_error(e)
{}
