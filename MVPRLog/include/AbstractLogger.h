//
// Created by AILEE on 2022/5/18.
//

#ifndef MVPR_LOG_ABSTRACTLOGGER_H
#define MVPR_LOG_ABSTRACTLOGGER_H

#include "AbstractLogConfig.h"
#include <boost/log/trivial.hpp>

namespace logging = boost::log;

class AbstractLogger {
public:
    virtual ~AbstractLogger() = 0;
    /**
     * @brief   日志库初始化
     * @param logConfig 日志配置器
     * @return  返回初始化状态，成功为0，失败为错误代码
     */
    virtual int Init(const AbstractLogConfig &logConfig) = 0;

    /**
     * @brief   写日志
     */
    static void WriteLog(const char *filename,
                          const char *func,
                          int line,
                         logging::trivial::severity_level level,
                          const char* fmt, ...) {};

    virtual void WriteLog(const logging::trivial::severity_level &level,
                         const char* message) = 0;

    /**
     * @brief   停止日志记录
     */
    virtual void Stop() = 0;

public:
    AbstractLogConfig *m_logConfig = nullptr;
};


#endif //MVPR_LOG_ABSTRACTLOGGER_H
