//
// Created by AILEE on 2022/5/19.
//

#include "Testsuite.h"

void Testsuite::testLogConfig() {
    AbstractLogConfig* boostLogConfig = new BoostLogConfig;

    boostLogConfig->LoadConfig();
    boostLogConfig->LoadConfig("../conf/log_config.json");
}

void Testsuite::testLogger() {
    AbstractLogger* boostLogger = new BoostLogger;
    AbstractLogConfig* boostLogConfig = new BoostLogConfig;

    boostLogConfig->LoadConfig("../conf/log_config.json");
    boostLogger->Init(*boostLogConfig);

    // 写日志
    src::severity_logger_mt<logging::trivial::severity_level> &lg = globalLogger::get();
    BOOST_LOG_TRACE("its a trace msg.");
    BOOST_LOG_DEBUG("its a debug msg.");
    BOOST_LOG_INFO("its an info msg. %s", "ailee");
    BOOST_LOG_WARN("its an warning msg. %d", 100);
    BOOST_LOG_ERROR("its an error msg.");
    BOOST_LOG_FATAL("its an fatal msg");

    boostLogger->Stop();
}

void Testsuite::testMVPRLogger() {
//    MVPRLog::Init("../conf/log_config.json");
    MVPRLog::Init();

    LOG_TRACE("its a trace msg.");
    LOG_DEBUG("its a debug msg.");
    LOG_INFO("its an info msg. %s", "ailee");
    LOG_WARN("its an warning msg. %d", 100);
    LOG_ERROR("its an error msg.");
    LOG_FATAL("its an fatal msg");

    MVPRLog::Stop();
}
