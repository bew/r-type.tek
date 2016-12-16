#include <fstream>
#include "AnimatedSpriteAsset.hh"

graphic::AnimatedSpriteAsset::AnimatedSpriteAsset(const std::string &path, const std::string &animSpecPath) {
  if (!_texture.loadFromFile(path))
    throw AssetException("Unable to load asset : '" + path + "'");

  
  std::basic_ifstream<unsigned char> file(animSpecPath, std::ios::binary);
  
  std::vector<unsigned char> buffer((std::istreambuf_iterator<unsigned char>(file)),
				    std::istreambuf_iterator<unsigned char>());

  try {
    const bson::Document document(buffer);
    for (auto animationKey = document.getKeys().begin();
	 animationKey < document.getKeys().end();
	 animationKey++) {
      
      const bson::Document &animationDocument = document[*animationKey].getValueDocument();
      _animations[*animationKey].frequency = animationDocument["frequency"].getValueDouble();
      const bson::Document &framesDocument = animationDocument["frames"].getValueDocument();
      for (auto frameKey = framesDocument.getKeys().begin();
	   frameKey < framesDocument.getKeys().end();
	   frameKey++) {
	
	const bson::Document &singleFrameDocument = framesDocument[*frameKey].getValueDocument();
	_animations[*animationKey]
	  .frames.emplace_back(singleFrameDocument["x"].getValueInt32(),
			       singleFrameDocument["y"].getValueInt32(),
			       singleFrameDocument["width"].getValueInt32(),
			       singleFrameDocument["height"].getValueInt32());
      }
    }
  } catch (const bson::BsonException &e) {
    throw graphic::AssetException(std::string("Unable to load asset '" + animSpecPath +"' : '" + e.what() + "'"));
  }
}
