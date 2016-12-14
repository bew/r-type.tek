#ifndef _ASSETSTORE_HPP
#define _ASSETSTORE_HPP

#include <string>
#include <unordered_map>

#include "AssetException.hh"
#include "TextAsset.hh"
#include "FontAsset.hh"
#include "SpriteAsset.hh"
#include "AnimatedSpriteAsset.hh"
#include "MusicAsset.hh"
#include "SoundAsset.hh"
#include "FSWatcher/AFileSystemWatcher.hh"

/**
 * contain graphic stuff
 */
namespace graphic {
  /**
   * Handle all the assets
   */
  class AssetStore {
  public:

    /**
     * @param root: the roort directory to use
     * @param local : string to use for locale dependent asset
     */
    AssetStore(const std::string &root, const std::string &local);

    /**
     * Constructor with default locale
     *
     * @param root: the roort directory to use
     */
    AssetStore(const std::string &root);

    /**
     * dtor
     */
    ~AssetStore(void);

    /**
     * Load a music with the given path
     *
     * @param path the path to the music
     */
    void loadMusic(const std::string &path);

    /**
     * Get the music of the given path which has been previously loaded
     * 
     * @param path the path to the music
     * @throw AssetException if the music hasn't been loaded previously
     * @return the music loaded previously
     */
    graphic::MusicAsset &getMusic(const std::string &path);

    /**
     * Free the music of the given path which has been previously loaded
     *
     * @param path the path to the music
     * @throw AssetException if the music hasn't been loaded previously
     */
    void freeMusic(const std::string &path);

    /**
     * Load a sound with the given path
     *
     * @param path the path to the sound
     */
    void loadSound(const std::string &path);

    /**
     * Get the sound of the given path which has been previously loaded
     * 
     * @param path the path to the sound
     * @throw AssetException if the sound hasn't been loaded previously
     * @return the sound loaded previously
     */
    graphic::SoundAsset &getSound(const std::string &path);

    /**
     * Free the sound of the given path which has been previously loaded
     *
     * @param path the path to the sound
     * @throw AssetException if the sound hasn't been loaded previously
     */
    void freeSound(const std::string &path);

    /**
     * Load a font with the given path
     *
     * @param path the path to the font
     */
    void loadFont(const std::string &path);

    /**
     * Get the font of the given path which has been previously loaded
     * 
     * @param path the path to the font
     * @throw AssetException if the font hasn't been loaded previously
     * @return the font loaded previously
     */
    graphic::FontAsset &getFont(const std::string &path);

    /**
     * Free the font of the given path which has been previously loaded
     *
     * @param path the path to the font
     * @throw AssetException if the font hasn't been loaded previously
     */
    void freeFont(const std::string &path);

    /**
     * Load a sprite with the given path
     *
     * @param path the path to the sprite
     */
    void loadSprite(const std::string &path);

    /**
     * Get the sprite of the given path which has been previously loaded
     * 
     * @param path the path to the sprite
     * @throw AssetException if the sprite hasn't been loaded previously
     * @return the sprite loaded previously
     */
    graphic::SpriteAsset &getSprite(const std::string &path);

    /**
     * Free the sprite of the given path which has been previously loaded
     *
     * @param path the path to the sprite
     * @throw AssetException if the sprite hasn't been loaded previously
     */
    void freeSprite(const std::string &path);
    
    /**
     * Load a animated sprite with the given path
     *
     * @param path the path to the animated sprite
     */
    void loadAnimatedSprite(const std::string &path);

    /**
     * Get the animated sprite of the given path which has been previously loaded
     * 
     * @param path the path to the animated sprite
     * @throw AssetException if the animated sprite hasn't been loaded previously
     * @return the animated sprite loaded previously
     */
    graphic::AnimatedSpriteAsset &getAnimatedSprite(const std::string &path);

    /**
     * Free the animated sprite of the given path which has been previously loaded
     *
     * @param path the path to the animated sprite
     * @throw AssetException if the animated sprite hasn't been loaded previously
     */
    void freeAnimatedSprite(const std::string &path);

    /**
     * Load a text with the given path
     *
     * @param path the path to the text
     */
    void loadText(const std::string &path);

    /**
     * Get the text of the given path which has been previously loaded
     * 
     * @param path the path to the text
     * @throw AssetException if the text hasn't been loaded previously
     * @return the text loaded previously
     */
    graphic::TextAsset &getText(const std::string &path);

