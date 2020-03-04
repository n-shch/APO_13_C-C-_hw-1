//
// Created by nick on 04.03.2020.
//


#include "gtest/gtest.h"

extern "C" {
    #include "testy/parser.h"
}

char line[] = "commit d5d7ecaf88dc1f492f05cb055350b47db2987e79";
char field[] = "commit";
char *result = line + strlen(field);

TEST(search_field_test, valid_data) {
    ASSERT_EQ(result, search_field(line, field));
}

TEST(testy, not_ok) {
    ASSERT_EQ(0, func(0));
}
