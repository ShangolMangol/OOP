#ifndef PART2_BOARDCELL_H
#define PART2_BOARDCELL_H

#include "CellType.h"
#include "Direction.h"

template<CellType Type, Direction Dir, int Length>
struct BoardCell
{
    static constexpr CellType type = Type;
    static constexpr Direction direction = Dir;
    static constexpr int length = Length;
};

#endif //PART2_BOARDCELL_H
