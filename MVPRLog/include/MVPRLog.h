//
// Created by nuc on 2022/5/11.
//

#ifndef MVPR_LOG_MVPRLOG_H
#define MVPR_LOG_MVPRLOG_H

#include "common.h"
#include "AbstractLogger.h"
#include "AbstractLogConfig.h"

/**
 * @brief   日志接口类，单例模式
 */
class MVPRLog {
private:
    static MVPRLog*     _pInstance;                 ///< 私有实例
    AbstractLogger*     m_logger = nullptr;         ///< 日志记录器

    AbstractLogConfig*  m_logConfig = nullptr;      ///< 日志配置

protected:
    /**
     * @brief   构造函数
     */
    MVPRLog();

    /**
     * @brief   析构函数
     */
    ~MVPRLog();

public:
    MVPRLog(MVPRLog &other) = delete;
    void operator=(const MVPRLog&) = delete;
    /**
     * @brief   获取日志类实例
     * @return  日志类实例对象
     */
    static MVPRLog* GetInstance();

    /**
     * @brief   使用默认配置文件路径初始化日志类实例
     */
    static void Init();

    /**
     * @brief   使用用户自定义日志配置文件路径初始化日志类实例
     * @param configFilePath 日志配置文件路径
     */
    static void Init(const char * configFilePath);

    /**
     * @brief   写日志
     * @param filename  源文件名
     * @param func      函数名
     * @param line      行号
     * @param level     日志严重级别
     * @param fmt       可选参数
     * @param ...
     */
    static void WriteLog(const char *filename,
                         const char *func,
                         int line,
                         mvpr::severity_levels level,
                         const char *fmt, ...);

    /**
     * @brief   停止日志记录
     */
    static void Stop();

private:
    /**
     * @brief   从默认日志配置文件路径加载日志配置参数
     */
    static void LoadConfig();

    /**
     * @brief   从指定路径加载日志配置参数
     * @param configFilePath 日志配置文件路径
     */
    static void LoadConfig(const char * configFilePath);
};

#define LOG_TRACE(fmt,...)  MVPRLog::GetInstance()->WriteLog(__FILE__, __FUNCTION__, __LINE__, mvpr::trace, fmt, ##__VA_ARGS__)
#define LOG_DEBUG(fmt,...)  MVPRLog::GetInstance()->WriteLog(__FILE__, __FUNCTION__, __LINE__, mvpr::debug, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt,...)  MVPRLog::GetInstance()->WriteLog(__FILE__, __FUNCTION__, __LINE__, mvpr::info, fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt,...)  MVPRLog::GetInstance()->WriteLog(__FILE__, __FUNCTION__, __LINE__, mvpr::warning, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt,...)  MVPRLog::GetInstance()->WriteLog(__FILE__, __FUNCTION__, __LINE__, mvpr::error, fmt, ##__VA_ARGS__)
#define LOG_FATAL(fmt,...)  MVPRLog::GetInstance()->WriteLog(__FILE__, __FUNCTION__, __LINE__, mvpr::fatal, fmt, ##__VA_ARGS__)

#endif //MVPR_LOG_MVPRLOG_H
