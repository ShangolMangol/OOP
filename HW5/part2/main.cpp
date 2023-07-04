#include <iostream>
#include <cassert>

#include "List.h"

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





    std::cout << "Hello, World!" << std::endl;
    return 0;
}
