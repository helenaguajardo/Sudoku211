#include "ui.hxx"
#include "model.hxx"


Digit_sprite::Digit_sprite(ge211::Text_sprite digit)
        : red_(digit) , black_(digit)
{}


Ui::Ui(Model& model)
        : model_(model)
{
    // vector of BLACK digit sprites
    for (int x = 0; x <= 9; x++) {
        ge211::Text_sprite::Builder builder(sans32_);
        builder.color(ge211::Color::black());
        builder << x;
        original_digit_sprite_.reconfigure(builder);
        digit_sprites_black.push_back(original_digit_sprite_);
    }

    // vector of BLUE digit sprites
    for (int x = 0; x <= 9; x++) {
        ge211::Text_sprite::Builder builder(sans32_);
        builder.color(ge211::Color::medium_blue());
        builder << x;
        original_digit_sprite_.reconfigure(builder);
        digit_sprites_blue.push_back(original_digit_sprite_);
    }

    // vector of RED digit sprites
    for (int x = 0; x <= 9; x++) {
        ge211::Text_sprite::Builder builder(sans32_);
        builder.color(ge211::Color::medium_green());
        builder << x;
        original_digit_sprite_.reconfigure(builder);
        digit_sprites_red.push_back(original_digit_sprite_);
    }

    // vector of digit sprites
    for (int x = 0; x <= 9; x++) {
        ge211::Text_sprite::Builder builder(sans32_);
        builder.color(ge211::Color::medium_blue());
        builder << x;
        original_digit_sprite_.reconfigure(builder);
        digit_sprites_green.push_back(original_digit_sprite_);
    }


    for (int x = 0; x < 9; x++) {
        for (int y = 0; y < 9; y++) {
            Box each_box;
            each_box.width  = individual_box_dims.width;
            each_box.height = individual_box_dims.height;
            each_box.x      = 214 + (40 * y);
            each_box.y      = 124 + (40 * x);
            box_vector.push_back(each_box);
        }
    }

}


// Use `Sprite_set::add_sprite(Sprite&, Position)` to add each sprite
// to `sprites`.
ge211::Dims<int> const individual_box_dims{35, 35};
ge211::Dims<int> const horizontal_rectangle_dims{365, 5};
ge211::Dims<int> const vertical_rectangle_dims{5, 355};


