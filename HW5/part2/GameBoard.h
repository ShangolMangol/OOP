#ifndef PART2_GAMEBOARD_H
#define PART2_GAMEBOARD_H

template<typename ListType, int Width, int Height>
struct Board
{
    typedef ListType board;
    static constexpr int width = Width;
    static constexpr int height = Height;
};
#endif //PART2_GAMEBOARD_H
