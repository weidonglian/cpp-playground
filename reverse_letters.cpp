#include <iostream>
#include <string>
#include <cctype>
#include <optional>

#include "cpptest.hpp"

//#define EXPECT_TRUE(e) if (!(e)) std::cout << "Failure:'" << (#e) << "' == false!" << std::endl;


std::string reverse_letters(const std::string& content) {
    std::string result;
    if (!content.empty()) {
        result.reserve(content.size());
        std::optional<int> b;
        int e = 0;
        for(int i = 0; i < content.size(); ++i) {
            bool is_alpha = std::isalpha(content[i]);
            if (is_alpha) {
                if (!b) { b = i; }
                e = i;
            } 
            if (!is_alpha || (is_alpha && i == content.size() -1)) {
                if (b) {
                    // now push the content reversely and then reset the b,e
                    for (int j = e; j >= b.value(); --j) {
                        result.push_back(content[j]);
                    }
                    b = std::nullopt;
                    e = 0;
                }
            }
            if (!is_alpha)
                result.push_back(content[i]);
        }
    }
    return result;
}

ADD_TEST_SUITE(ReverseLetters);

TEST(ReverseLetters, common) {
    EXPECT_TRUE(reverse_letters("; ABC ; ") == "; CBA ; ");
    EXPECT_TRUE(reverse_letters("; ABC") == "; CBA");
    EXPECT_TRUE(reverse_letters("ABC") == "CBA");
    EXPECT_TRUE(reverse_letters("ABC xyz; li, xiaogai; zhang") == "CBA zyx; il, iagoaix; gnahz");
}