add_executable(BSON_test main.cpp miscellaneous.cpp serialization.cpp deserialization.cpp)
target_link_libraries(BSON_test gtest)
target_link_libraries(BSON_test libBSON_test)