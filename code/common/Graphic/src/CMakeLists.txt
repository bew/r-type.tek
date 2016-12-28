cmake_minimum_required(VERSION 3.1)

set(LIB_SOURCES AssetException.cpp SpriteAsset.cpp AnimatedSpriteAsset.cpp FontAsset.cpp TextAsset.cpp MusicAsset.cpp SoundAsset.cpp AssetStore.cpp)
set(LIB_DEPENDENCIES sfml-graphics sfml-window sfml-system sfml-audio BSON FSWatcher Logs)

add_library(${LIB_NAME} STATIC ${LIB_SOURCES})
target_link_libraries(${LIB_NAME} ${LIB_DEPENDENCIES})

copy(${LIB_NAME} ${LIB_INCLUDE} ${RT_COMMON_INCLUDES}/${LIB_NAME})
