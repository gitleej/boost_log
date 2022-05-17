//#define BOOST_LOG_DYN_LINK 1

#include <iostream>
#include "MVPRLog.h"

int main() {
    MVPRLog::Init("./test_log_path");
//    fprintf(stderr, "Log Path: %s\n", MVPRLog::GetInstance()->getLogPath());
    fprintf(stderr, "Log Path: %s\n", GET_LOG_PATH());

//    init();
//
//    logging::add_common_attributes();

    using namespace logging::trivial;
    src::severity_logger< severity_level > lg;

    BOOST_LOG_SEV(lg, trace) << "A trace severity message";
    BOOST_LOG_SEV(lg, debug) << "A debug severity message";
    BOOST_LOG_SEV(lg, info) << "An informational severity message";
    BOOST_LOG_SEV(lg, warning) << "A warning severity message";
    BOOST_LOG_SEV(lg, error) << "An error severity message";
    BOOST_LOG_SEV(lg, fatal) << "A fatal severity message";

    return 0;
}
