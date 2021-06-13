//
// Created by master on 7/7/19.
//

#include "FSMocks.hpp"
#include <vector>
#include <string>
#include <cstdio>
#include <iostream>
#include "hippomocks.h"

std::vector<int> _get_seek_positions(const std::vector<std::string> & files) {
    std::vector<int> tmp;
    tmp.push_back(0);
    for (const auto & filename: files)
        tmp.push_back(tmp.back() + filename.length());
    return tmp;
}


FSMocks::FSMocks(const std::map<std::string, std::vector<std::string>> &in_fs) : fs(in_fs) {
        mocks.OnCallFunc(fopen).Do(
                [&](const char *filename, const char * mode)->FILE * {
                    files = fs[filename];
                    positions = _get_seek_positions(files);
                    entry_idx = 0;
                    return reinterpret_cast<FILE *>(1);
                }
        );
        mocks.OnCallFunc(fgets).Do(
        [&](char *buf, int n, FILE *f) -> char * {
            if (entry_idx < files.size()) {
                strcpy(buf, files[entry_idx++].c_str());
                return buf;
            } else
                return nullptr;
        }
        );
        mocks.OnCallFunc(fclose).Return(0);
        mocks.OnCallFunc(fseek).Do(
        [&](FILE *file, long position, int seek_type) -> int {
            if (seek_type == SEEK_SET && position >= 0 && position < positions.back()) {
                size_t offset_covered = 0;
                entry_idx = 0;
                while (offset_covered < position && entry_idx < files.size()) {
                    offset_covered += files[entry_idx].length();
                    entry_idx++;
                }
                if (offset_covered != positions[entry_idx] || offset_covered != position) {
                    std::cerr << "[ERROR] Failed seeking!" << offset_covered << " != " << positions[entry_idx] << " or " << offset_covered << " != " << position << std::endl;
                    return 1;
                }
            }
            return 0;
        }
        );
}