cmake_minimum_required(VERSION 3.0)

add_library(${LIB_NAME} STATIC AssetException.cpp SpriteAsset.cpp AnimatedSpriteAsset.cpp FontAsset.cpp TextAsset.cpp MusicAsset.cpp SoundAsset.cpp AssetStore.cpp)
target_link_libraries(${LIB_NAME} sfml-graphics sfml-window sfml-system sfml-audio BSON FSWatcher)
target_include_directories(${LIB_NAME} PUBLIC ${LIB_INCLUDE})