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
     * @param root: the root directory to use
     * @param local : string to use for locale dependent asset
     */
    AssetStore(const std::string &root, const std::string &local);

    /**
     * Constructor with default locale
     *
     * @param root: the root directory to use
     */
    AssetStore(const std::string &root);

    /**
     * dtor
     */
    ~AssetStore(void);

  protected:
    /**
     * Exist for factorisation. You should not use this. Load a ressource from path, into store
     *
     * @tparam RESSOURCE The type of ressource to load
     * @param store The store to load ressource in 
     * @param path The path of the ressource to load
     * @param directory The directrory to search this type of ressource in
     * @param extension The extension of the file
     */
    template<typename RESSOURCE>
    void loadSingleRessource(std::unordered_map<std::string, RESSOURCE> &store, const std::string &path, const std::string &directory, const std::string &extension) {
      try {
	store.emplace(path, _root + "/" + directory + "/" + _locale + "/" + path + extension);
      }
      catch (const AssetException &e) {
	if (_locale != graphic::AssetStore::DEFAULT_LOCALE)
	  store.emplace(path, _root + "/" + directory + "/" + graphic::AssetStore::DEFAULT_LOCALE + "/" + path + extension);
	else
	  throw e;
      }
    }

    /**
     * Exist for factorisation. You should not use this. Load a ressource from path, into store
     *
     * @tparam RESSOURCE The type of ressource to load
     * @param store The store to load ressource in
     * @param path The path of the ressource to load
     */
    template<typename RESSOURCE>
    RESSOURCE &getRessource(std::unordered_map<std::string, RESSOURCE> &store, const std::string &path) {
      try {
	return store.at(path);
      }
      catch (const std::out_of_range &e) {
	throw AssetException(std::string("Unable to find asset '") + path + "'");
      }
    }

    /**
     * Exist for factorisation. You should not use this. Load a ressource from path, into store
     *
     * @tparam RESSOURCE The type of ressource to load
     * @param store The store to load ressource in
     * @param path The path of the ressource to load
     */
    template<typename RESSOURCE>
    void freeRessource(std::unordered_map<std::string, RESSOURCE> &store, const std::string &path) {
        store.erase(path);
    }
    
    /**
     * Load a music with the given path
     *
     * @param path the path to the music
     */
    void loadMusic(const std::string &path);

  public:
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

    /**
     * Directory to search music in
     */
    static const std::string MUSIC_DIRECTORY;

    /**
     * Directory to search sound in
     */ 
    static const std::string SOUND_DIRECTORY;

    /**
     * Directory to search sprite in
     */
    static const std::string SPRITE_DIRECTORY;

    /**
     * Directory to search animation description  in
     */
    static const std::string ANIMATED_DIRECTORY;

    /**
     * Directory to search animated sprite in
     */
    static const std::string ANIMATED_SPRITE_DIRECTORY;

    /**
     * Directory to search text in
     */
    static const std::string TEXT_DIRECTORY;
    
    /**
     * Directory to search font in
     */
    static const std::string FONT_DIRECTORY;

    /**
     * Extension for music file
     */
    static const std::string MUSIC_EXTENSION;

    
    /**
     * Extension for sound file
     */
    static const std::string SOUND_EXTENSION;

    
    /**
     * Extension for sprite file
     */
    static const std::string SPRITE_EXTENSION;

    
    /**
     * Extension for animation description file
     */
    static const std::string ANIMATED_EXTENSION;

    
    /**
     * Extension for text file
     */
    static const std::string TEXT_EXTENSION;

    
    /**
     * Extension for font file
     */
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
   * Specialisation for AnimatedSprite
   */
  template<>
  void AssetStore::loadSingleRessource<graphic::AnimatedSpriteAsset>(std::unordered_map<std::string, graphic::AnimatedSpriteAsset> &store,
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
   * Class for loading a group of asset easely
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
     * Extract the ressource name from file name (basically the file without the extensions)
     *
     * @param path to a file
     * @return the ressource name
     */
    const std::string getRessourceName(const std::string &path);

    /**
     * Helper func to automatically load asset. You should not use this, it exist only for code factorisation.
     *
     * @tparam RESSOURCE The type of the store taken in parameter
     * @param store The store to put load this ressource type into.
     * @tparam directory The directory to search this ressource type from.
     */
    template<typename RESSOURCE>
    void loadRessource(std::unordered_map<std::string, RESSOURCE> &store, const std::string &directory) {
      FileSystemWatcher watcher(_root + "/" + directory + "/" + graphic::AssetStore::DEFAULT_LOCALE);
      std::vector<std::pair<std::string, FileSystemWatcher::Event>> _ressources = watcher.processEvents();

      for (auto i  = _ressources.begin(); i < _ressources.end(); i++) {
	if ((*i).second == FileSystemWatcher::Add) {
	  if (ressourceExist(_root + "/" + directory + "/" + this->_locale + "/" + (*i).first))
	    store.emplace(getRessourceName((*i).first), _root + "/" + directory + "/" + this->_locale + "/" + (*i).first);
	  else
	    store.emplace(getRessourceName((*i).first), _root + "/" + directory + "/" + graphic::AssetStore::DEFAULT_LOCALE + "/" + (*i).first);
	}
      }
    }
  };

  /**
   * Specialisation for AnimatedSprite
   */
  template<>
  void GroupedAssetStore::loadRessource<graphic::AnimatedSpriteAsset>(std::unordered_map<std::string, graphic::AnimatedSpriteAsset> &store, const std::string &directory) {
    FileSystemWatcher watcher(_root + "/" + directory + "/" + graphic::AssetStore::DEFAULT_LOCALE);
    std::vector<std::pair<std::string, FileSystemWatcher::Event>> _ressources = watcher.processEvents();
      
    for (auto i  = _ressources.begin(); i < _ressources.end(); i++) {
      if ((*i).second == FileSystemWatcher::Add) {
	if (ressourceExist(_root + "/" + directory + "/" + this->_locale + "/" + (*i).first) &&
	    ressourceExist(_root + "/" + graphic::AssetStore::ANIMATED_DIRECTORY + "/" + this->_locale + "/" + (*i).first))
	  store.emplace(std::piecewise_construct,
			std::forward_as_tuple(getRessourceName((*i).first)),
			std::forward_as_tuple(_root + "/" + directory + "/" + this->_locale + "/" + (*i).first,
					      _root + "/" + graphic::AssetStore::ANIMATED_DIRECTORY + "/" +
					      this->_locale + "/" + getRessourceName((*i).first) +  graphic::AssetStore::ANIMATED_EXTENSION
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
      }
    }
  }
}

#endif
