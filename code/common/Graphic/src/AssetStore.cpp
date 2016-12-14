#include "AssetStore.hh"

graphic::AssetStore::AssetStore(const std::string &root, const std::string &locale):
  _root(root),
  _locale(locale)
{}

graphic::AssetStore::AssetStore(const std::string &root):
  _root(root),
  _locale(graphic::AssetStore::DEFAULT_LOCALE)
{}

graphic::AssetStore::~AssetStore(void)
{}

// MUSIC

void graphic::AssetStore::loadMusic(const std::string &path) {
  std::cout << "LOAD MUSIC " << path << std::endl;
  try {
    _musics.emplace(path, _root + "/" + graphic::AssetStore::MUSIC_DIRECTORY + "/" + _locale + "/" + path + graphic::AssetStore::MUSIC_EXTENSION);
  }
  catch (const AssetException &e) {
    if (_locale != graphic::AssetStore::DEFAULT_LOCALE)
    _musics.emplace(path, _root + "/" + graphic::AssetStore::MUSIC_DIRECTORY + "/" + graphic::AssetStore::DEFAULT_LOCALE + "/" + path + graphic::AssetStore::MUSIC_EXTENSION);
    else
      throw e;
  }
}

graphic::MusicAsset &graphic::AssetStore::getMusic(const std::string &path) {
  try {
    return _musics.at(path);
  }
  catch (const std::out_of_range &e) {
    throw AssetException(std::string("Unable to find asset '") + path + "'");
  }
};

void graphic::AssetStore::freeMusic(const std::string &path) {
  _musics.erase(path);
};

// SOUND

void graphic::AssetStore::loadSound(const std::string &path) {
  std::cout << "LOAD SOUND " << path << std::endl;
  try {
    _sounds.emplace(path, _root + "/" + graphic::AssetStore::SOUND_DIRECTORY + "/" + _locale + "/" + path + graphic::AssetStore::SOUND_EXTENSION);
  }
  catch (const AssetException &e) {
    if (_locale != graphic::AssetStore::DEFAULT_LOCALE)
      _sounds.emplace(path, _root + "/" + graphic::AssetStore::SOUND_DIRECTORY + "/" + graphic::AssetStore::DEFAULT_LOCALE + "/" + path + graphic::AssetStore::SOUND_EXTENSION);
    else
      throw e;
  }
}

graphic::SoundAsset &graphic::AssetStore::getSound(const std::string &path) {
  try {
    return _sounds.at(path);
  }
  catch (const std:: out_of_range &e) {
    throw AssetException(std::string("Unable to find asset '") + path + "'");
  }
};

void graphic::AssetStore::freeSound(const std::string &path) {
  _sounds.erase(path);
};

// SPRITE

void graphic::AssetStore::loadSprite(const std::string &path) {
  std::cout << "LOAD SPRITE " << path << std::endl;
  try {
    _sprites.emplace(path, _root + "/" + graphic::AssetStore::SPRITE_DIRECTORY + "/" + _locale + "/" + path + graphic::AssetStore::SPRITE_EXTENSION);
  }
  catch (const AssetException &e) {
    if (_locale != graphic::AssetStore::DEFAULT_LOCALE)
      _sprites.emplace(path, _root + "/" + graphic::AssetStore::SPRITE_DIRECTORY + "/" + graphic::AssetStore::DEFAULT_LOCALE + "/" + path + graphic::AssetStore::SPRITE_EXTENSION);
    else
      throw e;
  }
}

graphic::SpriteAsset &graphic::AssetStore::getSprite(const std::string &path) {
  try {
    return _sprites.at(path);
  }
  catch (const std::out_of_range &e) {
    throw AssetException(std::string("Unable to find asset '") + path + "'");
  }
};

void graphic::AssetStore::freeSprite(const std::string &path) {
  _sprites.erase(path);
};

// ANIMATEDSPRITE

