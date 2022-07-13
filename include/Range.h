// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"

namespace glow
{
    typedef uint32_t range_pack;
    typedef struct
    {
        uint16_t begin;
        uint16_t end;
    } range_limits;

    const uint16_t upper_limit = 0xffff;

    class Range
    {
    private:
        union
        {
            range_pack pack;
            range_limits limits;
        };

    public:
        Range(range_pack pack = 0)
        {
            Pack(pack);
        }

        Range(uint16_t begin, uint16_t end)
        {
            Resize(begin, end);
        }

        Range(Range &range) : Range(range.Pack()) {}

        // access
        inline uint16_t Begin() const { return limits.begin; }
        inline uint16_t End() const { return limits.end; }
        inline range_pack Pack() const { return pack; }
        inline uint16_t Length() const { return End() - Begin(); }

        // modify
        inline void Pack(range_pack v)
        {
            pack = v;
            Resize(limits.begin, limits.end);
        }

        inline Range &operator=(const Range &other)
        {
            Pack(other.Pack());
            return *this;
        }

        inline Range &operator=(range_pack other)
        {
            Pack(other);
            return *this;
        }

        // move
        inline Range &operator++()
        {
            if (limits.end < upper_limit)
            {
                ++limits.begin;
                ++limits.end;
                Resize(limits.begin, limits.end);
            }
            return *this;
        }

        inline Range &operator--()
        {
            if (limits.begin > 0)
            {
                --limits.begin;
                --limits.end;
                Resize(limits.begin, limits.end);
            }
            return *this;
        }

        inline Range &operator+=(uint16_t v)
        {
            uint16_t end = v + limits.end;
            if (end > limits.end)
            {
                Resize(limits.begin + v, limits.end + v);
            }
            return *this;
        }

        inline Range &operator-=(uint16_t v)
        {
            if (v <= limits.begin)
            {
                Resize(Begin() - v, End() - v);
            }
            return *this;
        }

        inline range_pack operator+(uint16_t v)
        {
            uint16_t end = v + limits.end;
            if (end < limits.end)
            {
                return Pack();
            }
            return Range(Begin() + v, End() + v).Pack();
        }

        inline range_pack operator-(uint16_t v)
        {
            if (v > limits.begin)
            {
                return Pack();
            }
            return Range(Begin() - v, End() - v).Pack();
        }

        // squeeze
        inline Range &operator>>=(const uint16_t v)
        {
            uint16_t begin = v + Begin();
            if (begin > Begin() && begin <= End())
            {
                Resize(begin, End());
            }
            return *this;
        }

        inline Range &operator<<=(const uint16_t v)
        {
            uint16_t end = End() - v;
            if (end < End() && end >= Begin())
            {
                Resize(Begin(), end);
            }
            return *this;
        }

        inline range_pack operator<<(const uint16_t v)
        {
            uint16_t end = End() - v;
            if (end < End() && end >= Begin())
            {
                return Range(Begin(), end).Pack();
            }
            return Pack();
        }

        inline range_pack operator>>(const uint16_t v)
        {
            uint16_t begin = v + Begin();
            if (begin > Begin() && begin <= End())
            {
                return Range(begin, End()).Pack();
            }
            return Pack();
        }

        inline void Copy(Range &range)
        {
            Pack(range.Pack());
        }

        inline void Resize(uint16_t begin, uint16_t end)
        {
            if (end < begin)
            {
                uint16_t v = end;
                end = begin;
                begin = v;
            }
            limits.begin = begin;
            limits.end = end;
        }

        // implement
        template <typename PUTTER, typename VALUE>
        inline void Spin(PUTTER &putter, VALUE value)
        {
            for (uint16_t i = Begin(); i < End(); i++)
            {
                putter.Put(i, value);
            }
            putter.Update();
        }

        template <typename PUTTER, typename MAPPER, typename VALUE>
        inline void Spin(PUTTER &putter, MAPPER &mapper, VALUE value)
        {
            for (uint16_t i = Begin(); i < End(); i++)
            {
                putter.Put(mapper.Map(i), value);
            }
            putter.Update();
        }

        template <typename PUTTER, typename VALUE>
        inline void ReverseSpin(PUTTER &putter, VALUE value)
        {
            const uint16_t length = Length();
            for (uint16_t i = 1; i <= length; i++)
            {
                putter.Put(End() - i, value);
            }
            putter.Update();
        }

        template <typename PUTTER, typename MAPPER, typename VALUE>
        inline void ReverseSpin(PUTTER &putter, MAPPER &mapper, VALUE value)
        {
            const uint16_t length = Length();
            for (uint16_t i = 1; i <= length; i++)
            {
                putter.Put(mapper.Map(End() - i), value);
            }
            putter.Update();
        }
    };
}