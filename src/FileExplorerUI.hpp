//
// Created by master on 6/28/19.
//

#ifndef MP3_GUI_FILEEXPLORERUI_HPP
#define MP3_GUI_FILEEXPLORERUI_HPP
#include <string>
#include <array>
#include <stack>
#include "FileExplorer.hpp"
#include "AbstractUI.hpp"

constexpr int NUM_LINES_IN_UI = 4;

class FileExplorerUI: public AbstractUI {
public:
    explicit FileExplorerUI(AbstractScreen & screen);
    ~FileExplorerUI() final = default;
    void on_down_pressed() final;
    void on_up_pressed() final;
    void on_right_pressed() final;
    void on_left_pressed() final;
    void draw_whole_screen() final;
private:
    void read_state();
    void get_first_lines(int from_idx=0);
    FileExplorer _fileExplorer;
    std::array<std::string, NUM_LINES_IN_UI> _current_lines;
    int _curr_display_idx = 0;
    int _curr_file_idx = 0;
    std::stack<int> _prev_indices;
};


#endif //MP3_GUI_FILEEXPLORERUI_HPP
