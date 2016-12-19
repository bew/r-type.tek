/**
 * @file TextAsset.cpp
 * @brief Implementation for text asset
 * @author Nekhot
 */

#include "TextAsset.hh"

const unsigned int graphic::TextStyle::DEFAULT_SIZE = 30;
const float graphic::TextStyle::DEFAULT_THICKNESS = 1;
const sf::Color graphic::TextStyle::DEFAULT_FILL(255, 255, 255, 255);
const sf::Color graphic::TextStyle::DEFAULT_OUT(255, 255, 255, 255);

graphic::TextStyle::TextStyle(void) :
  thickness(graphic::TextStyle::DEFAULT_THICKNESS),
  size(graphic::TextStyle::DEFAULT_SIZE),
  fill(graphic::TextStyle::DEFAULT_FILL),
  out(graphic::TextStyle::DEFAULT_OUT)
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
  _text = new std::string(std::istreambuf_iterator<char>(asset), std::istreambuf_iterator<char>());
  asset.close();
}

const std::string &graphic::TextAsset::getText(void) const {
  return *_text;
}

graphic::TextAsset::~TextAsset(void) {
  delete _text;
}
