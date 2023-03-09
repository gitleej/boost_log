//
// Created by AILEE on 2023/3/9.
//

#include "Utils.h"

#include <unistd.h>

bool mvpr_log::Utils::isExist(const char *path) {
    if (access(path, 0) != F_OK) {
        return false;
    }
    return true;
}
