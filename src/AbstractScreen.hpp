//
// Created by master on 6/29/19.
//

#ifndef MP3_GUI_ABSTRACTSCREEN_HPP
#define MP3_GUI_ABSTRACTSCREEN_HPP

class AbstractScreen {
public:
    virtual ~AbstractScreen() = default;
    virtual void draw_text(int x, int y, const char * text) = 0;
    virtual void draw_selected_text(int x, int y, const char * text) = 0;
};

#endif //MP3_GUI_ABSTRACTSCREEN_HPP
