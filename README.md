# 基于boost::log库的二次次封装

# log_config.json配置文件说明
```json
{
  "log_filename": "MVPR_%Y%m%d%H%M%S.%N.log",
  "log_path": "./logs/",
  "log_level": "default",
  "log_rota_type": {
    "type": "default",
    "size": 32,
    "time_point": {
      "hour": 1,
      "minute": 2,
      "second": 3
    }
  },
  "is_console": false,
  "is_synchronize": false
}
```
- log_filename：日志文件名称，以模板形式表示，例如：xxxx_20220520113812_0.log
- log_path：日志文件保存路径
- log_level：日志保存级别，默认为所有级别都保存，可选：
  - default：默认无过滤器
  - trace
  - debug
  - info
  - warning
  - error
  - fatal
- log_rota：日志归档
  - type：日志归档方式
    - default：默认不归档
    - daily：按天归档
    - size：按文件大小归档
    - daily_size：按天和文件大小归档
  - size：日志文件大小
  - time_point：日志归档时间点
    - hour：时
    - minute：分
    - second：秒
- is_console：是否输出到终端
  - true：是
  - false：否
- is_synchronize：是否使用同步日志
  - true：同步日志
  - false：异步日志

# ERROR Solution
- [输出无日志级别](https://stackoverflow.com/questions/47918145/boost-log-severity-empty-in-the-log-message)
  - The problem is that you didn't add the severity level attribute. This attribute is normally provided by the logger, but you're using the logger_mt logger, which doesn't add any attributes and ignores the argument you provide to the BOOST_LOG_SEV macro. You should use severity_logger_mt or some other logger that provides support for severity levels. This logger will add the severity level attribute to every log record made through it and will set the level to the value you specify in the BOOST_LOG_SEV macro call.

# References
- [1] [基于Boost Log 开发的本地日志模块---SEED_LOG（一）](https://blog.csdn.net/ysf465639310/article/details/93497406)
- [2][rep: researchman/syslog](https://github.com/researchman/syslog)