    /**
     * Free the text of the given path which has been previously loaded
     *
     * @param path the path to the text
     * @throw AssetException if the text hasn't been loaded previously
     */
    void freeText(const std::string &path);

    /**
     * locale to use if there is no locale set
     */
    static const std::string DEFAULT_LOCALE;

    static const std::string MUSIC_DIRECTORY;
    
    static const std::string SOUND_DIRECTORY;
    
    static const std::string SPRITE_DIRECTORY;
    
    static const std::string ANIMATED_DIRECTORY;

    static const std::string ANIMATEDSPRITE_DIRECTORY;
    
    static const std::string TEXT_DIRECTORY;

    static const std::string FONT_DIRECTORY;
    
    static const std::string MUSIC_EXTENSION;
    
    static const std::string SOUND_EXTENSION;
    
    static const std::string SPRITE_EXTENSION;
    
    static const std::string ANIMATED_EXTENSION;
    
    static const std::string TEXT_EXTENSION;
    
    static const std::string FONT_EXTENSION;

  protected:

    /**
     * locale to use for all text
     */
    std::string _locale;

    /**
     * Root directory
     */
    std::string _root;

    /**
     * assets container
     */
    std::unordered_map<std::string, graphic::MusicAsset> _musics;
    std::unordered_map<std::string, graphic::SoundAsset> _sounds;
    std::unordered_map<std::string, graphic::FontAsset> _fonts;
    std::unordered_map<std::string, graphic::SpriteAsset> _sprites;
    std::unordered_map<std::string, graphic::AnimatedSpriteAsset> _animatedSprites;
    std::unordered_map<std::string, graphic::TextAsset> _texts;
  };



  /**
   * Expected filesystem architecture:
   * Root
   *    |-text
   *    |    |-en
   *    |    |-fr
   *    |-sprite
   *    |-font
   *    |-sound
   *    |-music
   *
   * If lookup for a file with locale fail, it will try with default locale
   * If it fail again, it will throw AssetException.
   */
  class GroupedAssetStore : public AssetStore {

  public:
    /**
     * @param root Root directory for asset
     * @param assetStore Subdirectory to load
     */
    GroupedAssetStore(const std::string &root, const std::string &assetStore);

    /**
     * @param root Root directory for asset
     * @param assetStore Subdirectory to load
     * @param lcoale The locale to transmit to AssetStore
     */
    GroupedAssetStore(const std::string &root, const std::string &assetStore, const std::string &locale);

    /**
     * dtor
     */
    ~GroupedAssetStore(void);

    /**
     * Load all the ressources found in root directory, according to local
     */
    void loadAll(void);
  protected:

    /**
     * Check if file is read-accessible
     *
     * @param path Path of file to check for accessibility 
     * @return True if file is accessible, else false
     */
    bool ressourceExist(const std::string &path);

    /**
     * Helper func to automatically load asset. You should not use this, it exist only for code factorisation.
     *
     * @tparam RESSOURCE The type of the store taken in parameter
     * @param store The store to put load this ressource type into.
     * @param directory The directory to search this ressource type from.
     */
    void loadRessource<typename RESSOURCE>(std::unordered_map<std::string, RESSOURCE> &store, const std::string &directory) {

      FileSystemWatcher watcher(_root + "/" + directory + "/" + graphic::AssetStore::DEFAULT_LOCALE);
      std::vector<std::pair<std::string, FileSystemWatcher::Event>> _ressources = watcher.processEvents();

      for (auto i  = _ressources.begin(); i < _ressources.end(); i++) {
	if ((*i).second == FileSystemWatcher::Add) {
	  if (ressourceExist(_root + "/" + directory + "/" + this->_locale + "/" + (*i).first))
	    this->_fonts.emplace((*i).first, _root + "/" + directory + "/" + this->_locale + "/" + (*i).first);
	  else
	    this->_fonts.emplace((*i).first, _root + "/" + directory + "/" + graphic::AssetStore::DEFAULT_LOCALE + "/" + (*i).first);
	}
      }
    }
    
    void loadAllMusic(void);
    void loadAllSound(void);
    void loadAllText(void);
    void loadAllSprite(void);
    void loadAllFont(void);
    void loadAllAnimatedSprite(void);
  };
}
  
#endif
