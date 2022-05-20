//
// Created by AILEE on 2022/5/18.
//

#ifndef BOOST_LOG_TEST_BOOSTLOGGER_H
#define BOOST_LOG_TEST_BOOSTLOGGER_H

#include "AbstractLogger.h"
#include "BoostLogConfig.h"

#include <boost/log/core.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/async_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/phoenix.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sources/severity_logger.hpp>

#include <string>


namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;

BOOST_LOG_ATTRIBUTE_KEYWORD(process_id, "ProcessID", attrs::current_process_id::value_type )
BOOST_LOG_ATTRIBUTE_KEYWORD(thread_id, "ThreadID", attrs::current_thread_id::value_type )
BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", severity_levels)

/**
 * @brief   全局日志记录器
 */
BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(globalLogger, src::severity_logger_mt<severity_levels>)

class BoostLogger : public AbstractLogger {
public:
    ~BoostLogger() override;

    int Init(const AbstractLogConfig &logConfig) override;

    static void WriteLog(const char *filename,
                         const char *func,
                         int line,
                         severity_levels level,
                         const char *fmt, ...);

    void Stop() override;

private:
    /**
     * @brief   后端初始化啊啊
     * @param logConfig 日志配置文件
     * @return  初始化成功返回0，失败返回错误代码
     */
    int backendInit(const AbstractLogConfig &logConfig);

    static void write_header(boost::log::sinks::text_file_backend::stream_type& file);

    static void write_footer(boost::log::sinks::text_file_backend::stream_type& file);

    static attrs::current_process_id::value_type::native_type get_native_process_id(
            logging::value_ref<attrs::current_process_id::value_type, tag::process_id> const &pid);

    static attrs::current_thread_id::value_type::native_type get_native_thread_id(
            logging::value_ref<attrs::current_thread_id::value_type, tag::thread_id> const &tid);

    static std::string get_file_line(const char *filename, const char *func, const int &line);
};

#define LOG_TRACE(fmt,...)  BoostLogger::WriteLog(__FILE__, __FUNCTION__, __LINE__, trace, fmt, ##__VA_ARGS__)
#define LOG_DEBUG(fmt,...)  BoostLogger::WriteLog(__FILE__, __FUNCTION__, __LINE__, debug, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt,...)  BoostLogger::WriteLog(__FILE__, __FUNCTION__, __LINE__, info, fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt,...)  BoostLogger::WriteLog(__FILE__, __FUNCTION__, __LINE__, warning, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt,...)  BoostLogger::WriteLog(__FILE__, __FUNCTION__, __LINE__, error, fmt, ##__VA_ARGS__)
#define LOG_FATAL(fmt,...)  BoostLogger::WriteLog(__FILE__, __FUNCTION__, __LINE__, fatal, fmt, ##__VA_ARGS__)

#endif //BOOST_LOG_TEST_BOOSTLOGGER_H
