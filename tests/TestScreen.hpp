//
// Created by master on 7/8/19.
//

#ifndef MP3_GUI_TESTSCREEN_HPP
#define MP3_GUI_TESTSCREEN_HPP

#include <array>
#include <string>
#include "AbstractScreen.hpp"


class TestScreen: public AbstractScreen {
public:
    ~TestScreen() final = default;
    void draw_text(int x, int y, const char * text) final {
        lines[y] = std::string(x, ' ') + text;
    }
    void draw_selected_text(int x, int y, const char * text) final {
        lines[y] = std::string(x, ' ') + std::string("*") + text;
    }
    std::array<std::string, 4> lines;
};


#endif //MP3_GUI_TESTSCREEN_HPP
