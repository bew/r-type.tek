/**
 * @file linuxFileSystemWatcher.cpp
 * @brief Implementation for linux file system watcher class
 * @author Nekhot
 */

#include "linuxFileSystemWatcher.hh"

LinuxFileSystemWatcher::LinuxFileSystemWatcher(const std::string &dirName) :
  AFileSystemWatcher(dirName) {
}

std::vector<std::pair<std::string, AFileSystemWatcher::Event>> LinuxFileSystemWatcher::processEvents(void) {
  DIR *directory;
  struct dirent* entry = nullptr;
  std::vector<std::string> newFiles;
  std::vector<std::string> currentFiles;
  std::vector<std::pair<std::string, AFileSystemWatcher::Event>> events;
  
  if ((directory = opendir(this->_directoryName.c_str())) == nullptr)
    throw FileSystemWatcherException("Unable to obtain directory open handle for '" + this->_directoryName + "'");
  while((entry = readdir(directory)) != nullptr) {
    std::string fileName(entry->d_name);
    if (fileName != "." && fileName != "..") {
      currentFiles.emplace_back(entry->d_name);
      if (std::find(_files.begin(), _files.end(), fileName) == _files.end()) {
	newFiles.emplace_back(entry->d_name);
      } else {
	_files.erase(std::remove(_files.begin(), _files.end(), fileName), _files.end());
      }
    }
  }
  for (auto i = newFiles.begin(); i < newFiles.end(); i++) {
    events.emplace_back(*i, AFileSystemWatcher::Add);
  }
  for (auto i = _files.begin(); i < _files.end(); i++) {
    events.emplace_back(*i, AFileSystemWatcher::Remove);
  }
  _files = currentFiles;
  closedir(directory);
  return events;
}
