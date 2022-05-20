//
// Created by AILEE on 2022/5/18.
//

#include "AbstractLogger.h"

AbstractLogger::~AbstractLogger() {
    if (this->m_logConfig != nullptr) {
        delete this->m_logConfig;
        this->m_logConfig = nullptr;
    }
}