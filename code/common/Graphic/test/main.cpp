//
// Created by Pierre Rousselle on 18/11/2016.
//
#include "gtest/gtest.h"
#include "AssetStore.hpp"

///////////////////////////////////////////////////

/**
 * Testc cas: Existing ressource, with default locale
 */
TEST(Font, LoadExistingDefault) {
  graphic::AssetStore store("asset");

  ASSERT_NO_THROW(store.loadFont("test"));
}

TEST(Font, GetExistingDefault) {
  graphic::AssetStore store("asset");

  ASSERT_NO_THROW(store.loadFont("test"));
  ASSERT_NO_THROW(store.getFont("test"));
}

TEST(Font, FreeExistingDefault) {
  graphic::AssetStore store("asset");

  ASSERT_NO_THROW(store.loadFont("test"));
  ASSERT_NO_THROW(store.getFont("test"));
  ASSERT_NO_THROW(store.freeFont("test"));
}

/**
 * Test case: Existing ressource in locale
 */
TEST(Font, LoadExistingLocale) {
  graphic::AssetStore store("asset", "fr");

  ASSERT_NO_THROW(store.loadFont("test"));
}

TEST(Font, GetExistingLocale) {
  graphic::AssetStore store("asset", "fr");

  ASSERT_NO_THROW(store.loadFont("test"));
  ASSERT_NO_THROW(store.getFont("test"));
}

TEST(Font, FreeExistingLocale) {
  graphic::AssetStore store("asset", "fr");

  ASSERT_NO_THROW(store.loadFont("test"));
  ASSERT_NO_THROW(store.getFont("test"));
  ASSERT_NO_THROW(store.freeFont("test"));
}

/**
 * Test case: Missing ressource 
 */
TEST(Font, LoadMissing) {

  graphic::AssetStore store("asset");

  ASSERT_THROW(store.loadFont("fake"), graphic::AssetException);
}

TEST(Font, GetMissing) {
  graphic::AssetStore store("asset");

  ASSERT_THROW(store.loadFont("fake"), graphic::AssetException);
  ASSERT_THROW(store.getFont("fake"), graphic::AssetException);
}

TEST(Font, FreeMissing) {
  graphic::AssetStore store("asset");

  ASSERT_THROW(store.loadFont("fake"), graphic::AssetException);
  ASSERT_THROW(store.getFont("fake"), graphic::AssetException);
  store.freeFont("fake");
}


/**
 * Test case: ressource existing in default local
 */
TEST(Font, LoadFallback) {
  graphic::AssetStore store("asset", "fr");

  ASSERT_NO_THROW(store.loadFont("default"));
}

TEST(Font, GetFallback) {
  graphic::AssetStore store("asset", "fr");

  ASSERT_NO_THROW(store.loadFont("default"));
  ASSERT_NO_THROW(store.getFont("default"));
}

TEST(Font, FreeFallback) {
  graphic::AssetStore store("asset", "fr");

  ASSERT_NO_THROW(store.loadFont("default"));
  ASSERT_NO_THROW(store.getFont("default"));
  ASSERT_NO_THROW(store.freeFont("default"));
}

///////////////////////////////////////////////////////

/**
 * Testc cas: Existing ressource, with default locale
 */
TEST(Music, LoadExistingDefault) {
  graphic::AssetStore store("asset");

  ASSERT_NO_THROW(store.loadMusic("test"));
}

TEST(Music, GetExistingDefault) {
  graphic::AssetStore store("asset");

  ASSERT_NO_THROW(store.loadMusic("test"));
  ASSERT_NO_THROW(store.getMusic("test"));
}

TEST(Music, FreeExistingDefault) {
  graphic::AssetStore store("asset");

  ASSERT_NO_THROW(store.loadMusic("test"));
  ASSERT_NO_THROW(store.getMusic("test"));
  ASSERT_NO_THROW(store.freeMusic("test"));
}

