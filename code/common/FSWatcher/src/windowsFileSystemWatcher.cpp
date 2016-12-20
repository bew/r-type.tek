/**
 * @file windowsFileSystemWatcher.cpp
 * @brief Implementation for windows file system watcher class
 * @author Nekhot
 */

#include "windowsFileSystemWatcher.hh"

WindowsFileSystemWatcher::WindowsFileSystemWatcher(const std::string &dirName) :
  AFileSystemWatcher(dirName)
{}
  
std::vector<std::pair<std::string, AFileSystemWatcher::Event>> WindowsFileSystemWatcher::processEvents(void) {
  WIN32_FIND_DATA findHandle;
  HANDLE directoryFileHandle;
  std::vector<std::string> newFiles;
  std::vector<std::string> currentFiles;
  std::vector<std::pair<std::string, AFileSystemWatcher::Event>> events;

  if ((directoryFileHandle = FindFirstFile((this->_directoryName + "\\*").c_str(), &findHandle)) == INVALID_HANDLE_VALUE)
    throw FileSystemWatcherException("Unable to obtain '" + _directoryName + "'  first file handle");
  do {
    std::string currentFileName(findHandle.cFileName);
    if (findHandle.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY) {
      currentFiles.emplace_back(findHandle.cFileName);
      if (std::find(_files.begin(), _files.end(), currentFileName) == _files.end()) {
	newFiles.emplace_back(findHandle.cFileName);
      } else {
	_files.erase(std::remove(_files.begin(), _files.end(), currentFileName), _files.end());
      }
    }
  } while (FindNextFile(directoryFileHandle, &findHandle) != 0);
  for (auto i = newFiles.begin(); i < newFiles.end(); i++) {
    events.emplace_back(*i, AFileSystemWatcher::Add);
  }
  for (auto i = _files.begin(); i < _files.end(); i++) {
    events.emplace_back(*i, AFileSystemWatcher::Remove);
  }
  _files = currentFiles;
  return events;
}
