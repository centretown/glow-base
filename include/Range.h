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

    class Range
    {
    private:
        union
        {
            range_pack pack;
            range_limits limits;
        };

        const static uint16_t lower_limit = 0;
        const static uint16_t upper_limit = 0xffff;

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
        inline uint16_t Length() const { return limits.end - limits.begin; }
        inline range_pack Pack() const { return pack; }

        // modify
        inline range_pack Pack(range_pack v)
        {
            pack = v;
            return Resize(limits.begin, limits.end);
        }

        inline void Copy(Range &range)
        {
            Pack(range.Pack());
        }

        inline range_pack operator()() const
        {
            return pack;
        }

        inline range_pack operator()(range_pack v)
        {
            return pack = v;
        }

        inline range_pack operator()(uint16_t begin, uint16_t end)
        {
            return Resize(begin, end);
        }

        inline Range &operator=(const Range &other)
        {
            Pack(other());
            return *this;
        }

        inline Range &operator=(range_pack other)
        {
            Pack(other);
            return *this;
        }

        // resize
        inline Range &operator++()
        {
            if (limits.end < upper_limit)
            {
                ++limits.end;
                Resize(limits.begin, limits.end);
            }
            return *this;
        }

        inline Range &operator--()
        {
            if (limits.end > limits.begin)
            {
                --limits.end;
                Resize(limits.begin, limits.end);
            }
            return *this;
        }

        inline range_pack operator+(uint16_t v) const
        {
            uint16_t end = limits.end + v;
            if (end < limits.end)
            {
                end = upper_limit;
            }
            return Range(limits.begin, end)
                .Pack();
        }

        inline range_pack operator-(uint16_t v) const
        {
            uint16_t end = limits.end - v;
            if (end < limits.begin || end > limits.end)
            {
                end = limits.begin;
            }
            return Range(limits.begin, end)
                .Pack();
        }

        inline Range &operator+=(uint16_t v)
        {
            uint16_t end = v + limits.end;
            if (end < limits.end)
            {
                end = upper_limit;
            }
            Resize(limits.begin, end);
            return *this;
        }

        inline Range &operator-=(uint16_t v)
        {
            uint16_t end = limits.end - v;
            if (end < limits.begin || end > limits.end)
            {
                end = limits.begin;
            }
            Resize(limits.begin, end);
            return *this;
        }

        // move
        inline range_pack operator<<(const uint16_t v) const
        {
            uint16_t delta = v;
            if (delta > limits.begin)
            {
                delta = limits.begin;
            }
            return Range(limits.begin - delta,
                         limits.end - delta)
                .Pack();
        }

        inline range_pack operator>>(const uint16_t v) const
        {
            uint16_t delta = v;
            uint16_t end = limits.end + delta;
            if (end < limits.end)
            {
                delta = upper_limit - limits.end;
                end = limits.end + delta;
            }
            return Range(limits.begin + delta, end)
                .Pack();
        }

        inline Range &operator<<=(const uint16_t v)
        {
            uint16_t delta = v;
            if (delta > limits.begin)
            {
                delta = limits.begin;
            }
            Resize(limits.begin - delta, limits.end - delta);
            return *this;
        }

        inline Range &operator>>=(const uint16_t v)
        {
            uint16_t delta = v;
            uint16_t end = limits.end + v;
            if (end < limits.end)
            {
                delta = upper_limit - limits.end;
                end = limits.end + delta;
            }
            Resize(limits.begin + delta, end);
            return *this;
        }

        inline range_pack Resize(uint16_t begin, uint16_t end)
        {
            if (end < begin)
            {
                uint16_t v = end;
                end = begin;
                begin = v;
            }
            limits.begin = begin;
            limits.end = end;
            return pack;
        }

        // implement
        inline uint16_t Map(uint16_t index) { return index; }

        template <typename PUT>
        inline void forward(PUT &put)
        {
            for (uint16_t i = limits.begin; i < limits.end; i++)
            {
                put(i);
            }
        }

        template <typename PUT>
        inline void backward(PUT &put)
        {
            const uint16_t length = Length();
            for (uint16_t i = 1; i <= length; i++)
            {
                put(limits.end - i);
            }
        }

        template <typename PUT>
        inline void spin(PUT &put, bool reverse = false)
        {
            if (reverse)
            {
                backward(put);
            }
            else
            {
                forward(put);
            }
        }

        template <typename PUTTER, typename VALUE>
        inline void Spin(PUTTER &putter, VALUE value, bool reverse = false)
        {
            auto put = [&](uint16_t index)
            {
                putter.Put(index, value);
            };
            spin(put, reverse);
            putter.Update();
        }

        template <typename PUTTER, typename MAPPER, typename VALUE>
        inline void Spin(PUTTER &putter, MAPPER &mapper, VALUE value, bool reverse = false)
        {
            auto put = [&](uint16_t index)
            {
                putter.Put(mapper.Map(index), value);
            };

            spin(put, reverse);
            putter.Update();
        }

        template <typename PUTTER, typename VALUE>
        inline void SpinValues(PUTTER &putter, VALUE value, bool reverse = false)
        {
            auto put = [&](uint16_t index)
            {
                putter.Put(index, value.Map(index));
            };

            spin(put, reverse);
            putter.Update();
        }

        template <typename PUTTER, typename MAPPER, typename VALUE>
        inline void SpinValues(PUTTER &putter, MAPPER &mapper, VALUE value, bool reverse = false)
        {
            auto put = [&](uint16_t index)
            {
                putter.Put(mapper.Map(index), value.Map(index));
            };

            spin(put, reverse);
            putter.Update();
        }
    };
}
