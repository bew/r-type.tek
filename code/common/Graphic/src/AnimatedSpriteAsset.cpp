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
      _animations[animationKey].frequency = animationDocument["frequency"].getValueInt64();
      if (_animations[animationKey].frequency < 1)
	throw graphic::AssetException(std::string("Frequency inferior to 1 are forbidden, in file '") + path + "'");
      const bson::Document &framesDocument = animationDocument["frames"].getValueDocument();
      for (auto frameKey : framesDocument.getKeys()) {
	const bson::Document &singleFrameDocument = framesDocument[frameKey].getValueDocument();
	_animations[animationKey]
	  .frames.emplace_back(singleFrameDocument["x"].getValueInt64(),
			       singleFrameDocument["y"].getValueInt64(),
			       singleFrameDocument["width"].getValueInt64(),
			       singleFrameDocument["height"].getValueInt64());
      }
      if (!_animations[animationKey].frames.size())
	throw graphic::AssetException(std::string("All animations need at least one frame, in file '") + path + "'");
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
