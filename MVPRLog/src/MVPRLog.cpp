//
// Created by nuc on 2022/5/11.
//
#define MVPR_LOG_EXPORTS

#include "../include/MVPRLog.h"
#include "BoostLogger.h"
#include "BoostLogConfig.h"

MVPRLog* MVPRLog::_pInstance = nullptr;

MVPRLog::MVPRLog() {}

MVPRLog::~MVPRLog() {
    MVPRLog::Stop();
    if (this->m_logger != nullptr) {
        delete this->m_logger;
        this->m_logger = nullptr;
    }

    if (this->m_logConfig != nullptr) {
        delete this->m_logConfig;
        this->m_logConfig = nullptr;
    }
}

MVPRLog *MVPRLog::GetInstance() {
    if (nullptr == _pInstance) {
        fprintf(stderr, "please Init first.\n");
        return nullptr;
    }
    return _pInstance;
}

void MVPRLog::Init() {
    if (nullptr == _pInstance) {
        _pInstance = new MVPRLog();
        MVPRLog::GetInstance()->m_logger = new BoostLogger;
        MVPRLog::GetInstance()->m_logConfig = new BoostLogConfig;
        // 加载日志配置文件
        MVPRLog::LoadConfig();
        MVPRLog::GetInstance()->m_logger->Init(*(MVPRLog::GetInstance()->m_logConfig));
    }
}

void MVPRLog::Init(const char* configFilePath) {
    if (nullptr == _pInstance) {
        _pInstance = new MVPRLog();
        MVPRLog::GetInstance()->m_logger = new BoostLogger;
        MVPRLog::GetInstance()->m_logConfig = new BoostLogConfig;
        // 加载日志配置文件
        MVPRLog::LoadConfig(configFilePath);
        MVPRLog::GetInstance()->m_logger->Init(*(MVPRLog::GetInstance()->m_logConfig));
    }
}

void MVPRLog::LoadConfig() {
    MVPRLog::GetInstance()->m_logConfig->LoadConfig();
}

void MVPRLog::LoadConfig(const char *configFilePath) {
    MVPRLog::GetInstance()->m_logConfig->LoadConfig(configFilePath);
}

void MVPRLog::WriteLog(const char *filename, const char *func, int line, severity_levels level, const char *fmt, ...) {
    va_list al;
    va_start(al, fmt);
    char *buffer = new char[1024];
    memset(buffer, 0, 1024);
//    vsnprintf(buffer, 1024, 1023, fmt, al);
    vsnprintf(buffer, 1024, fmt, al);
    std::string file = get_file_line(filename, func, line);
    std::string msg = buffer;
    msg = file + ": " + msg;
    MVPRLog::GetInstance()->m_logger->WriteLog(level, msg.c_str());
}

void MVPRLog::Stop() {
    MVPRLog::GetInstance()->m_logger->Stop();
}