void Ui::draw(ge211::Sprite_set& sprites)
{
    sprites.add_sprite(subtitle,
                       {300, 70}, 1);
    sprites.add_sprite(instructions_one,
                       {10, 214}, 1);
    sprites.add_sprite(instructions_two,
                       {10, 265}, 1);
    sprites.add_sprite(instructions_three,
                       {10, 315}, 1);
    sprites.add_sprite(instructions_four,
                       {10, 365}, 1);

    //borders
    sprites.add_sprite(horizontal_rectangle_sprite,
                       {210, 120}, 1);
    sprites.add_sprite(horizontal_rectangle_sprite,
                       {210, 240}, 1);
    sprites.add_sprite(horizontal_rectangle_sprite,
                       {210, 360}, 1);
    sprites.add_sprite(horizontal_rectangle_sprite,
                       {210, 480}, 1);
    sprites.add_sprite(vertical_rectangle_sprite,
                       {210, 124}, 1);
    sprites.add_sprite(vertical_rectangle_sprite,
                       {330, 124}, 1);
    sprites.add_sprite(vertical_rectangle_sprite,
                       {450, 124}, 1);
    sprites.add_sprite(vertical_rectangle_sprite,
                       {570, 124}, 1);


    for (Box each_box : box_vector) {
        sprites.add_sprite(individual_box_sprite_,
                           each_box.top_left(), 2);
    }

    for (int x = 0; x < 9; x++) {
        for (int y = 0; y < 9; y++) {
            ge211::Posn<int> grid_pos = {x, y};

            //starting numbers that cannot be changed
            if (!model_.is_edited(grid_pos)) {
                sprites.add_sprite(
                        digit_sprites_black.at(model_.unsolved_grid_[x][y]),
                        {226 + (40 * y), 125 + (40 * x)}, 3);
            }
            //starting blank boxes
            if (model_.unsolved_grid_[x][y] == 0 && selection_ != grid_pos){
            }

            if (model_.is_edited(grid_pos) && model_.unsolved_grid_[x][y]
                                              != 0 && selection_ == grid_pos){
                sprites.add_sprite(selection_sprite_, {215 + (40 * y), 125 +
                                                                       (40 * x)},3);
                if(model_.is_ineligible(grid_pos)){
                    for (int x = 0; x < 9; x++) {
                        for (int y = 0; y < 9; y++) {
                            ge211::Posn<int> grid_pos_two = {x, y};
                            if(model_.is_ineligible(grid_pos_two) && model_
                                                                             .unsolved_grid_[x][y] != 0) {
                                sprites.add_sprite(digit_sprites_red.at(
                                        model_.unsolved_grid_[x][y]),
                                                   {227 + (40 * y),
                                                    126 + (40 * x)}, 4);
                            }
                        }
                    }
                }else{
                    sprites.add_sprite(digit_sprites_blue.at(model_
                                                                     .unsolved_grid_[x][y]), {227 + (40 * y),
                                                                                              126 + (40 * x)}, 4);
                }
                //selection_ ={-1,-1};
            }
            else if (model_.is_ineligible(grid_pos) && model_
                                                               .unsolved_grid_[x][y]
                                                       != 0){

                sprites.add_sprite(digit_sprites_red.at(model_
                                                                .unsolved_grid_[x][y]),
                                   {227 + (40 * y), 126 + (40 * x)}, 3);
            }else if (selection_ == grid_pos && model_.is_edited
                                                              (grid_pos) && model_.unsolved_grid_[x][y] == 0){

                sprites.add_sprite(selection_sprite_, {215 + (40 * y), 125 +
                                                                       (40 * x)},3);
                sprites.add_sprite(starting_digit_sprite_, {227 + (40 * y),
                                                            126 + (40 * x)}, 4);
            }
            else if (!model_.is_ineligible(grid_pos) && model_
                                                                .unsolved_grid_[x][y]
                                                        != 0 && model_
                             .is_edited(grid_pos)){
                sprites.add_sprite(digit_sprites_blue.at(model_
                                                                 .unsolved_grid_[x][y]), {227 + (40 * y),
                                                                                          126 + (40 * x)}, 4);
            }

            if (model_.is_complete()){
                for (int x = 0; x < 9; x++) {
                    for (int y = 0; y < 9; y++) {
                        ge211::Posn<int> grid_pos_three = {x, y};
                        if (model_.is_edited(grid_pos_three)) {
                            sprites.add_sprite(digit_sprites_green.at(model_
                                                                              .unsolved_grid_[x][y]),
                                               {227 + (40 * y), 126 + (40 * x)},
                                               4);
                        }
                    }
                }
                sprites.add_sprite(winning_title,
                                   {150, 515}, 1);
            }

        }
    }
}


///
/// VIEW CONSTANTS
///


//Color of the 81 individual squares on the box  : white
ge211::Color const individual_box_color{255, 255, 255};

// Color of the 9 boxes (each of these boxes contain 9 smaller boxes) : pink
ge211::Color const mini_box_color{255, 0, 255};

//Color of the giant Sudoku grid (grid outline) : green
ge211::Color const rectangle_color{100, 200, 200};

//user selection color
ge211::Color const selection_color{180, 200, 190, 255};


///
/// CONTROLLER FUNCTIONS
///

