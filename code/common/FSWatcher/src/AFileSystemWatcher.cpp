#include "AFileSystemWatcher.hh"

AFileSystemWatcher::AFileSystemWatcher(const std::string &directoryName) :
  _directoryName(directoryName)
{}

AFileSystemWatcher::~AFileSystemWatcher(void)
{}

FileSystemWatcherException::FileSystemWatcherException(const std::string &e) :
  std::runtime_error(e)
{}