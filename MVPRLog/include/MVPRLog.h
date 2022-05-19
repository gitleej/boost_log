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

#include "AbstractLogger.h"
#include "AbstractLogConfig.h"

/**
 * @brief   日志接口类，单例模式
 */
class MVPRLog {
private:
//    void boostLogInit(const char * logPath);

    static MVPRLog*     _pInstance;                ///< 私有实例
    AbstractLogger*     m_logger = nullptr;        ///< 日志记录器
    AbstractLogConfig*  m_logConfig = nullptr;     ///< 日志配置
//    char*     m_logPath;                  ///< 日志保存文件夹

protected:
    /**
     * @brief   构造函数
     */
    MVPRLog();
//    MVPRLog(const char* logPath);

    /**
     * @brief   析构函数
     */
    ~MVPRLog();

public:
    MVPRLog(MVPRLog &other) = delete;
    void operator=(const MVPRLog&) = delete;
    static MVPRLog* GetInstance();
    static void Init();
//    static void Init(const char * logPath);

    // TODO: 其他业务逻辑
//    char * getLogPath();
};

#endif //BOOST_LOG_TEST_MVPRLOG_H
