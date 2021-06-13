#include "external_sort.hpp"
#include <math.h>
#include <cstdio>
#include <vector>
#include <array>

using namespace std;




/*void merge_sorted_files(FILE * output_file, const vector<FILE *> &input_files) {
    size_t num_simultanius_files = external_sort::MEMORY_LIMIT / (input_files.size() * 255);
    size_t num_chunks = ceil(float(input_files.size()) / float(num_simultanius_files));
    vector<array<char, 255>> lines(num_simultanius_files);
    vector<string> new_input_file_names(num_chunks);
    for (size_t chunk_idx = 0; chunk_idx < num_chunks; chunk_idx++) {
        FILE * output_chunk;
        if (num_chunks > 1) {
            char tmp_output_name[20];
            sprintf(tmp_output_name, "%dt", chunk_idx);
            new_input_file_names[chunk_idx] = string(tmp_output_name);
            output_chunk = fopen(tmp_output_name, "w");
        }
        else
            output_chunk = output_file;
        bool reach_end_of_all_inputs = false;
        while (!reach_end_of_all_inputs) {
            int num_reads = 0;
            for (size_t file_idx = chunk_idx * num_simultanius_files;
                 file_idx < (chunk_idx + 1) * num_simultanius_files; file_idx++) {
                 // read one line in each file
                 if(fgets(lines[file_idx % num_simultanius_files].data(), 255, input_files[file_idx]))
                     ++num_reads;
                 //else  // <-- check if necessary
                 //    lines[file_idx % num_simultanius_files][0] = '\0';
            }
            // TODO: merge, write to output chunk

            if (num_reads == 0)
                reach_end_of_all_inputs = true;
        }
        fclose(output_chunk);
    }
    for (const auto & input_file: input_files)
        fclose(input_file);
    if (num_chunks > 1) {
        vector<FILE *> new_input_files(num_chunks);
        for (size_t i = 0; i < num_chunks; ++i)
            new_input_files[i] = fopen(new_input_file_names[i].c_str(), "r");
        merge_sorted_files(output_file, new_input_files);
    }
}*/