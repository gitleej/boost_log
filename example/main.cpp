//#define BOOST_LOG_DYN_LINK 1

#include <iostream>
#include "MVPRLog.h"

int main() {
    MVPRLog::Init("../conf/log_config.json");
    LOG_TRACE("its a trace msg.");
    LOG_DEBUG("its a debug msg.");
    LOG_INFO("its an info msg. %s", "ailee");
    LOG_WARN("its an warning msg. %d", 100);
    LOG_ERROR("its an error msg.");
    LOG_FATAL("its an fatal msg");
    MVPRLog::Stop();
    return 0;
}