/**
 * Test case: Existing ressource in locale
 */
TEST(Music, LoadExistingLocale) {
  graphic::AssetStore store("asset", "fr");

  ASSERT_NO_THROW(store.loadMusic("test"));
}

TEST(Music, GetExistingLocale) {
  graphic::AssetStore store("asset", "fr");

  ASSERT_NO_THROW(store.loadMusic("test"));
  ASSERT_NO_THROW(store.getMusic("test"));
}

TEST(Music, FreeExistingLocale) {
  graphic::AssetStore store("asset", "fr");

  ASSERT_NO_THROW(store.loadMusic("test"));
  ASSERT_NO_THROW(store.getMusic("test"));
  ASSERT_NO_THROW(store.freeMusic("test"));
}

/**
 * Test case: Missing ressource 
 */
TEST(Music, LoadMissing) {

  graphic::AssetStore store("asset");

  ASSERT_THROW(store.loadMusic("fake"), graphic::AssetException);
}

TEST(Music, GetMissing) {
  graphic::AssetStore store("asset");

  ASSERT_THROW(store.loadMusic("fake"), graphic::AssetException);
  ASSERT_THROW(store.getMusic("fake"), graphic::AssetException);
}

TEST(Music, FreeMissing) {
  graphic::AssetStore store("asset");

  ASSERT_THROW(store.loadMusic("fake"), graphic::AssetException);
  ASSERT_THROW(store.getMusic("fake"), graphic::AssetException);
  store.freeMusic("fake");
}


/**
 * Test case: ressource existing in default local
 */
TEST(Music, LoadFallback) {
  graphic::AssetStore store("asset", "fr");

  ASSERT_NO_THROW(store.loadMusic("default"));
}

TEST(Music, GetFallback) {
  graphic::AssetStore store("asset", "fr");

  ASSERT_NO_THROW(store.loadMusic("default"));
  ASSERT_NO_THROW(store.getMusic("default"));
}

TEST(Music, FreeFallback) {
  graphic::AssetStore store("asset", "fr");

  ASSERT_NO_THROW(store.loadMusic("default"));
  ASSERT_NO_THROW(store.getMusic("default"));
  ASSERT_NO_THROW(store.freeMusic("default"));
}

////////////////////////////////////////////////////////////

/**
 * Testc cas: Existing ressource, with default locale
 */
TEST(Sound, LoadExistingDefault) {
  graphic::AssetStore store("asset");

  ASSERT_NO_THROW(store.loadSound("test"));
}

TEST(Sound, GetExistingDefault) {
  graphic::AssetStore store("asset");

  ASSERT_NO_THROW(store.loadSound("test"));
  ASSERT_NO_THROW(store.getSound("test"));
}

TEST(Sound, FreeExistingDefault) {
  graphic::AssetStore store("asset");

  ASSERT_NO_THROW(store.loadSound("test"));
  ASSERT_NO_THROW(store.getSound("test"));
  ASSERT_NO_THROW(store.freeSound("test"));
}

/**
 * Test case: Existing ressource in locale
 */
TEST(Sound, LoadExistingLocale) {
  graphic::AssetStore store("asset", "fr");

  ASSERT_NO_THROW(store.loadSound("test"));
}

TEST(Sound, GetExistingLocale) {
  graphic::AssetStore store("asset", "fr");

  ASSERT_NO_THROW(store.loadSound("test"));
  ASSERT_NO_THROW(store.getSound("test"));
}

TEST(Sound, FreeExistingLocale) {
  graphic::AssetStore store("asset", "fr");

  ASSERT_NO_THROW(store.loadSound("test"));
  ASSERT_NO_THROW(store.getSound("test"));
  ASSERT_NO_THROW(store.freeSound("test"));
}

/**
 * Test case: Missing ressource 
 */
TEST(Sound, LoadMissing) {

  graphic::AssetStore store("asset");

  ASSERT_THROW(store.loadSound("fake"), graphic::AssetException);
}

