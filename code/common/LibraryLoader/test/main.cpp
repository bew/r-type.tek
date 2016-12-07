//
// Created by Pierre Rousselle on 18/11/2016.
//

#include <iostream>
#include <string>

#include "ALibraryLoader.hh"
#include "Dependent_ptr.hpp"
#include "gtest/gtest.h"

Dependent_ptr<IGenerator, LibraryLoader> my_safe_factory(const std::string &path) {
  std::shared_ptr<LibraryLoader> module(new LibraryLoader(path));
  Dependent_ptr<IGenerator, LibraryLoader> instance(module->newInstance(), module);
  return instance;
}

TEST(LibraryLoader, Load) {
  Dependent_ptr<IGenerator, LibraryLoader> instance = my_safe_factory("./generators/libempty_test_generator.so");
  ASSERT_EQ(instance->getName(), "Empty generator");
}

TEST(LibraryLoader, Fail) {
  ASSERT_THROW(my_safe_factory("fake"), LibraryLoaderException);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
};