// Determines key functions for the game
void Ui::on_key(ge211::Key key)
{


    //Digit digit;
    if (key == ge211::Key::code('q')) {
        quit();
    }
    if (model_.is_edited(selection_)) {

        if (key == ge211::Key::code('\b')) {
            model_.unsolved_grid_[selection_.x][selection_.y] = 0;
        }
        if (key == ge211::Key::code(' ')) {
            selection_ = {-1, -1};
            valid_selection = false;
        }
        if (key == ge211::Key::up()) {
            int x = selection_.x;
            for (int i = x - 1; i >= 0; i--) {
                if (model_.is_edited({i, selection_.y})){
                    selection_ = {i, selection_.y};
                    break;
                }
            }
            if (selection_.x == x) {
                for (int j = selection_.x - 1; j >= 0; j--) {
                    for (int i = 0; i < 9; i++) {
                        if (model_.is_edited({j, i}) && i != selection_.y) {
                            selection_ = {j, i};
                            return;
                        }
                    }
                }
            }
        }
        if (key == ge211::Key::down()) {
            int x = selection_.x;
            for (int i = x + 1; i < 9; i++) {
                if (model_.is_edited({i, selection_.y})){
                    selection_ = {i, selection_.y};
                    break;
                }
            }
            if (selection_.x == x) {
                for (int j = selection_.x + 1; j < 9; j++) {
                    for (int i = 0; i < 9; i++) {
                        if (model_.is_edited({j, i}) && i != selection_.y) {
                            selection_ = {j, i};
                            return;
                        }
                    }
                }
            }
        }
        if (key == ge211::Key::left()) {
            int y = selection_.y;
            for (int i = y - 1; i >= 0; i--) {
                if (model_.is_edited({selection_.x, i})){
                    selection_ = {selection_.x, i};
                    break;

                }
            }
            if (selection_.y == y) {
                for (int j = selection_.y - 1; j >= 0; j--) {
                    for (int i = 0; i < 9; i++) {
                        if (model_.is_edited({i, j}) && i != selection_.x) {
                            selection_ = {i, j};
                            return;
                        }
                    }
                }
            }
        }
        if (key == ge211::Key::right()) {
            int      y = selection_.y;
            for (int i = y + 1; i < 9; i++) {
                if (model_.is_edited({selection_.x, i})) {
                    selection_ = {selection_.x, i};
                    break;
                }
            }
            if (selection_.y == y) {
                for (int j = selection_.y + 1; j < 9; j++) {
                    for (int i = 0; i < 9; i++) {
                        if (model_.is_edited({i, j}) && i != selection_.x) {
                            selection_ = {i, j};
                            return;
                        }
                    }
                }
            }
        }
        //if (digit) { // Idk if we need this line
        if (key == ge211::Key::code('1')) {
            model_.unsolved_grid_[selection_.x][selection_.y] = 1;

        } else if (key == ge211::Key::code('2')) {
            model_.unsolved_grid_[selection_.x][selection_.y] = 2;

        } else if (key == ge211::Key::code('3')) {
            model_.unsolved_grid_[selection_.x][selection_.y] = 3;

        } else if (key == ge211::Key::code('4')) {
            model_.unsolved_grid_[selection_.x][selection_.y] = 4;

        } else if (key == ge211::Key::code('5')) {
            model_.unsolved_grid_[selection_.x][selection_.y] = 5;

        } else if (key == ge211::Key::code('6')) {
            model_.unsolved_grid_[selection_.x][selection_.y] = 6;

        } else if (key == ge211::Key::code('7')) {
            model_.unsolved_grid_[selection_.x][selection_.y] = 7;


        } else if (key == ge211::Key::code('8')) {
            model_.unsolved_grid_[selection_.x][selection_.y] = 8;

        } else if (key == ge211::Key::code('9')) {
            model_.unsolved_grid_[selection_.x][selection_.y] = 9;

        }
    }else{

    }
}

// Allows the player to only click on modifiable positions
void Ui::on_mouse_up(ge211::Mouse_button, ge211::Posn<int> pos)
{

    ge211::Posn<int> clicked  = {(pos.y - 125)/(40), (pos.x - 215)/
                                                     (40)};
    //auto selected = selection_;

    selection_ = {-1,-1};
    valid_selection = false;

    if (clicked.x > 8 || clicked.x < 0 || clicked.y > 8 || clicked.y < 0){
        return;
    }
    else {
        selection_ = clicked;
        valid_selection = true;
        return;
    }

}