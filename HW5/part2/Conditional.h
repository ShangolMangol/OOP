//
// Created by regev on 04/07/2023.
//

#ifndef PART2_CONDITIONAL_H
#define PART2_CONDITIONAL_H

template<bool Cond, typename IfTrue, typename IfFalse>
struct Conditional;

template<typename IfTrue, typename IfFalse>
struct Conditional<true, IfTrue, IfFalse>
{
    typedef IfTrue value;
};

template<typename IfTrue, typename IfFalse>
struct Conditional<false, IfTrue, IfFalse>
{
    typedef IfFalse value;
};


template<bool Cond, int IfTrue, int IfFalse>
struct ConditionalInteger;

template<int IfTrue, int IfFalse>
struct ConditionalInteger<true, IfTrue, IfFalse>
{
    static constexpr int value = IfTrue;
};

template<int IfTrue, int IfFalse>
struct ConditionalInteger<false, IfTrue, IfFalse>
{
    static constexpr int value = IfFalse;
};

#endif //PART2_CONDITIONAL_H
