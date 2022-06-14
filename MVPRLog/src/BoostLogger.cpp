//
// Created by AILEE on 2022/5/18.
//

#include "BoostLogger.h"

#include <fstream>

#include <boost/log/core/core.hpp>
#include <boost/log/expressions/formatters/date_time.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/trivial.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <fstream>
#include <ostream>

typedef sinks::synchronous_sink< sinks::text_ostream_backend > syn_stream_sink_t;
typedef sinks::synchronous_sink<sinks::text_file_backend> syn_file_sink_t;
typedef sinks::asynchronous_sink< sinks::text_ostream_backend > asyn_stream_sink_t;
typedef sinks::asynchronous_sink<sinks::text_file_backend> asyn_file_sink_t;

template< typename CharT, typename TraitsT >
inline std::basic_ostream< CharT, TraitsT >& operator<< (
        std::basic_ostream< CharT, TraitsT >& strm, severity_levels lvl)
{
    static const char* const str[] =
            {
                    "trace",
                    "debug",
                    "info",
                    "warning",
                    "error",
                    "fatal"
            };
    if (static_cast<std::size_t>(lvl) < (sizeof(str) / sizeof(*str)))
        strm << str[lvl];
    else
        strm << static_cast<int>(lvl);
    return strm;
}

void coloring_formatter(
        logging::record_view const& rec, logging::formatting_ostream& strm)
{
    auto severity = rec[logging::trivial::severity];
    if (severity)
    {
        // Set the color
        switch (severity.get())
        {
            case logging::trivial::severity_level::info:
                strm << "\033[32m";
                break;
            case logging::trivial::severity_level::warning:
                strm << "\033[33m";
                break;
            case logging::trivial::severity_level::error:
            case logging::trivial::severity_level::fatal:
                strm << "\033[31m";
                break;
            default:
                break;
        }
    }

    // Format the message here...
    strm << rec[logging::expressions::smessage];

    if (severity)
    {
        // Restore the default color
        strm << "\033[0m";
    }
}

BoostLogger::~BoostLogger() = default;

int BoostLogger::Init(const AbstractLogConfig &logConfig) {
    this->m_logConfig = (AbstractLogConfig*) &logConfig;

    if (logConfig.m_isSynchronize) {    // 同步日志
        this->backendInit(logConfig);
    } else {    // 异步日志
        this->backendInit(logConfig);
    }

    return 0;
}

void BoostLogger::WriteLog(const char *filename, const char *func, int line, severity_levels level, const char *fmt, ...) {
    va_list al;
    va_start(al, fmt);
    char *buffer = new char[1024];
    memset(buffer, 0, 1024);
//    vsnprintf(buffer, 1024, 1023, fmt, al);
    vsnprintf(buffer, 1024, fmt, al);
    std::string file = get_file_line(filename, func, line);
    std::string msg = buffer;
    src::severity_logger_mt<severity_levels> &lg = globalLogger::get();
    BOOST_LOG_SEV(lg, level) << file << ": " << msg.c_str();
}

void BoostLogger::WriteLog(const severity_levels &level, const char* message) {
    src::severity_logger_mt<severity_levels> &lg = globalLogger::get();
    BOOST_LOG_SEV(lg, level) << message;
}

void BoostLogger::Stop() {
    if (!this->m_logConfig->m_isSynchronize) {
        boost::shared_ptr<logging::core> core = logging::core::get();
//        core->remove_all_sinks();
        core->flush();
        core.reset();
    }
}

