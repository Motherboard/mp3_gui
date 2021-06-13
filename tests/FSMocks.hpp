//
// Created by master on 7/7/19.
//

#ifndef MP3_GUI_FSMOCKS_HPP
#define MP3_GUI_FSMOCKS_HPP

#include <map>
#include <vector>
#include <string>
#include "hippomocks.h"

class FSMocks {
    std::map<std::string, std::vector<std::string>> fs;
    std::vector<std::string> files;
    std::vector<int> positions;
    int entry_idx = 0;
    MockRepository mocks;
public:
    FSMocks(const std::map<std::string, std::vector<std::string>> &in_fs);
};



#endif //MP3_GUI_FSMOCKS_HPP
