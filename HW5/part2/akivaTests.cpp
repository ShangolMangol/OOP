//
// Created by akiva on 1/10/2020.
//

#include <iostream>
#include "RushHour.h"
#include "Printer.h"
#include <string>


typedef List<
        List<BoardCell<EMPTY, RIGHT, 1>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<O, DOWN, 3>, BoardCell<EMPTY, RIGHT, 0> >,
        List<BoardCell<EMPTY, RIGHT, 2>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<A, RIGHT, 2>, BoardCell<A, LEFT, 2>, BoardCell<O, DOWN, 3>, BoardCell<EMPTY, RIGHT, 0> >,
        List<BoardCell<EMPTY, RIGHT, 3>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<X, RIGHT, 2>, BoardCell<X, LEFT, 2>, BoardCell<O, UP, 3>, BoardCell<EMPTY, RIGHT, 0> >,
        List<BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0> >,
        List<BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<B, DOWN, 2>, BoardCell<P, RIGHT, 3>, BoardCell<P, RIGHT, 3>, BoardCell<P, LEFT, 3> >,
        List<BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<B, UP, 2>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<C, RIGHT, 2>, BoardCell<C, LEFT, 2> >
> gameBoardLists;
typedef GameBoard<gameBoardLists> gameBoard;

void TestGameBoard() {
    typedef GameBoard<List<>> emptyBoard;

    Printer<gameBoard>::print((std::cout));
    typedef GameBoard<List<
            List<BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>>,
            List<BoardCell<X, RIGHT, 1>, BoardCell<A, UP, 1>>,
            List<BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>>
    >> gameBoard2;

    static_assert(gameBoard::width == 6, "GameBoard 1 width error");
    static_assert(gameBoard2::width == 2, "GameBoard 2 width error");
    static_assert(gameBoard::length == 6, "GameBoard 1 length error");
    static_assert(gameBoard2::length == 3, "GameBoard 2 length error");
    static_assert(std::is_same<gameBoard::board, gameBoardLists>::value == true,
                  "the board suppose to hold the list of lists");
}

void testMoveVehicle(){
    typedef typename MoveVehicle<gameBoard,2, 2, LEFT, 2>::board x_2_left_1;
    typedef typename MoveVehicle<gameBoard,2, 3, LEFT, 2>::board x_2_left_2;
    static_assert(std::is_same<x_2_left_1,x_2_left_2>::value == true, "Both coordinates are point on the same car,"
                                                                      " so it suppose to be equal");

    typedef typename GetAtIndex<2, typename GetAtIndex<5, gameBoard::board>::value>::value B;

    typedef typename MoveVehicle<gameBoard,5, 2, UP, 1>::board b_1_up;
    static_assert(std::is_same<x_2_left_1, b_1_up>::value == false, "Both coordinates are'nt point on the same car,"
                                                                    " so it not suppose to be equal");

    typedef typename GetAtIndex<2, typename GetAtIndex<5, b_1_up::board>::value>::value oldB;
    typedef typename GetAtIndex<2, typename GetAtIndex<3, b_1_up::board>::value>::value newB;
    static_assert(oldB::type == EMPTY, "old position of B suppose to be empty");
    static_assert((B::type == newB::type) && (B::length ==  newB::length), "B suppose to move one up");

    typedef typename MoveVehicle<b_1_up, 5,4,LEFT,4>::board b1up_c4left;
    typedef typename GetAtIndex<1, typename GetAtIndex<5, b1up_c4left::board>::value>::value newC;
    typedef typename GetAtIndex<4, typename GetAtIndex<5, b1up_c4left::board>::value>::value oldC;
    static_assert(oldC::type == EMPTY, "old position of C suppose to be empty");
    static_assert(newC::type == C, "c suppose to move to the left side of the board");
};
void testMoveVehicleErrors(){
    // ##### do this function after 'testMoveVehicle' function is compiled successfully #####
    // ##### remove one comment each time to check if the compilation failed #######

    //typedef typename MoveVehicle<gameBoard,-1, 2, RIGHT, 1>::board b; // error: out of board bounds. left
    //typedef typename MoveVehicle<gameBoard,6, 2, RIGHT, 1>::board b; // error: out of board bounds. down
    //typedef typename MoveVehicle<gameBoard,2, -1, RIGHT, 1>::board b2; // error: out of board bounds. up
    //typedef typename MoveVehicle<gameBoard,2, 6, RIGHT, 1>::board b2; // error: out of board bounds. right

    //typedef typename MoveVehicle<gameBoard,0, 0, RIGHT, 1>::board b; // error: empty cell

    //typedef typename MoveVehicle<gameBoard,2, 2, DOWN, 1>::board b; // error: wrong direction
    //typedef typename MoveVehicle<gameBoard,5, 2, LEFT, 1>::board b; // error: wrong direction

    //typedef typename MoveVehicle<gameBoard,2, 2, RIGHT, 1>::board b; // O block X
    //typedef typename MoveVehicle<gameBoard,5, 2, UP, 2>::board b; // X block B
    //typedef typename MoveVehicle<gameBoard,5, 5, LEFT, 4>::board b; // B block C

}



int main(){
    // run it to see how the board look like. it's gorgeous!
    Printer<gameBoard>::print(std::cout);
}