void graphic::AssetStore::loadAnimatedSprite(const std::string &path) {
  std::cout << "LOAD ANIMATION " << path << std::endl;
  try {
    _animatedSprites.emplace(std::piecewise_construct,
			     std::forward_as_tuple(path),
			     std::forward_as_tuple(_root + "/" + graphic::AssetStore::ANIMATEDSPRITE_DIRECTORY + "/" + _locale + "/" + path + graphic::AssetStore::SPRITE_EXTENSION,
						   _root + "/" + graphic::AssetStore::ANIMATED_DIRECTORY + "/" + _locale + "/" + path + graphic::AssetStore::SPRITE_EXTENSION + graphic::AssetStore::ANIMATED_EXTENSION
						   )
			     );
  }
  catch (const AssetException &e) {
    if (_locale != graphic::AssetStore::DEFAULT_LOCALE)
      _animatedSprites.emplace(std::piecewise_construct,
			       std::forward_as_tuple(path),
			       std::forward_as_tuple(_root + "/" + graphic::AssetStore::ANIMATEDSPRITE_DIRECTORY + "/" + graphic::AssetStore::DEFAULT_LOCALE + "/" + path + graphic::AssetStore::SPRITE_EXTENSION,
						     _root + "/" + graphic::AssetStore::ANIMATED_DIRECTORY + "/" + graphic::AssetStore::DEFAULT_LOCALE + "/" + path + graphic::AssetStore::ANIMATED_EXTENSION
						     )
			       );
    else
      throw e;
  }
}

graphic::AnimatedSpriteAsset &graphic::AssetStore::getAnimatedSprite(const std::string &path) {
  try {
    return _animatedSprites.at(path);
  }
  catch (const std::out_of_range &e) {
    throw AssetException(std::string("Unable to find asset '") + path + "'");
  }
};

void graphic::AssetStore::freeAnimatedSprite(const std::string &path) {
  _animatedSprites.erase(path);
};

// FONT

void graphic::AssetStore::loadFont(const std::string &path) {
  std::cout << "LOAD FONT " << path << std::endl;
  try {
    _fonts.emplace(path, _root + "/" + graphic::AssetStore::FONT_DIRECTORY + "/" + _locale + "/" + path + graphic::AssetStore::FONT_EXTENSION);
  }
  catch (const AssetException &e) {
    if (_locale != graphic::AssetStore::DEFAULT_LOCALE)
      _fonts.emplace(path, _root + "/" + graphic::AssetStore::FONT_DIRECTORY + "/" + graphic::AssetStore::DEFAULT_LOCALE + "/" + path + graphic::AssetStore::FONT_EXTENSION);
    else
      throw e;
  }
}

graphic::FontAsset &graphic::AssetStore::getFont(const std::string &path) {
  try {
    return _fonts.at(path);
  }
  catch (const std::out_of_range &e) {
    throw AssetException(std::string("Unable to find asset '") + path + "'");
  }
};

void graphic::AssetStore::freeFont(const std::string &path) {
  _fonts.erase(path);
};

// TEXT

void graphic::AssetStore::loadText(const std::string &path) {
  std::cout << "LOAD TEXT " << path << std::endl;
  try {
    _texts.emplace(path, _root + "/" + graphic::AssetStore::TEXT_DIRECTORY + "/" + _locale + "/" + path + graphic::AssetStore::TEXT_EXTENSION);
  }
  catch (const AssetException &e) {
    if (_locale != graphic::AssetStore::DEFAULT_LOCALE)
      _texts.emplace(path, _root + "/" + graphic::AssetStore::TEXT_DIRECTORY + "/" + graphic::AssetStore::DEFAULT_LOCALE + "/" + path + graphic::AssetStore::TEXT_EXTENSION);
    else
      throw e;
  }
}

graphic::TextAsset &graphic::AssetStore::getText(const std::string &path) {
  try {
    return _texts.at(path);
  }
  catch (const std::out_of_range &e) {
    throw AssetException(std::string("Unable to find asset '") + e.what() + "'");
  }
};

void graphic::AssetStore::freeText(const std::string &path) {
  _texts.erase(path);
};

// CONSTANT

const std::string graphic::AssetStore::DEFAULT_LOCALE = "en";

const std::string graphic::AssetStore::MUSIC_DIRECTORY = "musics";

const std::string graphic::AssetStore::SOUND_DIRECTORY = "sounds";

const std::string graphic::AssetStore::SPRITE_DIRECTORY = "sprites";

const std::string graphic::AssetStore::ANIMATED_DIRECTORY = "animateds";

const std::string graphic::AssetStore::ANIMATEDSPRITE_DIRECTORY = "spritemaps";

const std::string graphic::AssetStore::TEXT_DIRECTORY = "texts";

const std::string graphic::AssetStore::FONT_DIRECTORY = "fonts";

const std::string graphic::AssetStore::MUSIC_EXTENSION = ".ogg";

const std::string graphic::AssetStore::SOUND_EXTENSION = ".ogg";

const std::string graphic::AssetStore::SPRITE_EXTENSION = ".bmp";

