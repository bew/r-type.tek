set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(GENERATOR_NAME hello)
set(GENERATOR_SOURCE hello.cpp)

add_library(${GENERATOR_NAME} SHARED ${GENERATOR_SOURCE})
target_link_libraries(${LEVELS_LIB} ${RT_COMMON_NAME})
install(TARGETS ${GENERATOR_NAME} DESTINATION bin/generators)