int BoostLogger::backendInit(const AbstractLogConfig &logConfig) {
    // 获取日志核心
    boost::shared_ptr<logging::core> core = logging::core::get();

    // 创建文本文件后端
    boost::shared_ptr<sinks::text_file_backend> text_file_backend =
            boost::make_shared<sinks::text_file_backend>();
    // 设置日志文件名
    text_file_backend->set_file_name_pattern(logConfig.m_logPath + logConfig.m_logFilename);
    // 设置日志归档模式
    if (logConfig.m_logRotaType == "daily") {
        text_file_backend->set_time_based_rotation(sinks::file::rotation_at_time_point(
                logConfig.m_logRotaTimePoint.hour,
                logConfig.m_logRotaTimePoint.minute,
                logConfig.m_logRotaTimePoint.second));
    } else if (logConfig.m_logRotaType == "size") {
        text_file_backend->set_rotation_size(logConfig.m_logRotaSize);
    } else if (logConfig.m_logRotaType == "daily_size") {
        text_file_backend->set_time_based_rotation(sinks::file::rotation_at_time_point(
                logConfig.m_logRotaTimePoint.hour,
                logConfig.m_logRotaTimePoint.minute,
                logConfig.m_logRotaTimePoint.second));
        text_file_backend->set_rotation_size(logConfig.m_logRotaSize);
    }

    text_file_backend->set_open_handler(&(BoostLogger::write_header));
    text_file_backend->set_close_handler(&(BoostLogger::write_footer));

    // 设置自动刷新
    text_file_backend->auto_flush(true);

    if (logConfig.m_isSynchronize) {
        boost::shared_ptr<syn_file_sink_t> text_sink(new syn_file_sink_t(text_file_backend));
        text_sink->set_formatter(
                expr::format("[%1%] <%2%:%3%> [%4%]: %5%")
                % expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
                % boost::phoenix::bind(&BoostLogger::get_native_process_id, process_id.or_none())
                % boost::phoenix::bind(&BoostLogger::get_native_thread_id, thread_id.or_none())
                % expr::attr<severity_levels>("Severity")
                % expr::smessage
                );
        // 日志保留级别
        if (logConfig.m_logLevel == "trace") {
            text_sink->set_filter(expr::attr< severity_levels >("Severity") >= trace);
        } else if (logConfig.m_logLevel == "debug"){
            text_sink->set_filter(expr::attr< severity_levels >("Severity") >= debug);
        } else if (logConfig.m_logLevel == "info"){
            text_sink->set_filter(expr::attr< severity_levels >("Severity") >= info);
        } else if (logConfig.m_logLevel == "warning"){
            text_sink->set_filter(expr::attr< severity_levels >("Severity") >= warning);
        } else if (logConfig.m_logLevel == "error"){
            text_sink->set_filter(expr::attr< severity_levels >("Severity") >= error);
        }else if (logConfig.m_logLevel == "fatal"){
            text_sink->set_filter(expr::attr< severity_levels >("Severity") >= fatal);
        }

        core->add_sink(text_sink);
    } else {
        boost::shared_ptr<asyn_file_sink_t> text_sink(new asyn_file_sink_t (text_file_backend));
        text_sink->set_formatter(
                expr::format("[%1%] <%2%:%3%> [%4%]: %5%")
                % expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
                % boost::phoenix::bind(&BoostLogger::get_native_process_id, process_id.or_none())
                % boost::phoenix::bind(&BoostLogger::get_native_thread_id, thread_id.or_none())
                % expr::attr<severity_levels>("Severity")
                % expr::smessage
        );
        // 日志保留级别
        if (logConfig.m_logLevel == "trace") {
            text_sink->set_filter(expr::attr< severity_levels >("Severity") >= trace);
        } else if (logConfig.m_logLevel == "debug"){
            text_sink->set_filter(expr::attr< severity_levels >("Severity") >= debug);
        } else if (logConfig.m_logLevel == "info"){
            text_sink->set_filter(expr::attr< severity_levels >("Severity") >= info);
        } else if (logConfig.m_logLevel == "warning"){
            text_sink->set_filter(expr::attr< severity_levels >("Severity") >= warning);
        } else if (logConfig.m_logLevel == "error"){
            text_sink->set_filter(expr::attr< severity_levels >("Severity") >= error);
        }else if (logConfig.m_logLevel == "fatal"){
            text_sink->set_filter(expr::attr< severity_levels >("Severity") >= fatal);
        }

        core->add_sink(text_sink);
    }

    if (logConfig.m_is2Console) {
        // 创建字符串流后端
        boost::shared_ptr<sinks::text_ostream_backend> text_stream_backend =
                boost::make_shared<sinks::text_ostream_backend>();
        text_stream_backend->add_stream(boost::shared_ptr<std::ostream>(&std::clog, boost::null_deleter()));
        // 设置自动刷新
        text_stream_backend->auto_flush(true);

        // 同步或异步日志
        if (logConfig.m_isSynchronize) {
            boost::shared_ptr<syn_stream_sink_t> stream_sink(new syn_stream_sink_t (text_stream_backend));
            stream_sink->set_formatter(
                    expr::format("[%1%] <%2%:%3%> [%4%]: %5%")
                    % expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
                    % boost::phoenix::bind(&BoostLogger::get_native_process_id, process_id.or_none())
                    % boost::phoenix::bind(&BoostLogger::get_native_thread_id, thread_id.or_none())
                    % expr::attr<severity_levels>("Severity")
                    % expr::smessage
                    );
//            stream_sink->set_formatter(& coloring_formatter);
            core->add_sink(stream_sink);
        } else {
            boost::shared_ptr<asyn_stream_sink_t> stream_sink(new asyn_stream_sink_t (text_stream_backend));
            stream_sink->set_formatter(
                    expr::format("[%1%] <%2%:%3%> [%4%]: %5%")
                    % expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
                    % boost::phoenix::bind(&BoostLogger::get_native_process_id, process_id.or_none())
                    % boost::phoenix::bind(&BoostLogger::get_native_thread_id, thread_id.or_none())
                    % expr::attr<severity_levels>("Severity")
                    % expr::smessage
                    );
//            stream_sink->set_formatter(& coloring_formatter);
            core->add_sink(stream_sink);
        }
    }

    logging::add_common_attributes();
    return 0;
}

void BoostLogger::write_header(sinks::text_file_backend::stream_type &file) {
    file << "<?xml version=\"1.0\"?>\n<log>\n";
}

void BoostLogger::write_footer(sinks::text_file_backend::stream_type &file) {
    file << "</log>\n";
}

attrs::current_process_id::value_type::native_type BoostLogger::get_native_process_id(
        const logging::value_ref<attrs::current_process_id::value_type, tag::process_id> &pid) {
    if (pid) {
        return pid->native_id();
    }
    return 0;
}

attrs::current_thread_id::value_type::native_type
BoostLogger::get_native_thread_id(const logging::value_ref<attrs::current_thread_id::value_type, tag::thread_id> &tid) {
    if (tid) {
        return tid->native_id();
    }
    return 0;
}
