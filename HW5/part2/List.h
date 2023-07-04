#ifndef PART2_LIST_H
#define PART2_LIST_H

/**
 *  List<>::size
 *  List<>::head
 *  List<>::next
 */
//region List
template<typename... Items>
struct List;

template<typename T, typename... TT>
struct List<T, TT...>
{
    static constexpr int size = sizeof...(TT) + 1;
    typedef T head;
    typedef List<TT...> next;
};

template<>
struct List<>
{
    static constexpr int size = 0;
};
//endregion

/**
 * PrependList<Item, List>::list
 */
//region PrependList
template <typename T, typename S>
struct PrependList;

template <typename Item, typename... TT>
struct PrependList<Item, List<TT...>>
{
    typedef List<Item, TT...> list;
};

//endregion

/**
 * GetAtIndex<Index,List>::value
 */
//region GetAtIndex
template <int N, typename ListItem>
struct GetAtIndex;

template <typename Item, typename... TT>
struct GetAtIndex< 0, List<Item, TT...>>
{
    typedef Item value;
};

template <int N, typename Item, typename... TT>
struct GetAtIndex< N, List<Item, TT...>>
{
    typedef typename GetAtIndex< N-1, List<TT...>>::value value;
};

//endregion

/**
 * GetAtIndex<Index,Item, List>::list
 */
//region SetAtIndex
template <int N, typename Value, typename ListItem>
struct SetAtIndex;

template<typename Item, typename Value, typename... TT>
struct SetAtIndex<0, Value, List<Item, TT...>>
{

    typedef List<Value, TT...> list;
};


template<int N, typename Item, typename Value, typename... TT>
struct SetAtIndex<N, Value, List<Item, TT...> >
{
    typedef typename
    PrependList<
        Item,
        typename SetAtIndex<N-1, Value, List<TT...>>::list
    >::list list;
};
//endregion

#endif //PART2_LIST_H
