//
// Created by AILEE on 2022/5/23.
//
#include "../include/common.h"

std::string get_file_line(const char *filename, const char *func, const int &line) {
    std::string s = filename;
    auto idx = s.find_last_of("/\\" );
    s = s.substr(idx + 1, s.length());

    char buffer[100] = {0};
    snprintf(buffer, 100, "%s@%s: line:%d", s.c_str(), func, line);
    s = buffer;

    return s;
}