TEST(Sound, GetMissing) {
  graphic::AssetStore store("asset");

  ASSERT_THROW(store.loadSound("fake"), graphic::AssetException);
  ASSERT_THROW(store.getSound("fake"), graphic::AssetException);
}

TEST(Sound, FreeMissing) {
  graphic::AssetStore store("asset");

  ASSERT_THROW(store.loadSound("fake"), graphic::AssetException);
  ASSERT_THROW(store.getSound("fake"), graphic::AssetException);
  store.freeSound("fake");
}


/**
 * Test case: ressource existing in default local
 */
TEST(Sound, LoadFallback) {
  graphic::AssetStore store("asset", "fr");

  ASSERT_NO_THROW(store.loadSound("default"));
}

TEST(Sound, GetFallback) {
  graphic::AssetStore store("asset", "fr");

  ASSERT_NO_THROW(store.loadSound("default"));
  ASSERT_NO_THROW(store.getSound("default"));
}

TEST(Sound, FreeFallback) {
  graphic::AssetStore store("asset", "fr");

  ASSERT_NO_THROW(store.loadSound("default"));
  ASSERT_NO_THROW(store.getSound("default"));
  ASSERT_NO_THROW(store.freeSound("default"));
}

/////////////////////////////////////////////////////////////////////


/**
 * Testc cas: Existing ressource, with default locale
 */
TEST(Text, LoadExistingDefault) {
  graphic::AssetStore store("asset");

  ASSERT_NO_THROW(store.loadText("test"));
}

TEST(Text, GetExistingDefault) {
  graphic::AssetStore store("asset");

  ASSERT_NO_THROW(store.loadText("test"));
  ASSERT_NO_THROW(store.getText("test"));
}

TEST(Text, FreeExistingDefault) {
  graphic::AssetStore store("asset");

  ASSERT_NO_THROW(store.loadText("test"));
  ASSERT_NO_THROW(store.getText("test"));
  ASSERT_NO_THROW(store.freeText("test"));
}

/**
 * Test case: Existing ressource in locale
 */
TEST(Text, LoadExistingLocale) {
  graphic::AssetStore store("asset", "fr");

  ASSERT_NO_THROW(store.loadText("test"));
}

TEST(Text, GetExistingLocale) {
  graphic::AssetStore store("asset", "fr");

  ASSERT_NO_THROW(store.loadText("test"));
  ASSERT_NO_THROW(store.getText("test"));
}

TEST(Text, FreeExistingLocale) {
  graphic::AssetStore store("asset", "fr");

  ASSERT_NO_THROW(store.loadText("test"));
  ASSERT_NO_THROW(store.getText("test"));
  ASSERT_NO_THROW(store.freeText("test"));
}

/**
 * Test case: Missing ressource 
 */
TEST(Text, LoadMissing) {

  graphic::AssetStore store("asset");

  ASSERT_THROW(store.loadText("fake"), graphic::AssetException);
}

TEST(Text, GetMissing) {
  graphic::AssetStore store("asset");

  ASSERT_THROW(store.loadText("fake"), graphic::AssetException);
  ASSERT_THROW(store.getText("fake"), graphic::AssetException);
}

TEST(Text, FreeMissing) {
  graphic::AssetStore store("asset");

  ASSERT_THROW(store.loadText("fake"), graphic::AssetException);
  ASSERT_THROW(store.getText("fake"), graphic::AssetException);
  store.freeText("fake");
}


/**
 * Test case: ressource existing in default local
 */
TEST(Text, LoadFallback) {
  graphic::AssetStore store("asset", "fr");

  ASSERT_NO_THROW(store.loadText("default"));
}

TEST(Text, GetFallback) {
  graphic::AssetStore store("asset", "fr");

  ASSERT_NO_THROW(store.loadText("default"));
  ASSERT_NO_THROW(store.getText("default"));
}

