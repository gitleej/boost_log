//
// Created by AILEE on 2022/5/23.
//

#ifndef MVPR_LOG_COMMON_H
#define MVPR_LOG_COMMON_H

#include <string>

//enum severity_levels
//{
//    trace = 0,
//    debug,
//    info,
//    warning,
//    error,
//    fatal
//};

std::string get_file_line(const char *filename, const char *func, const int &line);

#endif //MVPR_LOG_COMMON_H
