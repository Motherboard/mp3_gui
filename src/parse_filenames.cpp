//
// Created by master on 6/3/19.
//
/*
#include "parse_filenames.hpp"
#include <vector>
#include <string>
#include <variant>
#include <map>


bool is_digit(char ch) {
    return ch >= '0' && ch <= '9';
}


NameParts filename_parts(const std::string & filename) {
    NameParts parts;
    std::string current_part;
    for (char ch: filename) {
        if (current_part.empty())
            current_part.push_back(ch);
        else if (is_digit(ch)) {
            if (is_digit(current_part[0]))
                current_part.push_back(ch);
            else {
                parts.emplace_back(std::stoi(current_part));
                current_part.clear();
            }
        }
        else {
            if (!is_digit(current_part[0]))
                current_part.push_back(ch);
            else {
                parts.emplace_back(current_part);
                current_part.clear();
            }
        }
    }
    return parts;
}

std::map<GroupInfo, std::vector<NameParts &>> group_by_longest_common_string(std::vector<NameParts> & parsed_file_names) {
    std::map<GroupInfo, std::vector<NameParts &>> groups;
    for (int i = 0; i < parsed_file_names.size() - 1; ++i) {
        int common_string_part = -1;
        int common_string_length = 0;
        for (int j = i + 1; j < parsed_file_names.size(); ++j) {
            int parts_to_test = std::min(parsed_file_names[i].size(), parsed_file_names[j].size());
            for (int k = 0; k < parts_to_test; ++k) {
                if (std::holds_alternative<int>(parsed_file_names[i][k]))
                    continue;
                if (std::holds_alternative<int>(parsed_file_names[j][k]))
                    break;
                const auto & first = std::get<std::string>(parsed_file_names[i][k]);
                const auto & second = std::get<std::string>(parsed_file_names[j][k]);
                if (first == second && common_string_length < first.size()) {
                    common_string_length = first.size();
                    common_string_part = k;
                }
            }
        }
        if (common_string_part >= 0) {
            parsed_file_names[i].erase(std::begin(parsed_file_names[i]) + common_string_part);
            groups[GroupInfo{common_string_part, std::get<std::string>(parsed_file_names[i][common_string_part])}].push_back(parsed_file_names[i]);
        }
    }
    return groups;
}*/