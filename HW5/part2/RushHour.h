#ifndef PART2_RUSHHOUR_H
#define PART2_RUSHHOUR_H


#include "BoardCell.h"
#include "CellType.h"
#include "Conditional.h"
#include "Direction.h"
#include "GameBoard.h"
#include "List.h"
#include "MoveVehicle.h"


//region find car, redCar
template<typename List, CellType carType>
struct FindCarList;

template<CellType CarType>
struct FindCarList<List<>, CarType>
{
    static constexpr bool found = false;
    static constexpr int index = -1;


};

template<typename Item, typename... TT, CellType CarType>
struct FindCarList<List<Item, TT...>,CarType>
{
    static constexpr bool found = ConditionalInteger<
                Item::type == CarType,
                true,
                FindCarList<List<TT...>,CarType>::found
            >::value;

    static constexpr int index = ConditionalInteger<
            Item::type == CarType,
            0,
            1 + FindCarList<List<TT...>,CarType>::index
            >::value;
};


template<typename Lists,CellType CarType>
struct FindCar;

template<CellType CarType>
struct FindCar<List<>,CarType>
{
    static constexpr int row = -1;
    static constexpr int column = -1;
};

template<typename Row, typename...Lists,CellType CarType>
struct FindCar<List<Row, Lists...>,CarType>
{
    static constexpr int row = ConditionalInteger<
                                    FindCarList<Row,CarType>::found,
                                    0,
                                    1 + FindCar<List<Lists...>,CarType>::row
                                >::value;

    static constexpr int column = ConditionalInteger<
                                        FindCarList<Row,CarType>::found,
                                        FindCarList<Row,CarType>::index,
                                        FindCar<List<Lists...>,CarType>::column
                                    >::value;
};


template<typename Lists>
struct FindRedCar
{
    static constexpr int row = FindCar<Lists, X>::row;
    static constexpr int column = FindCar<Lists, X>::column;
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
struct CheckWin;

template<typename... Lists>
struct CheckWin<GameBoard<Lists...>>
{
    static constexpr bool result = IsAllEmpty<Lists...>::isEmpty;
};

//endregion

template<typename Board, typename MovesList>
struct CheckSolution;

template<typename Board>
struct CheckSolution<Board, List<>>
{
    static constexpr bool result = CheckWin<Board>::result;
};

template<typename ListLists, typename MoveItem,typename... Moves>
struct CheckSolution<GameBoard<ListLists>, List<MoveItem, Moves...>>
{
    static constexpr bool result = CheckSolution<
                typename MoveVehicle<GameBoard<ListLists>,
                        FindCar<ListLists, MoveItem::type>::row,
                        FindCar<ListLists, MoveItem::type>::column,
                        MoveItem::direction,
                        MoveItem::amount>::board,
                List<Moves...>>
            ::result;
};




#endif //PART2_RUSHHOUR_H
