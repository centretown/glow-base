// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "Feature.h"

namespace glow
{
    template <class T>
    class FeatureValue : public Feature
    {
    private:
    protected:
        const char *label;
        T value;
        T high;

    public:
        FeatureValue(const char *label,
                     T value,
                     T high) : label(label), value(value), high(high) {}
        virtual ~FeatureValue() {}
        virtual const char *Label() { return label; }
        virtual feature_base Get()
        {
            return (feature_base)value;
        }
        virtual feature_base High()
        {
            return (feature_base)high;
        }
        virtual feature_base Low()
        {
            return 0;
        }
        virtual feature_base Filtered()
        {
            return Get();
        }
        virtual void Set(feature_base v)
        {
            feature_base h = High();
            value = (v > h) ? h : (T)v;
        }
        virtual char *Format(char *buffer, size_t bufLen)
        {
            snprintf(buffer, bufLen, Feature::U32_FORMAT, Get());
            return buffer;
        }
    };

    class FeatureU8 : public FeatureValue<uint8_t>
    {
    public:
        FeatureU8(const char *label,
                  uint8_t value,
                  uint8_t high) : FeatureValue(label, value, high) {}
    };

    class FeatureU16 : public FeatureValue<uint16_t>
    {
    public:
        FeatureU16(const char *label,
                   uint16_t value,
                   uint16_t high) : FeatureValue(label, value, high) {}
    };

    class FeatureU32 : public FeatureValue<uint32_t>
    {
    public:
        FeatureU32(const char *label,
                   uint16_t value,
                   uint16_t high) : FeatureValue(label, value, high) {}
    };
}