TEST(Text, FreeFallback) {
  graphic::AssetStore store("asset", "fr");

  ASSERT_NO_THROW(store.loadText("default"));
  ASSERT_NO_THROW(store.getText("default"));
  ASSERT_NO_THROW(store.freeText("default"));
}

///////////////////////////////////////////////////////////


/**
 * Testc cas: Existing ressource, with default locale
 */
TEST(Sprite, LoadExistingDefault) {
  graphic::AssetStore store("asset");

  ASSERT_NO_THROW(store.loadSprite("test"));
}

TEST(Sprite, GetExistingDefault) {
  graphic::AssetStore store("asset");

  ASSERT_NO_THROW(store.loadSprite("test"));
  ASSERT_NO_THROW(store.getSprite("test"));
}

TEST(Sprite, FreeExistingDefault) {
  graphic::AssetStore store("asset");

  ASSERT_NO_THROW(store.loadSprite("test"));
  ASSERT_NO_THROW(store.getSprite("test"));
  ASSERT_NO_THROW(store.freeSprite("test"));
}

/**
 * Test case: Existing ressource in locale
 */
TEST(Sprite, LoadExistingLocale) {
  graphic::AssetStore store("asset", "fr");

  ASSERT_NO_THROW(store.loadSprite("test"));
}

TEST(Sprite, GetExistingLocale) {
  graphic::AssetStore store("asset", "fr");

  ASSERT_NO_THROW(store.loadSprite("test"));
  ASSERT_NO_THROW(store.getSprite("test"));
}

TEST(Sprite, FreeExistingLocale) {
  graphic::AssetStore store("asset", "fr");

  ASSERT_NO_THROW(store.loadSprite("test"));
  ASSERT_NO_THROW(store.getSprite("test"));
  ASSERT_NO_THROW(store.freeSprite("test"));
}

/**
 * Test case: Missing ressource 
 */
TEST(Sprite, LoadMissing) {

  graphic::AssetStore store("asset");

  ASSERT_THROW(store.loadSprite("fake"), graphic::AssetException);
}

TEST(Sprite, GetMissing) {
  graphic::AssetStore store("asset");

  ASSERT_THROW(store.loadSprite("fake"), graphic::AssetException);
  ASSERT_THROW(store.getSprite("fake"), graphic::AssetException);
}

TEST(Sprite, FreeMissing) {
  graphic::AssetStore store("asset");

  ASSERT_THROW(store.loadSprite("fake"), graphic::AssetException);
  ASSERT_THROW(store.getSprite("fake"), graphic::AssetException);
  store.freeSprite("fake");
}


/**
 * Test case: ressource existing in default local
 */
TEST(Sprite, LoadFallback) {
  graphic::AssetStore store("asset", "fr");

  ASSERT_NO_THROW(store.loadSprite("default"));
}

TEST(Sprite, GetFallback) {
  graphic::AssetStore store("asset", "fr");

  ASSERT_NO_THROW(store.loadSprite("default"));
  ASSERT_NO_THROW(store.getSprite("default"));
}

TEST(Sprite, FreeFallback) {
  graphic::AssetStore store("asset", "fr");

  ASSERT_NO_THROW(store.loadSprite("default"));
  ASSERT_NO_THROW(store.getSprite("default"));
  ASSERT_NO_THROW(store.freeSprite("default"));
}

////////////////////////////////////////////////////////

/**
 * Testc cas: Existing ressource, with default locale
 */
TEST(AnimatedSprite, LoadExistingDefault) {
  graphic::AssetStore store("asset");

  store.loadAnimatedSprite("test");
}

TEST(AnimatedSprite, GetExistingDefault) {
  graphic::AssetStore store("asset");

  ASSERT_NO_THROW(store.loadAnimatedSprite("test"));
  ASSERT_NO_THROW(store.getAnimatedSprite("test"));
}

