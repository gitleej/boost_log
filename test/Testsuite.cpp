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
}
