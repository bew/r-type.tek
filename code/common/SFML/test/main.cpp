//
// Created by Pierre Rousselle on 18/11/2016.
//
#include "gtest/gtest.h"
#include "AssetStore.hh"

/**
 * Testc cas: Existing ressource, with default locale
 */
TEST(Text, LoadExistingDefault) {
  graphic::AssetStore store("asset");

  store.loadMusic("test");
}

TEST(Text, GetExistingDefault) {
  graphic::AssetStore store("asset");

  store.loadMusic("test");
  store.getMusic("test");
}

TEST(Text, FreeExistingDefault) {
  graphic::AssetStore store("asset");

  store.loadMusic("test");
  store.getMusic("test");
  store.freeMusic("test");
}

/**
 * Test case: Existing ressource in locale
 */
TEST(Text, LoadExistingLocale) {
  graphic::AssetStore store("asset", "fr");

  store.loadMusic("test");
}

TEST(Text, GetExistingLocale) {
  graphic::AssetStore store("asset", "fr");

  store.loadMusic("test");
  store.getMusic("test");
}

TEST(Text, FreeExistingLocale) {
  graphic::AssetStore store("asset", "fr");

  store.loadMusic("test");
  store.getMusic("test");
  store.freeMusic("test");
}

/**
 * Test case: Missing ressource 
 */
TEST(Text, LoadMissing) {

  graphic::AssetStore store("asset");

  store.loadMusic("fake");
}

TEST(Text, GetMissing) {
  graphic::AssetStore store("asset");

  store.loadMusic("fake");
  store.getMusic("fake");
}

TEST(Text, FreeMissing) {
  graphic::AssetStore store("asset");

  store.loadMusic("fake");
  store.getMusic("fake");
  store.freeMusic("fake");
}


/**
 * Test case: ressource existing in default local
 */
TEST(Text, LoadFallback) {
  graphic::AssetStore store("asset", "fr");

  store.loadMusic("default");
}

TEST(Text, GetFallback) {
  graphic::AssetStore store("asset", "fr");

  store.loadMusic("default");
  store.getMusic("default");
}

TEST(Text, FreeFallback) {
  graphic::AssetStore store("asset", "fr");

  store.loadMusic("default");
  store.getMusic("default");
  store.freeMusic("default");
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
};