TEST(AnimatedSprite, FreeExistingDefault) {
  graphic::AssetStore store("asset");

  ASSERT_NO_THROW(store.loadAnimatedSprite("test"));
  ASSERT_NO_THROW(store.getAnimatedSprite("test"));
  ASSERT_NO_THROW(store.freeAnimatedSprite("test"));
}

/**
 * Test case: Existing ressource in locale
 */
TEST(AnimatedSprite, LoadExistingLocale) {
  graphic::AssetStore store("asset", "fr");

  ASSERT_NO_THROW(store.loadAnimatedSprite("test"));
}

TEST(AnimatedSprite, GetExistingLocale) {
  graphic::AssetStore store("asset", "fr");

  ASSERT_NO_THROW(store.loadAnimatedSprite("test"));
  ASSERT_NO_THROW(store.getAnimatedSprite("test"));
}

TEST(AnimatedSprite, FreeExistingLocale) {
  graphic::AssetStore store("asset", "fr");

  ASSERT_NO_THROW(store.loadAnimatedSprite("test"));
  ASSERT_NO_THROW(store.getAnimatedSprite("test"));
  ASSERT_NO_THROW(store.freeAnimatedSprite("test"));
}

/**
 * Test case: Missing ressource 
 */
TEST(AnimatedSprite, LoadMissing) {

  graphic::AssetStore store("asset");

  ASSERT_THROW(store.loadAnimatedSprite("fake"), graphic::AssetException);
}

TEST(AnimatedSprite, GetMissing) {
  graphic::AssetStore store("asset");

  ASSERT_THROW(store.loadAnimatedSprite("fake"), graphic::AssetException);
  ASSERT_THROW(store.getAnimatedSprite("fake"), graphic::AssetException);
}

TEST(AnimatedSprite, FreeMissing) {
  graphic::AssetStore store("asset");

  ASSERT_THROW(store.loadAnimatedSprite("fake"), graphic::AssetException);
  ASSERT_THROW(store.getAnimatedSprite("fake"), graphic::AssetException);
  store.freeAnimatedSprite("fake");
}

/**
 * Test case: ressource existing in default local
 */
TEST(AnimatedSprite, LoadFallback) {
  graphic::AssetStore store("asset", "fr");

  ASSERT_NO_THROW(store.loadAnimatedSprite("default"));
}

TEST(AnimatedSprite, GetFallback) {
  graphic::AssetStore store("asset", "fr");

  ASSERT_NO_THROW(store.loadAnimatedSprite("default"));
  ASSERT_NO_THROW(store.getAnimatedSprite("default"));
}

TEST(AnimatedSprite, FreeFallback) {
  graphic::AssetStore store("asset", "fr");

  ASSERT_NO_THROW(store.loadAnimatedSprite("default"));
  ASSERT_NO_THROW(store.getAnimatedSprite("default"));
  ASSERT_NO_THROW(store.freeAnimatedSprite("default"));
}

////////////////////////////////////////////////////////

/**
 * Test loadall
 */
TEST(Grouped, loadAll) {
  graphic::GroupedAssetStore store(".", "asset", "fr");

  ASSERT_NO_THROW(store.loadAll());


  ASSERT_NO_THROW(store.getSprite("default"));
  ASSERT_NO_THROW(store.getSound("default"));
  ASSERT_NO_THROW(store.getMusic("default"));
  ASSERT_NO_THROW(store.getText("default"));

  ASSERT_NO_THROW(store.getSprite("test"));
  ASSERT_NO_THROW(store.getSound("test"));
  ASSERT_NO_THROW(store.getMusic("test"));
  ASSERT_NO_THROW(store.getText("test"));
  
  ASSERT_THROW(store.getSprite("fake"), graphic::AssetException);
  ASSERT_THROW(store.getSound("fake"), graphic::AssetException);
  ASSERT_THROW(store.getMusic("fake"), graphic::AssetException);
  ASSERT_THROW(store.getText("fake"), graphic::AssetException);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
};
