//
// Created by master on 6/28/19.
//
#include <algorithm>
#include "FileExplorerUI.hpp"
#include <iostream>

using namespace std;

FileExplorerUI::FileExplorerUI(AbstractScreen &screen) : AbstractUI(screen) { read_state(); }


void FileExplorerUI::on_down_pressed() {
    if (_curr_display_idx < NUM_LINES_IN_UI - 1 && _current_lines[_curr_display_idx + 1].empty())
        return;
    if (_curr_display_idx < NUM_LINES_IN_UI - 1) {
        _curr_display_idx++;
        _curr_file_idx++;
        _fileExplorer.next_file_name();
    }
    else {
        auto next_file_name = _fileExplorer.next_file_name();
        if (next_file_name.empty())
            return;
        rotate(_current_lines.begin(), _current_lines.begin() + 1, _current_lines.end());
        _current_lines[_curr_display_idx] = next_file_name;
        _curr_file_idx++;
    }
    draw_whole_screen();
}

void FileExplorerUI::on_up_pressed() {
    if (_curr_display_idx > 0) {
        _curr_display_idx--;
        _curr_file_idx--;
        _fileExplorer.seek_file_name(-1, SeekMode::Relative);
    }
    else {
        auto prev_line = _fileExplorer.seek_file_name(-1, SeekMode::Relative);
        if (prev_line.empty())
            return;
        rotate(_current_lines.rbegin(), _current_lines.rbegin() + 1, _current_lines.rend());
        _current_lines[0] = prev_line;
        _curr_file_idx--;
    }
    draw_whole_screen();
}

void FileExplorerUI::on_right_pressed() {
    if (_current_lines[_curr_display_idx][_current_lines[_curr_display_idx].size() - 1] == '/') {
        auto dir_name = _current_lines[_curr_display_idx];
        _fileExplorer.set_dir(dir_name.substr(0, dir_name.size() - 1), SeekMode::Relative);
        _prev_indices.push(_curr_file_idx);
        _curr_display_idx = 0;
        _curr_file_idx = 0;
        get_first_lines();
        draw_whole_screen();
    }
}

void FileExplorerUI::on_left_pressed() {
    if (_prev_indices.empty())
        return;
    _fileExplorer.set_dir("..", SeekMode::Relative);
    _curr_file_idx = _prev_indices.top();
    _prev_indices.pop();
    get_first_lines(_curr_file_idx);
    _curr_display_idx = 0;
    draw_whole_screen();
}

void FileExplorerUI::draw_whole_screen() {
    for (int i = 0; i < NUM_LINES_IN_UI; ++i) {
        if (i == _curr_display_idx)
            _screen.draw_selected_text(0, i, _current_lines[i].c_str());
        else
            _screen.draw_text(0, i, _current_lines[i].c_str());
    }
}

void FileExplorerUI::read_state() {
    _fileExplorer.set_dir("/", SeekMode::Absolute);
    get_first_lines();
}

void FileExplorerUI::get_first_lines(int from_idx) {
    for (int i = 0; i < from_idx; ++i) {
        _fileExplorer.next_file_name();
    }
    for (int i = 0; i < NUM_LINES_IN_UI; ++i) {
        _current_lines[i] = _fileExplorer.next_file_name();
    }
    _fileExplorer.seek_file_name(from_idx, SeekMode::Absolute);
}


