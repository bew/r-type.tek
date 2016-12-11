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
  _musics.emplace(path, _root + "/" + graphic::AssetStore::MUSIC_DIRECTORY + "/" + _locale + "/" + path + graphic::AssetStore::MUSIC_EXTENSION);
}

graphic::MusicAsset &graphic::AssetStore::getMusic(const std::string &path) {
  try {
    return _musics.at(path);
  }
  catch (const std:: out_of_range &e) {
    throw AssetException(std::string("Unable to find asset '") + e.what() + "'");
  }
};

void graphic::AssetStore::freeMusic(const std::string &path) {
  _musics.erase(path);
};

// SOUND

void graphic::AssetStore::loadSound(const std::string &path) {
  _sounds.emplace(path, _root + "/" + graphic::AssetStore::SOUND_DIRECTORY + "/" + _locale + "/" + path + graphic::AssetStore::SOUND_EXTENSION);
}

graphic::SoundAsset &graphic::AssetStore::getSound(const std::string &path) {
  try {
    return _sounds.at(path);
  }
  catch (const std:: out_of_range &e) {
    throw AssetException(std::string("Unable to find asset '") + e.what() + "'");
  }
};

void graphic::AssetStore::freeSound(const std::string &path) {
  _sounds.erase(path);
};

// SPRITE

void graphic::AssetStore::loadSprite(const std::string &path) {
  _sprites.emplace(path, _root + "/" + graphic::AssetStore::SPRITE_DIRECTORY + "/" + _locale + "/" + path + graphic::AssetStore::SPRITE_EXTENSION);
}

graphic::SpriteAsset &graphic::AssetStore::getSprite(const std::string &path) {
  try {
    return _sprites.at(path);
  }
  catch (const std:: out_of_range &e) {
    throw AssetException(std::string("Unable to find asset '") + e.what() + "'");
  }
};

void graphic::AssetStore::freeSprite(const std::string &path) {
  _sprites.erase(path);
};

// ANIMATEDSPRITE

void graphic::AssetStore::loadAnimatedSprite(const std::string &path) {
  _animatedSprites.emplace(std::piecewise_construct,
			   std::forward_as_tuple(path),
			   std::forward_as_tuple(_root + "/" + graphic::AssetStore::SPRITE_DIRECTORY + "/" + _locale + "/" + path + graphic::AssetStore::SPRITE_EXTENSION,
			   _root + "/" + graphic::AssetStore::ANIMATED_DIRECTORY + "/" + _locale + "/" + path + graphic::AssetStore::ANIMATED_EXTENSION
						 ));
}

graphic::AnimatedSpriteAsset &graphic::AssetStore::getAnimatedSprite(const std::string &path) {
  try {
    return _animatedSprites.at(path);
  }
  catch (const std:: out_of_range &e) {
    throw AssetException(std::string("Unable to find asset '") + e.what() + "'");
  }
};

void graphic::AssetStore::freeAnimatedSprite(const std::string &path) {
  _animatedSprites.erase(path);
};

// FONT

void graphic::AssetStore::loadFont(const std::string &path) {
  _fonts.emplace(path, _root + "/" + graphic::AssetStore::FONT_DIRECTORY + "/" + _locale + "/" + path + graphic::AssetStore::FONT_EXTENSION);
}

graphic::FontAsset &graphic::AssetStore::getFont(const std::string &path) {
  try {
    return _fonts.at(path);
  }
  catch (const std:: out_of_range &e) {
    throw AssetException(std::string("Unable to find asset '") + e.what() + "'");
  }
};

void graphic::AssetStore::freeFont(const std::string &path) {
  _fonts.erase(path);
};

// TEXT

void graphic::AssetStore::loadText(const std::string &path) {
  _texts.emplace(path, _root + "/" + graphic::AssetStore::TEXT_DIRECTORY + "/" + _locale + "/" + path + graphic::AssetStore::TEXT_EXTENSION);
}

graphic::TextAsset &graphic::AssetStore::getText(const std::string &path) {
  try {
    return _texts.at(path);
  }
  catch (const std:: out_of_range &e) {
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

const std::string graphic::AssetStore::TEXT_DIRECTORY = "texts";

const std::string graphic::AssetStore::FONT_DIRECTORY = "fonts";

const std::string graphic::AssetStore::MUSIC_EXTENSION = "mp3";

const std::string graphic::AssetStore::SOUND_EXTENSION = "mp3";

const std::string graphic::AssetStore::SPRITE_EXTENSION = "bmp";

const std::string graphic::AssetStore::ANIMATED_EXTENSION = "anim.bson";

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

//TO IMPLEMENT
void graphic::GroupedAssetStore::loadAll(void) {

};
