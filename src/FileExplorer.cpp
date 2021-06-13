#include "FileExplorer.hpp"

using namespace std;

FileExplorer::~FileExplorer () {
    if (_sorted_entries_in_dir)
        fclose(_sorted_entries_in_dir);
}

FileExplorer::FileExplorer() {
    _sorted_entries_in_dir = fopen("/.db", "r");
    _line_offsets.push_back(0);
}

void FileExplorer::set_dir(const string & dir_name, SeekMode seek_mode) {
    if (_sorted_entries_in_dir)
        fclose(_sorted_entries_in_dir);
    if (SeekMode::Absolute == seek_mode)
        _current_path = dir_name;
    else
        if (dir_name == "..")
            _current_path = _current_path.parent_path();
        else
            _current_path += dir_name;
    _sorted_entries_in_dir = fopen((_current_path / ".db").c_str(), "r");
    _line_offsets.clear();
    _line_offsets.push_back(0);
    _current_idx = 0;
}

string FileExplorer::next_file_name() {
    char entry[255];
    if (fgets((char *)entry, 255, _sorted_entries_in_dir) == nullptr)
        return string();
    _current_idx++;
    if (_current_idx == _line_offsets.size())
        _line_offsets.push_back(static_cast<unsigned>(char_traits<char>::length(entry)) + _line_offsets.back());
    return string(entry);
} 

string FileExplorer::seek_file_name(int offset_idx, SeekMode seek_mode) {
    if (seek_mode == SeekMode::Relative && offset_idx < (
        static_cast<int>(_line_offsets.size()) - _current_idx - 1) && offset_idx > (-_current_idx))
    {
        if(fseek(_sorted_entries_in_dir, static_cast<long>(_line_offsets[_current_idx + offset_idx - 1]), SEEK_SET))
            return string(); //error seeking!
        _current_idx += offset_idx - 1;
    }
    else if (seek_mode == SeekMode::Absolute && offset_idx >= 0 && offset_idx < static_cast<int>(_line_offsets.size() - 1))
    {
        if(fseek(_sorted_entries_in_dir, static_cast<long>(_line_offsets[offset_idx]), SEEK_SET))
            return string(); //error seeking!
        _current_idx = offset_idx;
    }
    else
        return string();
    
    return next_file_name();
}

string FileExplorer::get_dir() {
    return _current_path.string();
}