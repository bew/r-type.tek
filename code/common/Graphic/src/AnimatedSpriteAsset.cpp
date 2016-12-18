#include "AnimatedSpriteAsset.hh"

graphic::AnimatedSpriteAsset::AnimatedSpriteAsset(const std::string &path, const std::string &animSpecPath) {
  if (!_texture.loadFromFile(path))
    throw AssetException("Unable to load animated sprite asset : '" + path + "'");
  std::ifstream file(animSpecPath, std::ios::binary);
  if (!file.is_open())
     throw AssetException("Unable to load animation description asset : '" + animSpecPath + "'");
  file.unsetf(std::ios::skipws);
  std::streampos fileSize;
  file.seekg(0, std::ios::end);
  fileSize = file.tellg();
  file.seekg(0, std::ios::beg);
  std::vector<unsigned char> buffer;
  buffer.reserve(fileSize);
  buffer.insert(buffer.begin(),
		std::istream_iterator<unsigned char>(file),
		std::istream_iterator<unsigned char>());
  try {
    const bson::Document document(buffer);    
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
