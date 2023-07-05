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
    static constexpr CellType type = Type;
    static constexpr Direction direction = Dir;
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

template<typename Board, int RowIndex, int ColumnIndex, Direction Dir>
struct MoveStep;

template<typename ...Lists, int RowIndex, int ColumnIndex, Direction Dir>
struct MoveStep<List<Lists...>, RowIndex, ColumnIndex, Dir>
{
    typedef typename SetAtIndex<
                RowIndex,
                typename MoveStepList<
                    typename GetAtIndex<RowIndex,List<Lists...>>::value
                    ,ColumnIndex,
                    Dir>::list,
                List<Lists...>>::list list;
};

//region MoveVehicleNoCheck

template<typename Board, int RowIndex, int ColumnIndex, Direction Dir, int Amount>
struct MoveVehicleNoCheck;


template<typename ListType, int RowIndex, int ColumnIndex, Direction Dir, int Amount>
struct MoveVehicleNoCheck<GameBoard<ListType>, RowIndex, ColumnIndex, Dir, Amount>
{
    static_assert(GameBoard<ListType>::width > ColumnIndex, "column index too large");
    static_assert(ColumnIndex >= 0, "column index too small");
    static_assert(GameBoard<ListType>::height > RowIndex, "row index too large");
    static_assert(RowIndex >= 0, "row index is less than 0");
    static_assert(Amount > 0, "Amount less than 0");


    typedef typename MoveVehicleNoCheck<
                    GameBoard<
                        typename MoveStep<ListType, RowIndex, ColumnIndex, Dir>::list>,
                    RowIndex,
                    ConditionalInteger<Dir == RIGHT,ColumnIndex+1, ColumnIndex-1>::value,
                    Dir,
                    Amount - 1>::board board;
};

template<typename ListType, int RowIndex, int ColumnIndex>
struct MoveVehicleNoCheck<GameBoard<ListType>, RowIndex, ColumnIndex, LEFT, 1>
{
    static_assert(GameBoard<ListType>::width > ColumnIndex, "column index too large");
    static_assert(ColumnIndex >= 0, "column index too small");
    static_assert(GameBoard<ListType>::height > RowIndex, "row index too large");
    static_assert(RowIndex >= 0, "row index is less than 0");

    typedef GameBoard<typename MoveStep<ListType, RowIndex, ColumnIndex, LEFT>::list> board;
};

template<typename ListType, int RowIndex, int ColumnIndex>
struct MoveVehicleNoCheck<GameBoard<ListType>, RowIndex, ColumnIndex, RIGHT, 1>
{
    static_assert(GameBoard<ListType>::width > ColumnIndex, "column index too large");
    static_assert(ColumnIndex >= 0, "column index too small");
    static_assert(GameBoard<ListType>::height > RowIndex, "row index too large");
    static_assert(RowIndex >= 0, "row index is less than 0");

    typedef GameBoard<typename MoveStep<ListType, RowIndex, ColumnIndex, RIGHT>::list> board;
};
//endregion MoveVehicleNoCheck

//region MoveVehicle
template<typename Board, int RowIndex, int ColumnIndex, Direction Dir, int Amount>
struct MoveVehicle;

template<typename ListType, int RowIndex, int ColumnIndex, Direction Dir, int Amount>
struct MoveVehicle<GameBoard<ListType>, RowIndex, ColumnIndex, Dir, Amount>
{
    static_assert(GetAtIndex< ColumnIndex, typename GetAtIndex<RowIndex, ListType>::value>::value::type != EMPTY, "Can't move empty cell");
    static constexpr Direction directionOfCar = GetAtIndex< ColumnIndex, typename GetAtIndex<RowIndex, ListType>::value>::value::direction;
    static_assert(directionOfCar == LEFT
                  ||
                  directionOfCar == RIGHT, "Wrong direction");

    typedef typename MoveVehicleNoCheck<GameBoard<ListType>, RowIndex, ColumnIndex, Dir,Amount>::board board;
};

template<typename ListType, int RowIndex, int ColumnIndex>
struct MoveVehicle<GameBoard<ListType>, RowIndex, ColumnIndex, LEFT, 1>
{
    static_assert(GetAtIndex< ColumnIndex, typename GetAtIndex<RowIndex, ListType>::value>::value::type != EMPTY, "Can't move empty cell");
    static constexpr Direction directionOfCar = GetAtIndex< ColumnIndex, typename GetAtIndex<RowIndex, ListType>::value>::value::direction;
    static_assert(directionOfCar == LEFT
                  ||
                  directionOfCar == RIGHT, "Wrong direction");

    typedef typename MoveVehicleNoCheck<GameBoard<ListType>, RowIndex, ColumnIndex, LEFT,1>::board board;
};

template<typename ListType, int RowIndex, int ColumnIndex>
struct MoveVehicle<GameBoard<ListType>, RowIndex, ColumnIndex, RIGHT, 1>
{
    static_assert(GetAtIndex< ColumnIndex, typename GetAtIndex<RowIndex, ListType>::value>::value::type != EMPTY, "Can't move empty cell");
    static constexpr Direction directionOfCar = GetAtIndex< ColumnIndex, typename GetAtIndex<RowIndex, ListType>::value>::value::direction;
    static_assert(directionOfCar == LEFT
                  ||
                  directionOfCar == RIGHT, "Wrong direction");

    typedef typename MoveVehicleNoCheck<GameBoard<ListType>, RowIndex, ColumnIndex, RIGHT, 1>::board board;
};




template<typename ListType, int RowIndex, int ColumnIndex, int Amount>
struct MoveVehicle<GameBoard<ListType>, RowIndex, ColumnIndex, UP, Amount>
{
    static_assert(GetAtIndex< ColumnIndex, typename GetAtIndex<RowIndex, ListType>::value>::value::type != EMPTY, "Can't move empty cell");
    static constexpr Direction directionOfCar = GetAtIndex< ColumnIndex, typename GetAtIndex<RowIndex, ListType>::value>::value::direction;
    static_assert(directionOfCar == UP
                  ||
                  directionOfCar == DOWN, "Wrong direction");

    typedef GameBoard<
                typename Transpose<
                         typename MoveVehicleNoCheck<
                                GameBoard<typename Transpose<ListType>::matrix>,
                                ColumnIndex,
                                RowIndex,
                                LEFT,
                                Amount>::board::board>::matrix> board;
};


template<typename ListType, int RowIndex, int ColumnIndex, int Amount>
struct MoveVehicle<GameBoard<ListType>, RowIndex, ColumnIndex, DOWN, Amount>
{
    static_assert(GetAtIndex< ColumnIndex, typename GetAtIndex<RowIndex, ListType>::value>::value::type != EMPTY, "Can't move empty cell");

    static constexpr Direction directionOfCar = GetAtIndex< ColumnIndex, typename GetAtIndex<RowIndex, ListType>::value>::value::direction;
    static_assert(directionOfCar == UP
                  ||
                  directionOfCar == DOWN, "Wrong direction");
    typedef GameBoard<
            typename Transpose<
                    typename MoveVehicleNoCheck<
                            GameBoard<
                                    typename Transpose<ListType>::matrix>
                            ,ColumnIndex,
                            RowIndex,
                            RIGHT,
                            Amount>::board::board>::matrix> board;
};


//endregion MoveVehicle



#endif //PART2_MOVEVEHICLE_H
