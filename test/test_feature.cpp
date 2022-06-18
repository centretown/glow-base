// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED
#include <unity.h>
#include "base.h"

#include "FeatureValue.h"

using namespace glow;

void testFeature(Feature &f,
                 const char *label,
                 feature_base value,
                 feature_base high)
{
    TEST_ASSERT_EQUAL_STRING(label, f.Label());
    TEST_ASSERT_EQUAL(value, f.Get());
    TEST_ASSERT_EQUAL(high, f.High());
    TEST_ASSERT_EQUAL(0, f.Low());

    f.Set(f.High() - 1);
    TEST_ASSERT_EQUAL(f.High() - 1, f.Get());

    f.Set(f.High() + 1);
    TEST_ASSERT_EQUAL(f.High(), f.Get());

    f.Set(f.High() + 100);
    TEST_ASSERT_EQUAL(f.High(), f.Get());

    // restore original
    f.Set(value);
    TEST_ASSERT_EQUAL(value, f.Get());
}

void testFeatureU8()
{
    FeatureU8 f("u8", 88, 100);
    testFeature(f, "u8", 88, 100);
}

void testFeatureU16()
{
    char buffer[32];
    FeatureU16 f("u16", 5, 100);
    testFeature(f, "u16", 5, 100);

    TEST_ASSERT_EQUAL_STRING("5",
                             f.Format(buffer, sizeof(buffer)));
    f.Set(99);
    TEST_ASSERT_EQUAL(99, f.Get());
    TEST_ASSERT_EQUAL_STRING("99",
                             f.Format(buffer, sizeof(buffer)));
    f.Set(101);
    TEST_ASSERT_EQUAL(100, f.Get());
    TEST_ASSERT_EQUAL_STRING("100",
                             f.Format(buffer, sizeof(buffer)));
}

void testFeatureU32()
{
    FeatureU32 f("u32", 88, 100);
    testFeature(f, "u32", 88, 100);
}

void testFeatures()
{
    RUN_TEST(testFeatureU8);
    RUN_TEST(testFeatureU16);
    RUN_TEST(testFeatureU32);
}
