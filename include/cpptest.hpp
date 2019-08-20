#pragma once

#include <gtest/gtest.h>

#define ADD_TEST_SUITE(NAME) class NAME : public ::testing::Test {}
