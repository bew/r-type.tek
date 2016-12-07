add_executable(BSON_test main.cpp serialization.cpp miscellaneous.cpp)
target_link_libraries(BSON_test gtest)
target_link_libraries(BSON_test libBSON_test)