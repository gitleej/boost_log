//
// Created by AILEE on 2022/5/19.
//

#include "Testsuite.h"

void Testsuite::testLogConfig() {
    AbstractLogConfig* boostLogConfig = new BoostLogConfig;

    boostLogConfig->LoadConfig();
    boostLogConfig->LoadConfig((char*)"../conf/log_config.json");
}

void Testsuite::testLogger() {
    AbstractLogger* boostLogger = new BoostLogger;
    AbstractLogConfig* boostLogConfig = new BoostLogConfig;

    boostLogConfig->LoadConfig((char*)"../conf/log_config.json");
    boostLogger->Init(*boostLogConfig);

    // 写日志
    src::severity_logger_mt<severity_levels> &lg = globalLogger::get();
    LOG_TRACE("its a trace msg.");
    LOG_DEBUG("its a debug msg.");
    LOG_INFO("its an info msg. %s", "ailee");
    LOG_WARN("its an warning msg. %d", 100);
    LOG_ERROR("its an error msg.");
    LOG_FATAL("its an fatal msg");

    boostLogger->Stop();
}
