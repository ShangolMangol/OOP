#include <iostream>
#include <cassert>

#include "List.h"
#include "Conditional.h"
#include "BoardCell.h"
#include "MoveVehicle.h"
#include "RushHour.h"


template<int T>
struct Int
{

};


int main()
{
    typedef List<Int<1>,Int<1>,Int<2>,Int<2>,Int<1>,Int<1>> listSame;
    typedef List<Int<1>,Int<2>,Int<3>,Int<4>,Int<5>,Int<6>> list6;
    typedef List<Int<1>> list1;
    typedef List<> list0;

    static_assert(listSame::size == 6, "");
    static_assert(listSame::next::size == 5, "");
    assert(typeid(listSame::next::head) == typeid(Int<1>));
    assert(typeid(listSame::next::next::head) == typeid(Int<2>));
    assert(typeid(listSame::next::next::next::next::head) == typeid(Int<1>));
    assert(typeid(listSame::next::next::next::next::next::head) == typeid(Int<1>));
    assert(listSame::next::next::next::next::next::next::size == 0);




    static_assert(list6::size == 6, "");
    static_assert(list6::next::size == 5, "");
    assert(typeid(list6::next::head) == typeid(Int<2>));

    static_assert(list1::size == 1, "size 1 failed");
    static_assert(list1::next::size == 0, "");

    static_assert(list0::size == 0, "size 0 failed");

    typedef PrependList<Int<7>, list6>::list list7;
    static_assert(list7::size == 7, "size 7 failed");
    assert(typeid(list7::head) == typeid(Int<7>));
    assert(typeid(list7::next) == typeid(list6));

    assert(typeid(GetAtIndex<0, list7>::value) == typeid(Int<7>));
    assert(typeid(GetAtIndex<1, list7>::value) == typeid(Int<1>));
    assert(typeid(GetAtIndex<2, list7>::value) == typeid(Int<2>));
    assert(typeid(GetAtIndex<3, list7>::value) == typeid(Int<3>));
    assert(typeid(GetAtIndex<4, list7>::value) == typeid(Int<4>));
    assert(typeid(GetAtIndex<5, list7>::value) == typeid(Int<5>));
    assert(typeid(GetAtIndex<6, list7>::value) == typeid(Int<6>));

    assert(typeid(SetAtIndex<0, Int<99>, list7>::list) == typeid(List<Int<99>,Int<1>,Int<2>,Int<3>,Int<4>,Int<5>,Int<6>>));
    assert(typeid(SetAtIndex<1, Int<99>, list7>::list) == typeid(List<Int<7>,Int<99>,Int<2>,Int<3>,Int<4>,Int<5>,Int<6>>));
    assert(typeid(SetAtIndex<2, Int<99>, list7>::list) == typeid(List<Int<7>,Int<1>,Int<99>,Int<3>,Int<4>,Int<5>,Int<6>>));
    assert(typeid(SetAtIndex<3, Int<99>, list7>::list) == typeid(List<Int<7>,Int<1>,Int<2>,Int<99>,Int<4>,Int<5>,Int<6>>));
    assert(typeid(SetAtIndex<4, Int<99>, list7>::list) == typeid(List<Int<7>,Int<1>,Int<2>,Int<3>,Int<99>,Int<5>,Int<6>>));
    assert(typeid(SetAtIndex<5, Int<99>, list7>::list) == typeid(List<Int<7>,Int<1>,Int<2>,Int<3>,Int<4>,Int<99>,Int<6>>));
    assert(typeid(SetAtIndex<6, Int<99>, list7>::list) == typeid(List<Int<7>,Int<1>,Int<2>,Int<3>,Int<4>,Int<5>,Int<99>>));



    typedef typename Conditional<(0 != 1), Int<0>, Int<1>>::value test1; // = Int<0>
    typedef typename Conditional<(0 == 1), Int<0>, Int<1>>::value test2; // = Int<1>
    assert(typeid(test1) == typeid(Int<0>));
    assert(typeid(test2) == typeid(Int<1>));

    static_assert(ConditionalInteger<(0 != 1), 0, 1>::value == 0, "value of conditional is not false");
    static_assert(ConditionalInteger<(0 == 1), 0, 1>::value == 1, "value of ConditinalInteger isn't 1 ");

    static_assert(Move<X, RIGHT, 1>::amount == 1, "as");

    static_assert(FindFirstIndex<
            List<BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>,BoardCell<E, UP, 3>>,
            0 >::index == 0, "wrong index");
    static_assert(FindFirstIndex<
            List<BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>,BoardCell<E, UP, 3>>,
            1 >::index == 0, "wrong index");
    static_assert(FindFirstIndex<
            List<BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>,BoardCell<E, UP, 3>>,
            2 >::index == 0, "wrong index");


    static_assert(FindLastIndex<
            List<BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>,BoardCell<E, UP, 3>>,
            0 >::index == 2, "wrong index");
    static_assert(FindLastIndex<
            List<BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>,BoardCell<E, UP,3>>,
            1 >::index == 2, "wrong index");
    static_assert(FindLastIndex<
            List<BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>,BoardCell<E, UP, 3>>,
            2 >::index == 2, "wrong index");


    static_assert(FindFirstIndex<
            List<BoardCell<E, UP, 3>, BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>>,
            1 >::index == 1, "wrong index");
    static_assert(FindFirstIndex<
            List<BoardCell<E, UP, 3>, BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>>,
            2 >::index == 1, "wrong index");
    static_assert(FindFirstIndex<
            List<BoardCell<E, UP, 3>, BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>>,
            3 >::index == 1, "wrong index");


    static_assert(FindLastIndex<
            List<BoardCell<E, UP, 3>, BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>>,
            1 >::index == 3, "wrong index");
    static_assert(FindLastIndex<
            List<BoardCell<E, UP, 3>, BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>>,
            2 >::index == 3, "wrong index");
    static_assert(FindLastIndex<
            List<BoardCell<E, UP, 3>, BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>>,
            3 >::index == 3, "wrong index");

    static_assert(FindFirstIndex<
            List<BoardCell<E, DOWN, 3>, BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>>,
            0>::index == 0, "wrong index");
    static_assert(FindFirstIndex<
            List<BoardCell<E, DOWN, 3>, BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>>,
            1>::index == 1, "wrong index");
    static_assert(FindFirstIndex<
            List<BoardCell<E, DOWN, 3>, BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>>,
            2>::index == 1, "wrong index");
    static_assert(FindFirstIndex<
            List<BoardCell<E, DOWN, 3>, BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>>,
            3>::index == 1, "wrong index");


    static_assert(FindLastIndex<
            List<BoardCell<E, DOWN, 3>, BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>>,
            0 >::index == 0, "wrong index");
    static_assert(FindLastIndex<
            List<BoardCell<E, DOWN, 3>, BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>>,
            1 >::index == 3, "wrong index");
    static_assert(FindLastIndex<
            List<BoardCell<E, DOWN, 3>, BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>>,
            2 >::index == 3, "wrong index");
    static_assert(FindLastIndex<
            List<BoardCell<E, DOWN, 3>, BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>>,
            3 >::index == 3, "wrong index");


    assert(typeid(MoveStepList<List<BoardCell<EMPTY, UP, 0>,BoardCell<X, LEFT, 2>,BoardCell<X, LEFT, 2>,BoardCell<E, UP, 3>>
            , 1, LEFT >::list) ==
        typeid(List<BoardCell<X, LEFT, 2>,BoardCell<X, LEFT, 2>,BoardCell<EMPTY, UP, 0>,BoardCell<E, UP, 3>>));

    assert(typeid(MoveStepList<List<BoardCell<EMPTY, UP, 0>,BoardCell<X, LEFT, 2>,BoardCell<X, LEFT, 2>,BoardCell<E, UP, 3>>
            , 2, LEFT >::list) ==
           typeid(List<BoardCell<X, LEFT, 2>,BoardCell<X, LEFT, 2>,BoardCell<EMPTY, UP, 0>,BoardCell<E, UP, 3>>));

    assert(typeid(MoveStepList<List<BoardCell<EMPTY, UP, 0>,BoardCell<X, LEFT, 2>,BoardCell<X, LEFT, 2>, BoardCell<EMPTY, UP, 0>>
            , 1, RIGHT >::list) ==
           typeid(List<BoardCell<EMPTY, UP, 0>,BoardCell<EMPTY, UP, 0>,BoardCell<X, LEFT, 2>,BoardCell<X, LEFT, 2>>));

    assert(typeid(MoveStepList<List<BoardCell<EMPTY, UP, 0>,BoardCell<X, LEFT, 2>,BoardCell<X, LEFT, 2>, BoardCell<EMPTY, UP, 0>>
            , 2, RIGHT >::list) ==
           typeid(List<BoardCell<EMPTY, UP, 0>,BoardCell<EMPTY, UP, 0>,BoardCell<X, LEFT, 2>,BoardCell<X, LEFT, 2>>));






    assert(typeid(MoveStepList<
            List<BoardCell<E, DOWN, 3>, BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>,BoardCell<EMPTY, LEFT, 3>>,
            1, RIGHT>::list)
            ==
            typeid(List<BoardCell<E, DOWN, 3>, BoardCell<EMPTY, UP, 0>,BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>>));

    assert(typeid(MoveStepList<
            List<BoardCell<E, DOWN, 3>, BoardCell<X, RIGHT, 3>,BoardCell<X, RIGHT, 3>,BoardCell<EMPTY, RIGHT, 3>>,
            2, RIGHT>::list)
           ==
           typeid(List<BoardCell<E, DOWN, 3>, BoardCell<EMPTY, UP, 0>,BoardCell<X, RIGHT, 3>,BoardCell<X, RIGHT, 3>>));

    assert(typeid(MoveStepList<
            List<BoardCell<E, DOWN, 3>, BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>,BoardCell<EMPTY, LEFT, 3>>,
            1, RIGHT>::list)
           ==
           typeid(List<BoardCell<E, DOWN, 3>, BoardCell<EMPTY, UP, 0>,BoardCell<X, LEFT, 3>,BoardCell<X, LEFT, 3>>));

    assert(typeid(MoveStepList<
            List<BoardCell<E, DOWN, 3>, BoardCell<EMPTY, UP, 0>,BoardCell<X, RIGHT, 3>,BoardCell<X, RIGHT, 3>>,
            2, LEFT>::list)
           ==
           typeid(List<BoardCell<E, DOWN, 3>, BoardCell<X, RIGHT, 3>,BoardCell<X, RIGHT, 3>,BoardCell<EMPTY, UP, 0>>));



    typedef GameBoard< List<
            List< BoardCell<EMPTY,RIGHT,1>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<  O  ,DOWN ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,2>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<  A  ,RIGHT,2>,  BoardCell<  A  ,LEFT ,2>,  BoardCell<  O  ,DOWN ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,3>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<  X  ,RIGHT,2>,  BoardCell<  X  ,LEFT ,2>,  BoardCell<  O  ,UP   ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<  B  ,DOWN ,2>,  BoardCell<  P  ,RIGHT,3>,  BoardCell<  P  ,RIGHT,3>, BoardCell<  P  ,LEFT  ,3> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<  B  ,UP   ,2>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<  C  ,RIGHT,2>, BoardCell<  C  ,LEFT  ,2> >
    >> gameBoard;

    typedef GameBoard< List<
            List< BoardCell<EMPTY,RIGHT,1>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<  O  ,DOWN ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,2>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<  A  ,RIGHT,2>,  BoardCell<  A  ,LEFT ,2>,  BoardCell<  O  ,DOWN ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,3>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<  X  ,RIGHT,2>,  BoardCell<  X  ,LEFT ,2>,  BoardCell<  O  ,UP   ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<  B  ,DOWN ,2 >,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<  B  ,DOWN ,2>,  BoardCell<  P  ,RIGHT,3>,  BoardCell<  P  ,RIGHT,3>, BoardCell<  P  ,LEFT  ,3> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell< EMPTY,UP,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<  C  ,RIGHT,2>, BoardCell<  C  ,LEFT  ,2> >
    >> gameBoardBUp;

    assert(typeid(typename MoveVehicle<gameBoard, 4, 2, UP, 1>::board) == typeid(gameBoardBUp));


    typedef GameBoard< List<
            List< BoardCell<EMPTY,RIGHT,1>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0> >,
            List< BoardCell<EMPTY,RIGHT,2>,  BoardCell<  B  ,UP   ,2>,  BoardCell<  A  ,RIGHT,2>,  BoardCell<  A  ,LEFT ,2> >,
            List< BoardCell<EMPTY,RIGHT,3>,  BoardCell<  B  ,UP   ,2>,  BoardCell<  X  ,RIGHT,2>,  BoardCell<  X  ,LEFT ,2> >
    >> smallGameBoard;

    typedef GameBoard< List<
            List< BoardCell<EMPTY,RIGHT,1>,  BoardCell<  B  ,UP   ,2>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0> >,
            List< BoardCell<EMPTY,RIGHT,2>,  BoardCell<  B  ,UP   ,2>,  BoardCell<  A  ,RIGHT,2>,  BoardCell<  A  ,LEFT ,2> >,
            List< BoardCell<EMPTY,RIGHT,3>,  BoardCell<EMPTY,UP   ,0>,  BoardCell<  X  ,RIGHT,2>,  BoardCell<  X  ,LEFT ,2> >
    >> smallGameBoardBUp;

    assert(typeid(typename MoveVehicle<smallGameBoard, 2, 1, UP, 1>::board) == typeid(smallGameBoardBUp));


    typedef GameBoard< List<
            List< BoardCell<EMPTY,RIGHT,1>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<  O  ,DOWN ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,2>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<  A  ,RIGHT,2>,  BoardCell<  A  ,LEFT ,2>,  BoardCell<  O  ,DOWN ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<  X  ,RIGHT,2>,  BoardCell<  X  ,RIGHT,2>,  BoardCell<EMPTY,UP   ,0>,  BoardCell<EMPTY,UP   ,0>,  BoardCell<  O  ,UP   ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<  B  ,DOWN ,2>,  BoardCell<  P  ,RIGHT,3>,  BoardCell<  P  ,RIGHT,3>, BoardCell<  P  ,LEFT  ,3> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<  B  ,UP   ,2>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<  C  ,RIGHT,2>, BoardCell<  C  ,LEFT  ,2> >
    >> gameBoardXLeft;

    assert(typeid(typename MoveVehicle<gameBoard, 2, 2, LEFT, 2>::board) == typeid(gameBoardXLeft));



    typedef GameBoard< List<
            List< BoardCell<EMPTY,RIGHT,1>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<  O  ,DOWN ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,2>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<  A  ,RIGHT,2>,  BoardCell<  A  ,LEFT ,2>,  BoardCell<  O  ,DOWN ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,3>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<  X  ,RIGHT,2>,  BoardCell<  X  ,LEFT ,2>,  BoardCell<  O  ,UP   ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<  D  ,DOWN ,2>,  BoardCell<  B  ,DOWN ,2>,  BoardCell<  P  ,RIGHT,3>,  BoardCell<  P  ,RIGHT,3>, BoardCell<  P  ,LEFT  ,3> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<  D  ,DOWN ,2>,  BoardCell<  B  ,UP   ,2>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<  C  ,RIGHT,2>, BoardCell<  C  ,LEFT  ,2> >
    >> gameBoardMoveUp;

    typedef GameBoard< List<
            List< BoardCell<EMPTY,RIGHT,1>,  BoardCell<  D  ,DOWN ,2>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<  O  ,DOWN ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,2>,  BoardCell<  D  ,DOWN ,2>,  BoardCell<  A  ,RIGHT,2>,  BoardCell<  A  ,LEFT ,2>,  BoardCell<  O  ,DOWN ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,3>,  BoardCell<EMPTY,UP,0>,  BoardCell<  X  ,RIGHT,2>,  BoardCell<  X  ,LEFT ,2>,  BoardCell<  O  ,UP   ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,UP,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,UP,0>,  BoardCell<  B  ,DOWN ,2>,  BoardCell<  P  ,RIGHT,3>,  BoardCell<  P  ,RIGHT,3>, BoardCell<  P  ,LEFT  ,3> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,UP,0>,  BoardCell<  B  ,UP   ,2>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<  C  ,RIGHT,2>, BoardCell<  C  ,LEFT  ,2> >
    >> gameBoardMoveUpAfter;

    assert(typeid(MoveVehicle<gameBoardMoveUp, 5,1, UP, 4>::board) == typeid(gameBoardMoveUpAfter));


    typedef GameBoard< List<
            List< BoardCell<EMPTY,RIGHT,1>,  BoardCell<  D  ,DOWN ,2>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<  O  ,DOWN ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,2>,  BoardCell<  D  ,DOWN ,2>,  BoardCell<  A  ,RIGHT,2>,  BoardCell<  A  ,LEFT ,2>,  BoardCell<  O  ,DOWN ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,3>,  BoardCell<EMPTY,UP,0>,  BoardCell<  X  ,RIGHT,2>,  BoardCell<  X  ,LEFT ,2>,  BoardCell<  O  ,UP   ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<  C  ,DOWN ,2>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<  C  ,DOWN ,2>,  BoardCell<  B  ,DOWN ,2>,  BoardCell<  P  ,RIGHT,3>,  BoardCell<  P  ,RIGHT,3>, BoardCell<  P  ,LEFT  ,3> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,UP,0>,  BoardCell<  B  ,UP   ,2>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<  C  ,RIGHT,2>, BoardCell<  C  ,LEFT  ,2> >
    >> gameBoardCarCrash;

    typedef GameBoard< List<
            List< BoardCell<EMPTY,RIGHT,1>,  BoardCell<EMPTY  ,UP ,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<  O  ,DOWN ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,2>,  BoardCell<  D  ,DOWN ,2>,  BoardCell<  A  ,RIGHT,2>,  BoardCell<  A  ,LEFT ,2>,  BoardCell<  O  ,DOWN ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,3>,  BoardCell<  D  ,DOWN ,2>,  BoardCell<  X  ,RIGHT,2>,  BoardCell<  X  ,LEFT ,2>,  BoardCell<  O  ,UP   ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<  C  ,DOWN ,2>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<  C  ,DOWN ,2>,  BoardCell<  B  ,DOWN ,2>,  BoardCell<  P  ,RIGHT,3>,  BoardCell<  P  ,RIGHT,3>, BoardCell<  P  ,LEFT  ,3> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,UP,0>,  BoardCell<  B  ,UP   ,2>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<  C  ,RIGHT,2>, BoardCell<  C  ,LEFT  ,2> >
    >> gameBoardCarCrashNOT;

    assert(typeid(MoveVehicle<gameBoardCarCrash, 0,1, DOWN, 1>::board) == typeid(gameBoardCarCrashNOT));
//        assert(typeid(MoveVehicle<gameBoardCarCrash, 0,0, LEFT, 1>::board) == typeid(gameBoardCarCrashNOT));
//        assert(typeid(MoveVehicle<gameBoardCarCrash, 0,1, DOWN, 2>::board) == typeid(gameBoardCarCrashNOT));
//        assert(typeid(MoveVehicle<gameBoardCarCrash, 3,1, UP, 2>::board) == typeid(gameBoardCarCrashNOT));


    typedef List<
            List< BoardCell<EMPTY,RIGHT,1>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,DOWN ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,2>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,RIGHT,2>,  BoardCell<EMPTY,LEFT ,2>,  BoardCell<EMPTY,DOWN ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,3>,  BoardCell<EMPTY,UP   ,0>,  BoardCell<EMPTY,RIGHT,2>,  BoardCell<EMPTY,LEFT ,2>,  BoardCell<EMPTY,UP   ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<  X  ,RIGHT,2>,  BoardCell<  X  ,RIGHT,2>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,RIGHT,3>,  BoardCell<EMPTY,RIGHT,3>, BoardCell<EMPTY,LEFT  ,3> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,UP   ,0>,  BoardCell<EMPTY,UP   ,2>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,2>, BoardCell<EMPTY,LEFT  ,2> >
    > board_x_3_0;

    typedef  List<
            List< BoardCell<  X  ,RIGHT,2>,  BoardCell<  X  ,RIGHT,2>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,DOWN ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,2>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,RIGHT,2>,  BoardCell<EMPTY,LEFT ,2>,  BoardCell<EMPTY,DOWN ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,3>,  BoardCell<EMPTY,UP   ,0>,  BoardCell<EMPTY,RIGHT,2>,  BoardCell<EMPTY,LEFT ,2>,  BoardCell<EMPTY,UP   ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,RIGHT,3>,  BoardCell<EMPTY,RIGHT,3>, BoardCell<EMPTY,LEFT  ,3> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,UP   ,0>,  BoardCell<EMPTY,UP   ,2>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,2>, BoardCell<EMPTY,LEFT  ,2> >
    > board_x_0_0;


    typedef  List<
            List< BoardCell<EMPTY,RIGHT,1>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,DOWN ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,2>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,RIGHT,2>,  BoardCell<EMPTY,LEFT ,2>,  BoardCell<EMPTY,DOWN ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,3>,  BoardCell<EMPTY,UP   ,0>,  BoardCell<EMPTY,RIGHT,2>,  BoardCell<EMPTY,LEFT ,2>,  BoardCell<EMPTY,UP   ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,RIGHT,3>,  BoardCell<EMPTY,RIGHT,3>, BoardCell<EMPTY,LEFT  ,3> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,UP   ,0>,  BoardCell<EMPTY,UP   ,2>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<  X  ,RIGHT,2>, BoardCell<  X  ,RIGHT,2> >
    > board_x_5_4;


    typedef List<
            List< BoardCell<EMPTY,RIGHT,1>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<  X  ,RIGHT,2>, BoardCell<  X  ,RIGHT,2> >,
            List< BoardCell<EMPTY,RIGHT,2>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,RIGHT,2>,  BoardCell<EMPTY,LEFT ,2>,  BoardCell<EMPTY,DOWN ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,3>,  BoardCell<EMPTY,UP   ,0>,  BoardCell<EMPTY,RIGHT,2>,  BoardCell<EMPTY,LEFT ,2>,  BoardCell<EMPTY,UP   ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,RIGHT,3>,  BoardCell<EMPTY,RIGHT,3>, BoardCell<EMPTY,LEFT  ,3> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,UP   ,0>,  BoardCell<EMPTY,UP   ,2>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,2>, BoardCell<EMPTY,LEFT  ,2> >
    > board_x_0_4;

    typedef List<
            List< BoardCell<EMPTY,RIGHT,1>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT ,0>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,2>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,RIGHT,2>,  BoardCell<EMPTY,LEFT ,2>,  BoardCell<EMPTY,DOWN ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,3>,  BoardCell<EMPTY,UP   ,0>,  BoardCell<EMPTY,RIGHT,2>,  BoardCell<EMPTY,LEFT ,2>,  BoardCell<EMPTY,UP   ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,RIGHT,3>,  BoardCell<EMPTY,RIGHT,3>, BoardCell<EMPTY,LEFT  ,3> >,
            List< BoardCell<  X  ,RIGHT,2>,  BoardCell<  X  ,RIGHT,2>,  BoardCell<EMPTY,UP   ,2>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,2>, BoardCell<EMPTY,LEFT  ,2> >
    > board_x_5_0;

    static_assert(FindRedCar<board_x_0_0>::row == 0, "x 0 0 ");
    static_assert(FindRedCar<board_x_0_0>::column == 0, "x 0 0 ");
    static_assert(FindRedCar<board_x_0_4>::row == 0, "x 0 4 ");
    static_assert(FindRedCar<board_x_0_4>::column == 4, "x 0 4 ");
    static_assert(FindRedCar<board_x_3_0>::row == 3, "x 3 0 ");
    static_assert(FindRedCar<board_x_3_0>::column == 0, "x 3 0 ");
    static_assert(FindRedCar<board_x_5_4>::row == 5, "x 5 4 ");
    static_assert(FindRedCar<board_x_5_4>::column == 4, "x 5 4 ");
    static_assert(FindRedCar<board_x_5_0>::row == 5, "x 5 0 ");
    static_assert(FindRedCar<board_x_5_0>::column == 0, "x 5 0 ");


    static_assert(FindCar<board_x_0_0, X>::row == 0, "x 0 0 ");
    static_assert(FindCar<board_x_0_0, X>::column == 0, "x 0 0 ");
    static_assert(FindCar<board_x_0_4, X>::row == 0, "x 0 4 ");
    static_assert(FindCar<board_x_0_4, X>::column == 4, "x 0 4 ");
    static_assert(FindCar<board_x_3_0, X>::row == 3, "x 3 0 ");
    static_assert(FindCar<board_x_3_0, X>::column == 0, "x 3 0 ");
    static_assert(FindCar<board_x_5_4, X>::row == 5, "x 5 4 ");
    static_assert(FindCar<board_x_5_4, X>::column == 4, "x 5 4 ");
    static_assert(FindCar<board_x_5_0, X>::row == 5, "x 5 0 ");
    static_assert(FindCar<board_x_5_0, X>::column == 0, "x 5 0 ");


    typedef  List<
            List< BoardCell<  X  ,RIGHT,2>,  BoardCell<  X  ,RIGHT,2>,  BoardCell<EMPTY,RIGHT,0> >,
            List< BoardCell<EMPTY,RIGHT,2>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,RIGHT,2> >
    > small_board_x_0_0;

    typedef List<
            List< BoardCell<EMPTY,RIGHT,1>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT ,0>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,2>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,RIGHT,2>,  BoardCell<EMPTY,LEFT ,2>,  BoardCell<EMPTY,DOWN ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,3>,  BoardCell<EMPTY,UP   ,0>,  BoardCell<EMPTY,RIGHT,2>,  BoardCell<EMPTY,LEFT ,2>,  BoardCell<EMPTY,UP   ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,RIGHT,3>,  BoardCell<EMPTY,RIGHT,3>, BoardCell<EMPTY,LEFT  ,3> >,
            List< BoardCell<  X  ,RIGHT,2>,  BoardCell<  X  ,RIGHT,2>,  BoardCell<  A  ,RIGHT,2>,  BoardCell<  A  ,LEFT ,2>,  BoardCell<EMPTY,RIGHT,2>, BoardCell<EMPTY,LEFT  ,2> >
    > board_red_block_near;

    typedef List<
            List< BoardCell<EMPTY,RIGHT,1>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT ,0>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,2>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,RIGHT,2>,  BoardCell<EMPTY,LEFT ,2>,  BoardCell<EMPTY,DOWN ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,3>,  BoardCell<EMPTY,UP   ,0>,  BoardCell<EMPTY,RIGHT,2>,  BoardCell<EMPTY,LEFT ,2>,  BoardCell<EMPTY,UP   ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,RIGHT,3>,  BoardCell<EMPTY,RIGHT,3>, BoardCell<EMPTY,LEFT  ,3> >,
            List< BoardCell<  X  ,RIGHT,2>,  BoardCell<  X  ,RIGHT,2>,  BoardCell<EMPTY,UP   ,2>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<  A  ,RIGHT,2>,  BoardCell<  A  ,LEFT ,2> >
    > board_red_block_far;


    typedef List<
            List< BoardCell<EMPTY,RIGHT,1>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT ,0>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,2>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,RIGHT,2>,  BoardCell<EMPTY,LEFT ,2>,  BoardCell<EMPTY,DOWN ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,3>,  BoardCell<EMPTY,UP   ,0>,  BoardCell<EMPTY,RIGHT,2>,  BoardCell<EMPTY,LEFT ,2>,  BoardCell<EMPTY,UP   ,3>, BoardCell<EMPTY,RIGHT ,0> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,RIGHT,0>, BoardCell<  A  ,UP    ,3> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,RIGHT,3>,  BoardCell<EMPTY,RIGHT,3>, BoardCell<  A  ,UP    ,3> >,
            List< BoardCell<EMPTY,RIGHT,0>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<EMPTY,DOWN ,2>,  BoardCell<  X  ,RIGHT,2>,  BoardCell<  X  ,RIGHT,2>, BoardCell<  A  ,UP    ,3> >
    > board_red_block_exit;

    static_assert(CheckWin<GameBoard<small_board_x_0_0>>::result, "");
    static_assert(CheckWin<GameBoard<board_x_0_0>>::result, "");
    static_assert(CheckWin<GameBoard<board_x_0_4>>::result, "");
    static_assert(CheckWin<GameBoard<board_x_3_0>>::result, "");
    static_assert(CheckWin<GameBoard<board_x_5_4>>::result, "");
    static_assert(CheckWin<GameBoard<board_x_5_0>>::result, "");

    static_assert(CheckWin<GameBoard<board_red_block_near>>::result == false, "");
    static_assert(CheckWin<GameBoard<board_red_block_far>>::result == false, "");
    static_assert(CheckWin<GameBoard<board_red_block_exit>>::result == false, "");

    std::cout << std::endl << "Passed!" << std::endl << std::endl;
    return 0;
}
