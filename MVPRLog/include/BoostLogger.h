//
// Created by AILEE on 2022/5/18.
//

#ifndef BOOST_LOG_TEST_BOOSTLOGGER_H
#define BOOST_LOG_TEST_BOOSTLOGGER_H

#include "AbstractLogger.h"
#include "BoostLogConfig.h"

#include <fstream>
#include <iomanip>
#include <boost/log/core.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/core/null_deleter.hpp>

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;

class BoostLogger : public AbstractLogger {
public:
    ~BoostLogger() override;

    int Init(AbstractLogConfig &logConfig) override;

    void WriteLog() override;

    void Stop() override;
};


#endif //BOOST_LOG_TEST_BOOSTLOGGER_H
