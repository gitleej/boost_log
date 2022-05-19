//
// Created by AILEE on 2022/5/19.
//

#ifndef BOOST_LOG_TEST_TESTSUITE_H
#define BOOST_LOG_TEST_TESTSUITE_H

#include "../MVPRLog/include/AbstractLogConfig.h"
#include "../MVPRLog/include/BoostLogConfig.h"
#include "../MVPRLog/include/AbstractLogger.h"
#include "../MVPRLog/include/BoostLogger.h"

class Testsuite {
public:
    static void testLogConfig();
    static void testLogger();
};


#endif //BOOST_LOG_TEST_TESTSUITE_H
