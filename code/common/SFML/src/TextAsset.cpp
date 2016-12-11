#include "TextAsset.hh"

graphic::TextStyle::TextStyle(void) :
  thickness(graphic::TextStyle::DEFAUL_THICKNESS),
  size(graphic::TextStyle::DEFAUL_SIZE),
  fill(graphic::TextStyle::DEFAUL_FILL),
  out(graphic::TextStyle::DEFAUL_OUT)
{}

void graphic::TextStyle::setFill(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
  fill = sf::Color(r, g, b, a);
}

void graphic::TextStyle::setOut(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
  out = sf::Color(r, g, b, a);
}

graphic::TextAsset::TextAsset(const std::string &path) {
  std::ifstream asset;

  asset.open(path, std::fstream::in);
  if (!asset.is_open())
    throw AssetException("Unable to load text asset '" + path + "'");
  _text = new std::String(std::istreambuf_iterator<char>(asset), std::istreambuf_iterator<char>());
  asset.close();
}

const std::String &graphic::TextAsset::getText(void) const {
  return *_text;
}

graphic::TextAsset::~TextAsset(void) {
  delete _text;
}
