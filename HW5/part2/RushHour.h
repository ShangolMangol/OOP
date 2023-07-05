#ifndef PART2_RUSHHOUR_H
#define PART2_RUSHHOUR_H


#include "BoardCell.h"
#include "CellType.h"
#include "Conditional.h"
#include "Direction.h"
#include "GameBoard.h"
#include "List.h"
#include "MoveVehicle.h"
#include "TransposeList.h"


//region find car x
template<typename List>
struct FindRedCarList;

template<>
struct FindRedCarList<List<>>
{
    static constexpr bool found = false;
    static constexpr int index = -1;


};

template<typename Item, typename... TT>
struct FindRedCarList<List<Item, TT...>>
{
    static constexpr bool found = ConditionalInteger<
                Item::type == X,
                true,
                FindRedCarList<List<TT...>>::found
            >::value;

    static constexpr int index = ConditionalInteger<
            Item::type == X,
            0,
            1 + FindRedCarList<List<TT...>>::index
            >::value;
};


template<typename Lists>
struct FindRedCar;

template<>
struct FindRedCar<List<>>
{
    static constexpr int row = -1;
    static constexpr int column = -1;
};

template<typename Row, typename...Lists>
struct FindRedCar<List<Row, Lists...>>
{
    static constexpr int row = ConditionalInteger<
                                    FindRedCarList<Row>::found,
                                    0,
                                    1 + FindRedCar<List<Lists...>>::row
                                >::value;

    static constexpr int column = ConditionalInteger<
                                        FindRedCarList<Row>::found,
                                        FindRedCarList<Row>::index,
                                        FindRedCar<List<Lists...>>::column
                                    >::value;
};



//endregion


//region IsAllEmpty
template<typename Items, int Start, int End>
struct IsAllEmptyList;

template<typename Item, typename... Items, int Start, int End>
struct IsAllEmptyList<List<Item, Items...>, Start, End>
{
    static constexpr bool isEmpty = IsAllEmptyList<List<Items...>, Start-1, End-1>::isEmpty;
};

template<typename Item, typename... Items, int End>
struct IsAllEmptyList<List<Item, Items...>, 0, End>
{
    static constexpr bool isEmpty = ConditionalInteger<
                                        Item::type == EMPTY,
                                        IsAllEmptyList<List<Items...>,0,End - 1>::isEmpty,
                                        false>::value;
};

template<typename Item, typename... Items>
struct IsAllEmptyList<List<Item, Items...>, 0, 0>
{
    static constexpr bool isEmpty = Item::type == EMPTY;
};

template<typename Item, typename... Items, int start>
struct IsAllEmptyList<List<Item, Items...>, start, 0>
{
    static constexpr bool isEmpty = true;
};

//isAllEmpty list of cells, start, end
template<typename Lists>
struct IsAllEmpty;

template<typename... Rows>
struct IsAllEmpty<List<Rows...>>
{
    static constexpr int redCarRow = FindRedCar<List<Rows...>>::row;
    static constexpr int redCarCol = FindRedCar<List<Rows...>>::column;

    static constexpr int redCarLastIndex = FindLastIndex<typename GetAtIndex<redCarRow, List<Rows...>>::value, redCarCol>::index;
    static constexpr int end = List<Rows...>::head::size-1;

    static constexpr bool isEmpty =IsAllEmptyList<typename GetAtIndex<redCarRow, List<Rows...>>::value, redCarLastIndex + 1, end>::isEmpty;
};
//endregion

//region check solution
template<typename Board>
struct CheckSolution;

template<typename... Lists>
struct CheckSolution<GameBoard<Lists...>>
{
    static constexpr bool result = IsAllEmpty<Lists...>::isEmpty;
};

//endregion








#endif //PART2_RUSHHOUR_H
