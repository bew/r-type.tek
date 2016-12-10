#ifndef _ASSETSTORE_HPP
#define _ASSETSTORE_HPP

#include <string>
#include <unordored>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "assetException.hh"
#include "textAsset.hh"

class AssetStore {
public:

  /**
   * @param local : string to use for locale dependent asset
   */
  AssetStore(const std::string &local);

  /**
   * Constructor with default locale
   */
  AssetStore(void);
  ~AssetStore(void);
  
  void loadMusic(const std::string &);
  sf::Music &getMusic(const std::string &);
  void freeMusic(const std::string &);
  
  void loadSound(const std::string &);
  sf::Sound &getSound(const std::string &);
  void freeSound(const std::string &);
  
  void loadFont(const std::string &);
  sf::Font &getFont(const std::string &);
  void freeFont(const std::string &);
  
  void loadSprite(const std::string &);
  sf::Sprite &getSprite(const std::string &);
  void freeSprite(const std::string &);
  
  void loadText(const std::string &);
  sf::TextAsset &getText(const std::string &);
  void freeText(const std::string &);
  
protected:
  static std::string _default_locale;
  std::string _locale;
  std::unordored_map<std::string, sf::Music> _musics;
  std::unordored_map<std::string, sf::Sound> _sounds;
  std::unordored_map<std::string, sf::Font> _fonts;
  std::unordored_map<std::string, sf::Sprite> _sprites;
  std::unordored_map<std::string, TextAsset> _texts;
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

  /**
   * @param root Root directory for asset
   * @params All the subdirectory associed with each asset type
   */
  GoupedAssetStore(const std::string &root,
		   const std::string &text,
		   const std::string &sprite,
		   const std::string &font,
		   const std::string &sound,
		   const std::string &music);
  ~GroupedAssetStore(void);
  
  const std::string &getAssetRoot(void) const;
  const std::string &getMusicRoot(void) const;
  const std::string &getSoundRoot(void) const;
  const std::string &getFontRoot(void) const;
  const std::string &getTextRoot(void) const;
  const std::string &getSpriteRoot(void) const;

  void loadAll(void);

protected:
  std::string _assetStoreRoot;
  std::string _textRoot;
  std::string _spriteRoot;
  std::string _fontRoot;
  std::string _soundRoot;
  std::string _musicRoot;
}
  
#endif
