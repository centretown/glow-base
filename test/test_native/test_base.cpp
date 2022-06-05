// Copyright (c) 2022 Dave Marsh. See LICENSE.

#ifndef ARDUINO

#define UNITY_INCLUDE_PRINT_FORMATTED
#include <unity.h>
#include "base.h"
uint64_t millis() { return 0; }

#include "FeatureValue.h"

void testFeature(Feature *f,
                 const char *label,
                 feature_base value,
                 feature_base high)
{
    TEST_ASSERT_EQUAL_STRING(label, f->Label());
    TEST_ASSERT_EQUAL(value, f->Get());
    TEST_ASSERT_EQUAL(high, f->High());
    TEST_ASSERT_EQUAL(0, f->Low());

    f->Set(f->High() - 1);
    TEST_ASSERT_EQUAL(f->High() - 1, f->Get());

    f->Set(f->High() + 1);
    TEST_ASSERT_EQUAL(f->High(), f->Get());

    f->Set(f->High() + 100);
    TEST_ASSERT_EQUAL(f->High(), f->Get());

    // restore original
    f->Set(value);
}

void testFeatureU8()
{
    char buffer[32];
    FeatureU8 *f = new FeatureU8("u8", 88, 100);
    testFeature(f, "u8", 88, 100);
    delete f;
}

void testFeatureU16()
{
    char buffer[32];
    FeatureU16 *f = new FeatureU16("u16", 5, 100);
    testFeature(f, "u16", 5, 100);

    TEST_ASSERT_EQUAL_STRING("5",
                             f->Format(buffer, sizeof(buffer)));
    f->Set(99);
    TEST_ASSERT_EQUAL(99, f->Get());
    TEST_ASSERT_EQUAL_STRING("99",
                             f->Format(buffer, sizeof(buffer)));
    f->Set(101);
    TEST_ASSERT_EQUAL(100, f->Get());
    TEST_ASSERT_EQUAL_STRING("100",
                             f->Format(buffer, sizeof(buffer)));

    delete f;
}

void testFeatureU32()
{
    char buffer[32];
    FeatureU32 *f = new FeatureU32("u32", 88, 100);
    testFeature(f, "u32", 88, 100);
    delete f;
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(testFeatureU8);
    RUN_TEST(testFeatureU16);
    RUN_TEST(testFeatureU32);
    UNITY_END();
}
#endif // not ARDUINO
