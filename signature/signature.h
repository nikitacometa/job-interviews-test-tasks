#pragma once

#include <string>

#define DEFAULT_BLOCK_SIZE (1L * 1024 * 1024) // 1mb
#define MAX_BLOCK_SIZE (1L * 256 * 1024 * 1024) // 256mb

extern long long block_size;

void create_signature(const std::string &input_filename, const std::string &output_filename);
