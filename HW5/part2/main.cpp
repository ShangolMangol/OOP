#include <iostream>
#include <cassert>

#include "List.h"
#include "Conditional.h"
#include "BoardCell.h"
#include "MoveVehicle.h"


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








    std::cout << std::endl << "Passed!" << std::endl << std::endl;
    return 0;
}
