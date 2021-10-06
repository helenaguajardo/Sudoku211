#pragma once

#include <vector>
#include "model.hxx"
#include <ge211.hxx>
#include "ge211_geometry.hxx"
#include "ge211_sprites.hxx"
#include "ge211_forward.hxx"
#include "ge211_resource.hxx"


extern ge211::Color const
        individual_box_color,
        mini_box_color,
        rectangle_color,
        selection_color;
extern ge211::Dims<int> const individual_box_dims, mini_box_dims,
        horizontal_rectangle_dims, vertical_rectangle_dims;

using Box = ge211::Rect<int>;

using Text = ge211::Text_sprite;

class Digit_sprite
{
public:
    explicit Digit_sprite(ge211::Text_sprite digit);


private:
    ge211::Text_sprite red_;
    ge211::Text_sprite black_;

};

struct Ui : ge211::Abstract_game
{

    explicit Ui(Model&);

    Text original_digit_;
    Text valid_digit_;
    Text invalid_digit_;



    //Declaring font for number text
    ge211::Font sans32_{"sans.ttf", 20};

    //instruction font
    ge211::Font sans_smaller{"sans.ttf", 13};

    //non-selection
    ge211::Posn<int> selection_{-1, -1};

    bool valid_selection;


    void draw(ge211::Sprite_set&) override;


    ///
    /// MEMBER FUNCTIONS (for the controller)
    ///

    void on_key(ge211::Key) override;

    void on_mouse_up(ge211::Mouse_button, ge211::Posn<int>) override;

    ///
    /// MEMBER VARIABLE (model reference)
    ///

    Model& model_;

    ///
    /// MEMBER VARIABLES (for the view)
    ///

    ge211::Rectangle_sprite const individual_box_sprite_
            {individual_box_dims,
             individual_box_color};

    ge211::Rectangle_sprite const
            horizontal_rectangle_sprite{horizontal_rectangle_dims,
                                        rectangle_color};
    ge211::Rectangle_sprite const
            vertical_rectangle_sprite{vertical_rectangle_dims,
                                      rectangle_color};

    ge211::Rectangle_sprite selection_sprite_{individual_box_dims,
                                              selection_color};


    Text
            original_digit_sprite_;
    Text
            starting_digit_sprite_{"_", sans32_};


    ge211::Text_sprite const
            subtitle{"Welcome to Sudoku!",
                     sans32_};

    ge211::Text_sprite const
            instructions_one{"Click Mouse to select a box",
                             sans_smaller};

    ge211::Text_sprite const
            instructions_two{"press SPACE_BAR to "
                             "unselect",
                             sans_smaller};
    ge211::Text_sprite const
            instructions_three{"press 'q' to quit",
                               sans_smaller};

    ge211::Text_sprite const
            instructions_four{"pink number means it is Invalid",
                              sans_smaller};


    ge211::Text_sprite const
            winning_title{"CONGRATULATIONS YOU SOLVED THIS PUZZLE!",
                          sans32_};


    std::vector<Text> digit_sprites_black;

    std::vector<Text> digit_sprites_red;

    std::vector<Text> digit_sprites_blue;

    std::vector<Text> digit_sprites_green;

    std::vector<Box> box_vector;
};
