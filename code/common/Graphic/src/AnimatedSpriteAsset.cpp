/**
 * @file AnimatedSpriteAsset.cpp
 * @brief Implementation for animated sprite asset
 * @author Nekhot
 */

#include "AnimatedSpriteAsset.hh"

graphic::AnimatedSpriteAsset::AnimatedSpriteAsset(const std::string &path, const std::string &animSpecPath) {
  if (!_texture.loadFromFile(path))
    throw AssetException("Unable to load animated sprite asset : '" + path + "'");
  try {
    bson::Document document;
    document.readFromFile(animSpecPath, true);
    for (auto animationKey : document.getKeys()) {
      const bson::Document &animationDocument = document[animationKey].getValueDocument();
      _animations[animationKey].frequency = animationDocument["frequency"].getValueDouble();
      const bson::Document &framesDocument = animationDocument["frames"].getValueDocument();
      for (auto frameKey : framesDocument.getKeys()) {
	const bson::Document &singleFrameDocument = framesDocument[frameKey].getValueDocument();
	_animations[animationKey]
	  .frames.emplace_back(singleFrameDocument["x"].getValueInt32(),
			       singleFrameDocument["y"].getValueInt32(),
			       singleFrameDocument["width"].getValueInt32(),
			       singleFrameDocument["height"].getValueInt32());
      }
    }
  } catch (const bson::BsonException &e) {
    throw graphic::AssetException(std::string("Unable to load asset '" + animSpecPath +"' : '" + e.what() + "'"));
  }
};

const sf::Texture &graphic::AnimatedSpriteAsset::getLowLevelTexture(void) const {
  return _texture;
};

const std::unordered_map<std::string, graphic::AnimatedSpriteAsset::FrameDescriptions> &graphic::AnimatedSpriteAsset::getAnimations(void) const {
  return _animations;
};
