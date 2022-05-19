//
// Created by AILEE on 2022/5/18.
//

#ifndef BOOST_LOG_TEST_ABSTRACTLOGCONFIG_H
#define BOOST_LOG_TEST_ABSTRACTLOGCONFIG_H

#include <string>

/**
 * @brief   抽象日志配置类
 */
class AbstractLogConfig {
public:
    virtual ~AbstractLogConfig() = 0;
    /**
     * @brief   加载日志配置文件
     * @return  返回加载状态值，成功返回0，失败返回错误代码。
     */
    virtual int LoadConfig() = 0;

    /**
     * @brief   加载日志配置文件
     * @param configFilePath 配置文件路径
     * @return  返回加载状态值，成功返回0，失败返回错误代码。
     */
    virtual int LoadConfig(char* configFilePath) = 0;

public:
    std::string         m_logFilename;          ///< 日志文件名称
    std::string         m_logPath;              ///< 日志存储路径
    std::string         m_logLevel;             ///< 日志存储级别
    std::string         m_logRotaType;          ///< 日志归档方式
    bool                m_isSynchronize;        ///< 是否同步
    bool                m_is2Console;           ///< 是否输出到控制台
};


#endif //BOOST_LOG_TEST_ABSTRACTLOGCONFIG_H
