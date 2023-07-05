#ifndef PART2_GAMEBOARD_H
#define PART2_GAMEBOARD_H

#include "List.h"

template<typename ListType>
struct GameBoard;


template<typename... ListType>
struct GameBoard<List<ListType...>>
{
    typedef List<ListType...> board;
    static constexpr int width = List<ListType...>::head::size;
    static constexpr int length = List<ListType...>::size;

};
#endif //PART2_GAMEBOARD_H
