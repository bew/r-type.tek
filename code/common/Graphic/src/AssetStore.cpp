/**
 * @file AssetStore.cpp
 * @brief Implementation for asset store
 * @author Nekhot
 */

#include "AssetStore.hpp"

/**
 * Specialisation for AnimatedSprite
 */
template<>
void graphic::AssetStore::loadSingleRessource<graphic::AnimatedSpriteAsset>(std::unordered_map<std::string, graphic::AnimatedSpriteAsset> &store,
									    const std::string &path,
									    const std::string &directory,
									    const std::string &extension) {
  try {
    store.emplace(std::piecewise_construct,
		  std::forward_as_tuple(path),
		  std::forward_as_tuple(_root + "/" + directory + "/" + _locale + "/" + path + extension,
					_root + "/" + graphic::AssetStore::ANIMATED_DIRECTORY + "/" +
					_locale + "/" + path + graphic::AssetStore::ANIMATED_EXTENSION
					)
		  );
  }
  catch (const AssetException &e) {
    if (_locale != graphic::AssetStore::DEFAULT_LOCALE)
      _animatedSprites.emplace(std::piecewise_construct,
			       std::forward_as_tuple(path),
			       std::forward_as_tuple(_root + "/" + directory + "/" + graphic::AssetStore::DEFAULT_LOCALE + "/" + path + extension,
						     _root + "/" + graphic::AssetStore::ANIMATED_DIRECTORY + "/" +
						     graphic::AssetStore::DEFAULT_LOCALE + "/" + path + graphic::AssetStore::ANIMATED_EXTENSION
						     )
			       );
    else
      throw e;
  }
}

/**                                                                                                                                                                                          
 * Specialisation for AnimatedSprite                                                                                                                                                         
 */
template<>
void graphic::GroupedAssetStore::loadRessource<graphic::AnimatedSpriteAsset>(std::unordered_map<std::string, graphic::AnimatedSpriteAsset> &store, const std::string &directory) {
  FileSystemWatcher watcher(_root + "/" + directory + "/" + graphic::AssetStore::DEFAULT_LOCALE);
  std::vector<std::pair<std::string, FileSystemWatcher::Event>> _ressources = watcher.processEvents();
  
  for (auto i  = _ressources.begin(); i < _ressources.end(); i++) {
    if ((*i).second == FileSystemWatcher::Add) {
      try {
	if (ressourceExist(_root + "/" + directory + "/" + this->_locale + "/" + (*i).first) &&
	    ressourceExist(_root + "/" + graphic::AssetStore::ANIMATED_DIRECTORY + "/" + this->_locale + "/" + getRessourceName((*i).first) + graphic::AssetStore::ANIMATED_EXTENSION))
	  store.emplace(std::piecewise_construct,
			std::forward_as_tuple(getRessourceName((*i).first)),
			std::forward_as_tuple(_root + "/" + directory + "/" + this->_locale + "/" + (*i).first,
					      _root + "/" + graphic::AssetStore::ANIMATED_DIRECTORY + "/" +
					      this->_locale + "/" + getRessourceName((*i).first) + graphic::AssetStore::ANIMATED_EXTENSION
					      )
			);
	else
	  store.emplace(std::piecewise_construct,
			std::forward_as_tuple(getRessourceName((*i).first)),
			std::forward_as_tuple(_root + "/" + directory + "/" + graphic::AssetStore::DEFAULT_LOCALE + "/" + (*i).first,
					      _root + "/" + graphic::AssetStore::ANIMATED_DIRECTORY + "/" +
					    graphic::AssetStore::DEFAULT_LOCALE + "/" + getRessourceName((*i).first) +  graphic::AssetStore::ANIMATED_EXTENSION
					      )
			);
      } catch(const graphic::AssetException &e) {
	logs::getLogger()[logs::ERRORS] << "Could not load animation : '" << e.what() << "'" << std::endl;
      }
    }
  }
}

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

const std::string &graphic::AssetStore::getLocale(void) const {
  return _locale;
};

void graphic::AssetStore::setLocale(const std::string &locale) {
  _locale = locale;
};

void graphic::AssetStore::empty(void) {
  _musics.clear();
  _sounds.clear();
  _sprites.clear();
  _animatedSprites.clear();
  _fonts.clear();
  _texts.clear();
};


// MUSIC ////////////////

void graphic::AssetStore::loadMusic(const std::string &path) {
  loadSingleRessource(this->_musics, path, graphic::AssetStore::MUSIC_DIRECTORY, graphic::AssetStore::MUSIC_EXTENSION);
}

graphic::MusicAsset &graphic::AssetStore::getMusic(const std::string &path) {
  return getRessource(this->_musics, path);
};

void graphic::AssetStore::freeMusic(const std::string &path) {
  freeRessource(this->_musics, path);
};

// SOUND ////////////////

void graphic::AssetStore::loadSound(const std::string &path) {
  loadSingleRessource(this->_sounds, path, graphic::AssetStore::SOUND_DIRECTORY, graphic::AssetStore::SOUND_EXTENSION);
}

