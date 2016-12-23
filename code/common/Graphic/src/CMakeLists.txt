cmake_minimum_required(VERSION 3.0)

set(LIB_SOURCES AssetException.cpp SpriteAsset.cpp AnimatedSpriteAsset.cpp FontAsset.cpp TextAsset.cpp MusicAsset.cpp SoundAsset.cpp AssetStore.cpp)
set(LIB_DEPENDENCIES sfml-graphics sfml-window sfml-system sfml-audio BSON FSWatcher)

add_library(${LIB_NAME} STATIC ${LIB_SOURCES})
target_link_libraries(${LIB_NAME} ${LIB_DEPENDENCIES})
target_include_directories(${LIB_NAME} PUBLIC ${LIB_INCLUDE})

add_custom_command(TARGET ${LIB_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${LIB_INCLUDE} ${RT_COMMON_INCLUDES}/${LIB_NAME}
        )