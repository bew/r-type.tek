set(LIB_SOURCE AssetException.cpp SpriteAsset.cpp AnimatedSpriteAsset.cpp FontAsset.cpp TextAsset.cpp MusicAsset.cpp SoundAsset.cpp AssetStore.cpp)
set(LIB_DEPENDENCIES sfml-graphics sfml-audio sfml-window sfml-system)

add_library(${LIB_NAME} STATIC ${LIB_SOURCE})
add_library(${LIB_TEST_NAME} SHARED ${LIB_SOURCE})
target_link_libraries(${LIB_NAME} ${LIB_DEPENDENCIES})
target_link_libraries(${LIB_TEST_NAME} ${LIB_DEPENDENCIES})
install(TARGETS ${LIB_TEST_NAME} DESTINATION bin/test/lib)
target_include_directories(${LIB_NAME} PUBLIC ${LIB_INCLUDE})
target_include_directories(${LIB_TEST_NAME} PUBLIC ${LIB_INCLUDE})
set(RT_COMMON_NAMES ${RT_COMMON_NAMES} ${LIB_NAME} PARENT_SCOPE)
add_custom_command(TARGET ${LIB_NAME}
                   POST_BUILD
                   COMMAND  ${CMAKE_COMMAND} -E copy_directory ${LIB_INCLUDE} ${RT_COMMON_INCLUDES}/${LIB_NAME}
                   )
