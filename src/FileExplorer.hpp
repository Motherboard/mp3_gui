#pragma once
#include <vector>
#include <string>
#include <cstdio>
#include <experimental/filesystem>

enum class SeekMode { Relative, Absolute };

class FileExplorer {    
    std::vector<unsigned> _line_offsets;
    std::experimental::filesystem::path _current_path{"/"};
    FILE * _sorted_entries_in_dir = nullptr;
    uint16_t _current_idx = 0;
    public:
        FileExplorer();
        ~FileExplorer();
        void set_dir(const std::string & dir_name, SeekMode seek_mode);
        std::string get_dir();
        std::string next_file_name();
        std::string seek_file_name(int offset_idx, SeekMode seek_mode);
};
