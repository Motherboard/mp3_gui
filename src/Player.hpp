//
// Created by master on 7/16/19.
//

#ifndef MP3_GUI_PLAYER_HPP
#define MP3_GUI_PLAYER_HPP

#include <string>
#include <chrono>
#include "FileExplorer.hpp"


class Player {
public:
    void play();
    void pause_play();
    void next_track();
    void prev_track();
    void fast_foreward(int speed);
    void rewined(int speed);
    void set_track(std::string path);
    std::string & get_track();

private:
    int _play_speed = 1;
    FileExplorer _file_explorer;
    std::string _current_track;
    unsigned int _elapsed_time;
};


#endif //MP3_GUI_PLAYER_HPP
