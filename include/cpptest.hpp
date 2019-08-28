#pragma once

#include <gtest/gtest.h>

#define ADD_TEST_SUITE(NAME) class NAME : public ::testing::Test {}

ADD_TEST_SUITE(ArraySuite);

struct test_input_output {
    std::string input;
    std::string output;
};