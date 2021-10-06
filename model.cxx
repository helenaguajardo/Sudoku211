#include "model.hxx"

Model::Model(Grid const& starting, Grid const& finished)
        : starting_grid_(starting),
          solved_grid_(finished),
          unsolved_grid_(starting)
{ }

// gives the digit at the specified position
Digit Model::get_digit(ge211::Posn<int> pos) const
{
    return unsolved_grid_[pos.x][pos.y];
}

// the player is able to enter/remove a digit in a position that is
// originally zero
void Model::play_move(Digit digit, ge211::Posn<int> pos)
{
    if (is_edited(pos)) {
        unsolved_grid_[pos.x][pos.y] = digit;
    }
}


// determines whether a position's digit is one already given, if so false
bool Model::is_edited(ge211::Posn<int> pos) const
{
    return starting_grid_[pos.x][pos.y] == 0;
}

// determines whether a position's digit conflicts with another positions
// digit in the row, column, or grid, if so returns true
bool Model::is_ineligible(ge211::Posn<int> pos) const
{
    for (int i = 0; i < 9; i++) {
        if (i != pos.y &&
            unsolved_grid_[pos.x][i] == get_digit(pos)) {
            return true;
        }
    }
    for (int i = 0; i < 9; i++) {
        if (i != pos.x &&
            unsolved_grid_[i][pos.y] == get_digit(pos)) {
            return true;
        }
    }
    for (int i = 0; i < 9; i++) {
        int xpos = (pos.x / 3) * 3 + (i / 3);
        int ypos = (pos.y / 3) * 3 + ((i+3) % 3);
        if ((unsolved_grid_[xpos][ypos] == get_digit(pos)) &&
            (xpos != pos.x || ypos != pos.y)){
            return true;
        }
    }
    return false;
}
bool Model::is_complete() const
{
    return unsolved_grid_ == solved_grid_;
}
