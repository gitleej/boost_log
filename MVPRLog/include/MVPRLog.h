//
// Created by nuc on 2022/5/11.
//

#ifndef BOOST_LOG_TEST_MVPRLOG_H
#define BOOST_LOG_TEST_MVPRLOG_H

#ifdef WIN32
    #ifdef _WINDLL
        #define MVPR_LOG_API __declspeeec(dllexport)
    #else
        #define MVPR_LOG_API __declspeeec(dllimport)
    #endif
#elif LINUX
    #define MVPR_LOG_API
#endif

#define GET_LOG_PATH() MVPRLog::GetInstance()->getLogPath()

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

class MVPRLog {
private:
    void boostLogInit(const char * logPath);

    static MVPRLog* _pInstance;

protected:
    MVPRLog();
    MVPRLog(const char* logPath);
    ~MVPRLog();

    char*     m_logPath;      ///< 日志保存文件夹

public:
    MVPRLog(MVPRLog &other) = delete;
    void operator=(const MVPRLog&) = delete;
    static MVPRLog* GetInstance();
    static void Init();
    static void Init(const char * logPath);

    // TODO: 其他业务逻辑
    char * getLogPath();
};

#endif //BOOST_LOG_TEST_MVPRLOG_H
