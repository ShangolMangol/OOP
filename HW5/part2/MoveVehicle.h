#ifndef PART2_MOVEVEHICLE_H
#define PART2_MOVEVEHICLE_H


#include "CellType.h"
#include "Direction.h"
#include "GameBoard.h"
#include "TransposeList.h"

template<CellType Type, Direction Dir, int Amount>
struct Move
{
    static_assert(Type != EMPTY, "bad");
    static constexpr int amount = Amount;
};

/**
 *  FindFirstIndex<Row,Index>::index
 */
//region FindFirstIndex
template<typename Row, int Index>
struct FindFirstIndex;


template<typename... TT, int Index>
struct FindFirstIndex< List<TT...>, Index>
{
    static constexpr bool isStart = GetAtIndex<Index,List<TT...>>::value::type != GetAtIndex<Index-1,List<TT...>>::value::type;
    static constexpr int index = ConditionalInteger<
            (isStart) ,
            Index,
            FindFirstIndex< List<TT...>, Index-1>::index> ::value;
};

template<typename... TT>
struct FindFirstIndex< List<TT...>, 0>
{
    static constexpr int index = 0;
};

//endregion


/**
 * FindFirstIndex<Row, Length, Index>::Index
 */
//region FindLastIndex

template<typename Row, int Length, int Index>
struct FindLastIndexAux;

template<typename... TT, int Length, int Index>
struct FindLastIndexAux< List<TT...>, Length, Index>
{
    static constexpr bool isLast =
            GetAtIndex<Index, List<TT...>>::value::type != GetAtIndex<Index + 1, List<TT...>>::value::type;
    static constexpr int index = ConditionalInteger<
            isLast ,
            Index,
            FindLastIndexAux< List<TT...>, Length, Index+1>::index> ::value;
};

template<typename... TT, int Index>
struct FindLastIndexAux< List<TT...>, Index, Index>
{
    static constexpr int index = Index;
};

template<typename Row, int Index>
struct FindLastIndex;

template<typename... TT, int Index>
struct FindLastIndex< List<TT...>, Index>
{
    static constexpr int index = FindLastIndexAux<List<TT...>, List<TT...>::size -1, Index>::index;
};


//endregion FindLastIndex

/**
 *  MoveStepList<Row, Index, Dir>::list
 */
//region MoveStepList
template<typename Row, int Index, Direction Dir>
struct MoveStepList;

template<typename... Cell, int Index>
struct MoveStepList<List<Cell...>, Index, LEFT>
{
    static_assert(GetAtIndex<Index, List<Cell...>>::value::direction == LEFT
                    ||
                    GetAtIndex<Index, List<Cell...>>::value::direction == RIGHT, "Wrong direction");
    static constexpr int startIndex = FindFirstIndex<List<Cell...>, Index>::index;
    static constexpr int lastIndex = FindLastIndex<List<Cell...>, Index>::index;
    static_assert(startIndex > 0, "move out of board");
    static_assert(GetAtIndex<startIndex - 1, List<Cell...>>::value::type == EMPTY, "Not empty");

    typedef typename SetAtIndex<
                lastIndex,
                BoardCell<EMPTY, UP, 0>,
                typename SetAtIndex<
                    startIndex - 1,
                    typename GetAtIndex<Index, List<Cell...>>::value,
                    List<Cell...>>::list
                >::list list;
};

template<typename... Cell, int Index>
struct MoveStepList<List<Cell...>, Index, RIGHT>
{
    static_assert(GetAtIndex<Index, List<Cell...>>::value::direction == LEFT
                  ||
                  GetAtIndex<Index, List<Cell...>>::value::direction == RIGHT, "Wrong direction");
    static constexpr int startIndex = FindFirstIndex<List<Cell...>, Index>::index;
    static constexpr int lastIndex = FindLastIndex<List<Cell...>, Index>::index;
    static_assert(lastIndex < List<Cell...>::size -1 , "move out of board");
    static_assert(GetAtIndex<lastIndex + 1, List<Cell...>>::value::type == EMPTY, "Not empty");

    typedef typename SetAtIndex<
            startIndex ,
            BoardCell<EMPTY, UP, 0>,
            typename SetAtIndex<
                    lastIndex + 1,
                    typename GetAtIndex<Index, List<Cell...>>::value,
                    List<Cell...>>::list
    >::list list;
};
//endregion

/*
template<typename ...Cell, typename... ListType, int Width, int Height, int RowIndex, int ColumnIndex, int Amount>
struct MoveStep<List<List<Cell...>, ListType...>, Width, Height, >
{

};
*/

//region MoveVehicle
template<typename Board, int RowIndex, int ColumnIndex, Direction Dir, int Amount>
struct MoveVehicle;

template<typename ListType, int Width, int Height, int RowIndex, int ColumnIndex, int Amount>
struct MoveVehicle<GameBoard<ListType, Width, Height>, RowIndex, ColumnIndex, UP, Amount>
{
    typedef GameBoard<
                typename Transpose<
                         typename MoveVehicle<
                                GameBoard<
                                    typename Transpose<ListType>::matrix,
                                    Height,
                                    Width>
                                ,ColumnIndex,
                                RowIndex,
                                LEFT,
                                Amount>::board::board>::matrix,
                Width,
                Height> board;
};


template<typename ListType, int Width, int Height, int RowIndex, int ColumnIndex, int Amount>
struct MoveVehicle<GameBoard<ListType, Width, Height>, RowIndex, ColumnIndex, DOWN, Amount>
{
    typedef GameBoard<
            typename Transpose<
                    typename MoveVehicle<
                            GameBoard<
                                    typename Transpose<ListType>::matrix,
                                    Height,
                                    Width>
                            ,ColumnIndex,
                            RowIndex,
                            RIGHT,
                            Amount>::board::board>::matrix,
            Width,
            Height> board;
};


//endregion MoveVehicle



#endif //PART2_MOVEVEHICLE_H
