#pragma once

#include <cstdio>
#include <vector>

namespace  external_sort { constexpr size_t MEMORY_LIMIT = 100000; }

void merge_sorted_files(const FILE * output_file, const std::vector<const FILE *> &input_files);
