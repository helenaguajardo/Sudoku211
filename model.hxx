#pragma once

#include <ge211.hxx>

#include <iostream>
#include <array>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "ge211_geometry.hxx"

using Digit = int;
using Row = std::array<Digit, 9>;
using Grid = std::array<Row, 9>;

class Model {
public:
    // A board consists of the starting puzzle and the solution
    Model(Grid const& puzzle, Grid const& solution);

    ///
    /// Modifying the state
    ///

    // the player is able to enter a digit into a specified postion
    void play_move(Digit digit, ge211::Posn<int>);


    ///
    /// Querying the state
    ///

    // returns the digit at the specified position
    Digit get_digit(ge211::Posn<int>) const;

    // determines whether a position's digit is one already given, if so false
    bool is_edited(ge211::Posn<int>) const;

    // determines whether a position's digit conflicts with another positions
    // digit in the row, column, or grid, if so returns true
    bool is_ineligible(ge211::Posn<int>) const;

    // determines whether the editing grid and the solution grid match, if so
    // returns true
    bool is_complete() const;

    Grid starting_grid_;
    Grid solved_grid_;
    Grid unsolved_grid_;


};