const std::string graphic::AssetStore::ANIMATED_EXTENSION = ".anim";

const std::string graphic::AssetStore::TEXT_EXTENSION = ".txt";

const std::string graphic::AssetStore::FONT_EXTENSION = ".ttf";

// GROUPED

graphic::GroupedAssetStore::GroupedAssetStore(const std::string &root, const std::string &subDir):
  AssetStore(root + "/" + subDir)
{};

graphic::GroupedAssetStore::GroupedAssetStore(const std::string &root, const std::string &subDir, const std::string &locale):
  AssetStore(root + "/" + subDir, locale)
{};

graphic::GroupedAssetStore::~GroupedAssetStore(void) {};

bool graphic::GroupedAssetStore::ressourceExist(const std::string &path) {
  std::ifstream file(path);
  return file.good();
}

//Todo: logging here
void graphic::GroupedAssetStore::loadAll(void) {
  try {
    //loadAllMusic();
    this->loadRessource<graphic::MusicAsset>(this->_musics, graphic::AssetStore::MUSIC_DIRECTORY);
  }
  catch (const FileSystemWatcherException &e) {
  }

  try {
    loadAllSound();}
  catch (const FileSystemWatcherException &e) {
  }

  try {
    loadAllFont();}
  catch (const FileSystemWatcherException &e) {
  }

  try {
    loadAllText();}
  catch (const FileSystemWatcherException &e) {
  }

  try {
    loadAllSprite();}
  catch (const FileSystemWatcherException &e) {
  }

  try {
    loadAllAnimatedSprite();
  }
  catch (const FileSystemWatcherException &e) {
  }
};

void graphic::GroupedAssetStore::loadAllMusic(void) {
  FileSystemWatcher watcher(_root + "/" + graphic::AssetStore::MUSIC_DIRECTORY + "/" + graphic::AssetStore::DEFAULT_LOCALE);
  std::vector<std::pair<std::string, FileSystemWatcher::Event>> _ressources = watcher.processEvents();

  for (auto i  = _ressources.begin(); i < _ressources.end(); i++) {
    if ((*i).second == FileSystemWatcher::Add) {
      if (ressourceExist(_root + "/" + graphic::AssetStore::MUSIC_DIRECTORY + "/" + this->_locale + "/" + (*i).first))
	this->_musics.emplace((*i).first, _root + "/" + graphic::AssetStore::MUSIC_DIRECTORY + "/" + this->_locale + "/" + (*i).first);
      else
	this->_musics.emplace((*i).first, _root + "/" + graphic::AssetStore::MUSIC_DIRECTORY + "/" + graphic::AssetStore::DEFAULT_LOCALE + "/" + (*i).first);
    }
  }
};

void graphic::GroupedAssetStore::loadAllSound(void) {  
  FileSystemWatcher watcher(_root + "/" + graphic::AssetStore::SOUND_DIRECTORY + "/" + graphic::AssetStore::DEFAULT_LOCALE);
  std::vector<std::pair<std::string, FileSystemWatcher::Event>> _ressources = watcher.processEvents();

  for (auto i  = _ressources.begin(); i < _ressources.end(); i++) {
    if ((*i).second == FileSystemWatcher::Add) {
      if (ressourceExist(_root + "/" + graphic::AssetStore::SOUND_DIRECTORY + "/" + this->_locale + "/" + (*i).first))
	this->_sounds.emplace((*i).first, _root + "/" + graphic::AssetStore::SOUND_DIRECTORY + "/" + this->_locale + "/" + (*i).first);
      else
	this->_sounds.emplace((*i).first, _root + "/" + graphic::AssetStore::SOUND_DIRECTORY + "/" + graphic::AssetStore::DEFAULT_LOCALE + "/" + (*i).first);
    }
  }
};

void graphic::GroupedAssetStore::loadAllText(void){

  FileSystemWatcher watcher(_root + "/" + graphic::AssetStore::TEXT_DIRECTORY + "/" + graphic::AssetStore::DEFAULT_LOCALE);
  std::vector<std::pair<std::string, FileSystemWatcher::Event>> _ressources = watcher.processEvents();

  for (auto i  = _ressources.begin(); i < _ressources.end(); i++) {
    if ((*i).second == FileSystemWatcher::Add) {
      if (ressourceExist(_root + "/" + graphic::AssetStore::TEXT_DIRECTORY + "/" + this->_locale + "/" + (*i).first))
	this->_texts.emplace((*i).first, _root + "/" + graphic::AssetStore::TEXT_DIRECTORY + "/" + this->_locale + "/" + (*i).first);
      else
	this->_texts.emplace((*i).first, _root + "/" + graphic::AssetStore::TEXT_DIRECTORY + "/" + graphic::AssetStore::DEFAULT_LOCALE + "/" + (*i).first);
    }  
  }
};

