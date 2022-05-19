//
// Created by nuc on 2022/5/11.
//

#include "../include/MVPRLog.h"
#include "BoostLogger.h"
#include "BoostLogConfig.h"

MVPRLog* MVPRLog::_pInstance{nullptr};

MVPRLog::MVPRLog() {}

//MVPRLog::MVPRLog(const char *logPath) {}

MVPRLog::~MVPRLog() = default;

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
    }
}

//void MVPRLog::Init(const char *logPath) {
//    if (nullptr == _pInstance) {
//        _pInstance = new MVPRLog(logPath);
//    }
//}

//char *MVPRLog::getLogPath() {
//    return m_logPath;
//}

//void MVPRLog::boostLogInit(const char *logPath) {
//    typedef sinks::synchronous_sink< sinks::text_ostream_backend > text_sink;
//    boost::shared_ptr< text_sink > sink = boost::make_shared< text_sink >();
//
//    // Add a stream to write log to
//    sink->locked_backend()->add_stream(
//            boost::make_shared< std::ofstream >("sample.log"));
//
//    // output to console
//    boost::shared_ptr< std::ostream > stream(&std::clog, boost::null_deleter());
//    sink->locked_backend()->add_stream(stream);
//
//    sink->set_formatter
//            (
//                    expr::stream
//                            // line id will be written in hex, 8-digits, zero-filled
//                            << std::hex << std::setw(8) << std::setfill('0') << expr::attr< unsigned int >("LineID")
//                            << ": <" << logging::trivial::severity
//                            << "> " << expr::smessage
//            );
//
//    // Register the sink in the logging core
//    logging::core::get()->add_sink(sink);
//
//    logging::add_common_attributes();
//}