graphic::SoundAsset &graphic::AssetStore::getSound(const std::string &path) {
  return getRessource(this->_sounds, path);
};

void graphic::AssetStore::freeSound(const std::string &path) {
  freeRessource(this->_sounds, path);
};

// SPRITE ///////////////

void graphic::AssetStore::loadSprite(const std::string &path) {
  loadSingleRessource(this->_sprites, path, graphic::AssetStore::SPRITE_DIRECTORY, graphic::AssetStore::SPRITE_EXTENSION);
}

graphic::SpriteAsset &graphic::AssetStore::getSprite(const std::string &path) {
  return getRessource(this->_sprites, path);
};

void graphic::AssetStore::freeSprite(const std::string &path) {
   freeRessource(this->_sprites, path);
};

// ANIMATEDSPRITE ////////

void graphic::AssetStore::loadAnimatedSprite(const std::string &path) {
  loadSingleRessource(this->_animatedSprites, path, graphic::AssetStore::ANIMATED_SPRITE_DIRECTORY, graphic::AssetStore::SPRITE_EXTENSION);
}

graphic::AnimatedSpriteAsset &graphic::AssetStore::getAnimatedSprite(const std::string &path) {
  return getRessource(this->_animatedSprites, path);
};

void graphic::AssetStore::freeAnimatedSprite(const std::string &path) {
  freeRessource(this->_animatedSprites, path);
};

// FONT //////////////////////

void graphic::AssetStore::loadFont(const std::string &path) {
 loadSingleRessource(this->_fonts, path, graphic::AssetStore::FONT_DIRECTORY, graphic::AssetStore::FONT_EXTENSION);
}

graphic::FontAsset &graphic::AssetStore::getFont(const std::string &path) {
  return getRessource(this->_fonts, path);
};

void graphic::AssetStore::freeFont(const std::string &path) {
  freeRessource(this->_fonts, path);
};

// TEXT //////////////////////

void graphic::AssetStore::loadText(const std::string &path) {
  loadSingleRessource(this->_texts, path, graphic::AssetStore::TEXT_DIRECTORY, graphic::AssetStore::TEXT_EXTENSION);
}

graphic::TextAsset &graphic::AssetStore::getText(const std::string &path) {
  return getRessource(this->_texts, path);
};

void graphic::AssetStore::freeText(const std::string &path) {
  freeRessource(this->_texts, path);
};

// CONSTANT

const std::string graphic::AssetStore::DEFAULT_LOCALE = "en";

const std::string graphic::AssetStore::MUSIC_DIRECTORY = "musics";

const std::string graphic::AssetStore::SOUND_DIRECTORY = "sounds";

const std::string graphic::AssetStore::SPRITE_DIRECTORY = "sprites";

const std::string graphic::AssetStore::ANIMATED_DIRECTORY = "animateds";

const std::string graphic::AssetStore::ANIMATED_SPRITE_DIRECTORY = "spritemaps";

const std::string graphic::AssetStore::TEXT_DIRECTORY = "texts";

const std::string graphic::AssetStore::FONT_DIRECTORY = "fonts";

const std::string graphic::AssetStore::MUSIC_EXTENSION = ".ogg";

const std::string graphic::AssetStore::SOUND_EXTENSION = ".ogg";

const std::string graphic::AssetStore::SPRITE_EXTENSION = ".png";

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

const std::string graphic::GroupedAssetStore::getRessourceName(const std::string &path) {
  size_t pos = path.rfind(".");

  if (pos == std::string::npos)
    return path;
  if (pos == 0)
    return path;
  return path.substr(0, pos);
}

//Todo: logging here
void graphic::GroupedAssetStore::loadAll(void) {
  try {
    this->loadRessource<graphic::MusicAsset>(this->_musics, graphic::AssetStore::MUSIC_DIRECTORY);
  }
  catch (const FileSystemWatcherException &) {
  }

  try {
    this->loadRessource<graphic::FontAsset>(this->_fonts, graphic::AssetStore::FONT_DIRECTORY);
  }
  catch (const FileSystemWatcherException &) {
  }

  try {
    this->loadRessource<graphic::TextAsset>(this->_texts, graphic::AssetStore::TEXT_DIRECTORY);
  }
  catch (const FileSystemWatcherException &) {
  }

  try {
    this->loadRessource<graphic::SoundAsset>(this->_sounds, graphic::AssetStore::SOUND_DIRECTORY);
  }
  catch (const FileSystemWatcherException &) {
  }

  try {
    this->loadRessource<graphic::SpriteAsset>(this->_sprites, graphic::AssetStore::SPRITE_DIRECTORY);
  }
  catch (const FileSystemWatcherException &) {
  }

  try {
    this->loadRessource<graphic::AnimatedSpriteAsset>(this->_animatedSprites, graphic::AssetStore::ANIMATED_SPRITE_DIRECTORY);
  }
  catch (const FileSystemWatcherException &) {
  }
}
