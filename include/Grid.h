// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Range.h"
#include "Math.h"
#include "Point.h"

namespace glow
{
    enum : uint8_t
    {
        GRID_ZIGZAG = 1,
        GRID_ROWS = 2,
        GRID_COLUMNS = 4,
        GRID_ZIGZAG_ROWS = GRID_ZIGZAG | GRID_ROWS,
        GRID_ZIGZAG_COLUMNS = GRID_ZIGZAG | GRID_COLUMNS,
    };

    class Grid : public Range
    {
    protected:
        uint8_t arrangement;
        uint16_t columns;
        uint16_t rows;

    public:
        Grid(range_pack range,
             uint16_t columns = 0,
             uint8_t arrangement = GRID_ROWS)
            : arrangement(arrangement), columns(columns)
        {
            Resize(range, columns);
        }

        // access
        inline uint8_t Arrangment() const { return arrangement; }
        inline uint16_t Rows() const { return rows; }
        inline uint16_t Columns() const { return columns; }

        // modify
        inline uint8_t Rearrange(uint8_t v) { return arrangement = v; }

        inline range_pack Resize(range_pack range, uint16_t colLength)
        {
            Pack(range);
            columns = (colLength == 0) ? Length() : colLength;
            rows = Length() / columns;
            return Pack();
        }

        // implement
        inline uint16_t Map(uint16_t index)
        {
            index -= Begin();
            if (arrangement == GRID_ROWS)
            {
                return Begin() + index;
            }

            if (arrangement & GRID_COLUMNS)
            {
                Point point = DivMod(index, rows);

                if (arrangement == GRID_ZIGZAG_COLUMNS &&
                    (point.y & 1)) // odd row
                {
                    return Begin() +
                           point.y * columns +
                           columns - (point.x + 1);
                }
                return Begin() + point.y * columns + point.x;
            }

            // arrangement == GRID_ZIGZAG_COLUMNS
            Point point = DivMod(index, columns);
            if (point.x & 1) // odd row
            {
                return Begin() +
                       point.x * columns +
                       columns - (point.y + 1);
            }
            return Begin() + index;
        }
    };
} // namespace glow
