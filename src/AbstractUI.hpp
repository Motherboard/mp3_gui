//
// Created by master on 6/29/19.
//

#ifndef MP3_GUI_ABSTRACTUI_HPP
#define MP3_GUI_ABSTRACTUI_HPP

#include "AbstractScreen.hpp"


class AbstractUI {
public:
    AbstractUI() = delete;
    explicit AbstractUI(AbstractScreen & screen): _screen(screen) {}
    virtual ~AbstractUI() = default;
    virtual void on_down_pressed() = 0;
    virtual void on_up_pressed() = 0;
    virtual void on_right_pressed() = 0;
    virtual void on_left_pressed() = 0;
    virtual void draw_whole_screen() = 0;

protected:
    AbstractScreen & _screen;

};


#endif //MP3_GUI_ABSTRACTUI_HPP
