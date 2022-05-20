//
// Created by AILEE on 2022/5/18.
//

#ifndef BOOST_LOG_TEST_ABSTRACTLOGGER_H
#define BOOST_LOG_TEST_ABSTRACTLOGGER_H

#include "AbstractLogConfig.h"

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
                          severity_levels level,
                          const char* fmt, ...) {};

    /**
     * @brief   停止日志记录
     */
    virtual void Stop() = 0;

public:
    AbstractLogConfig *m_logConfig = nullptr;
};


#endif //BOOST_LOG_TEST_ABSTRACTLOGGER_H