void graphic::GroupedAssetStore::loadAllSprite(void) {

  FileSystemWatcher watcher(_root + "/" + graphic::AssetStore::SPRITE_DIRECTORY + "/" + graphic::AssetStore::DEFAULT_LOCALE);
  std::vector<std::pair<std::string, FileSystemWatcher::Event>> _ressources = watcher.processEvents();

  for (auto i  = _ressources.begin(); i < _ressources.end(); i++) {
    if ((*i).second == FileSystemWatcher::Add) {
      if (ressourceExist(_root + "/" + graphic::AssetStore::SPRITE_DIRECTORY + "/" + this->_locale + "/" + (*i).first))
	this->_sprites.emplace((*i).first, _root + "/" + graphic::AssetStore::SPRITE_DIRECTORY + "/" + this->_locale + "/" + (*i).first);
      else
	this->_sprites.emplace((*i).first, _root + "/" + graphic::AssetStore::SPRITE_DIRECTORY + "/" + graphic::AssetStore::DEFAULT_LOCALE + "/" + (*i).first);
    }
  }
};

void graphic::GroupedAssetStore::loadAllFont(void) {

  FileSystemWatcher watcher(_root + "/" + graphic::AssetStore::FONT_DIRECTORY + "/" + graphic::AssetStore::DEFAULT_LOCALE);
  std::vector<std::pair<std::string, FileSystemWatcher::Event>> _ressources = watcher.processEvents();

  for (auto i  = _ressources.begin(); i < _ressources.end(); i++) {
    if ((*i).second == FileSystemWatcher::Add) {
      if (ressourceExist(_root + "/" + graphic::AssetStore::FONT_DIRECTORY + "/" + this->_locale + "/" + (*i).first))
	this->_fonts.emplace((*i).first, _root + "/" + graphic::AssetStore::FONT_DIRECTORY + "/" + this->_locale + "/" + (*i).first);
      else
	this->_fonts.emplace((*i).first, _root + "/" + graphic::AssetStore::FONT_DIRECTORY + "/" + graphic::AssetStore::DEFAULT_LOCALE + "/" + (*i).first);
    }
  }
};

void graphic::GroupedAssetStore::loadAllAnimatedSprite(void) {
  
  FileSystemWatcher watcher(_root + "/" + graphic::AssetStore::ANIMATEDSPRITE_DIRECTORY + "/" + graphic::AssetStore::DEFAULT_LOCALE);
  std::vector<std::pair<std::string, FileSystemWatcher::Event>> _ressources = watcher.processEvents();

  for (auto i  = _ressources.begin(); i < _ressources.end(); i++) {
    if ((*i).second == FileSystemWatcher::Add) {
      if (ressourceExist(_root + "/" + graphic::AssetStore::ANIMATEDSPRITE_DIRECTORY + "/" + this->_locale + "/" + (*i).first) &&
	  ressourceExist(_root + "/" + graphic::AssetStore::ANIMATED_DIRECTORY + "/" + this->_locale + "/" + (*i).first))
	this->_animatedSprites.emplace(std::piecewise_construct,
				       std::forward_as_tuple((*i).first),
				       std::forward_as_tuple(_root + "/" + graphic::AssetStore::ANIMATEDSPRITE_DIRECTORY + "/" + this->_locale + "/" + (*i).first,
							     _root + "/" + graphic::AssetStore::ANIMATED_DIRECTORY + "/" + this->_locale + "/" + (*i).first +  graphic::AssetStore::ANIMATED_EXTENSION
							     )
				       );
      else
	this->_animatedSprites.emplace(std::piecewise_construct,
                                       std::forward_as_tuple((*i).first),
				       std::forward_as_tuple(_root + "/" + graphic::AssetStore::ANIMATEDSPRITE_DIRECTORY + "/" + graphic::AssetStore::DEFAULT_LOCALE + "/" + (*i).first,
							      _root + "/" + graphic::AssetStore::ANIMATED_DIRECTORY + "/" + graphic::AssetStore::DEFAULT_LOCALE + "/" + (*i).first +  graphic::AssetStore::ANIMATED_EXTENSION
							      )
				       );
    }
  }
};
