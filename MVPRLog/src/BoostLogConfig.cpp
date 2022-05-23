//
// Created by AILEE on 2022/5/18.
//

#include "BoostLogConfig.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <fstream>

BoostLogConfig::~BoostLogConfig() = default;

int BoostLogConfig::LoadConfig() {
    const char* configFilePath = "./conf/log_config.json";

    int ret = 0;
    ret = this->LoadConfig((char *)configFilePath);

    return ret;
}

int BoostLogConfig::LoadConfig(const char *configFilePath) {
    std::ifstream jsonStrm(configFilePath, std::ios_base::in);

    boost::property_tree::ptree root;
    boost::property_tree::read_json(jsonStrm, root);

    /**
     * {
     *   "log_filename": "MVPR_%Y%m%d%H%M%S.%N.log",
     *   "log_path": "./logs/",
     *   "log_level": "default",
     *   "log_rota": {
     *     "type": "default",
     *     "size": 32,
     *     "time_point": {
     *       "hour": 0,
     *       "minute": 0,
     *       "second": 0
     *      }
     *    },
     *    "is_console": false,
     *    "is_synchronize": false
     *  }
     */
    this->m_logFilename = root.get<std::string>("log_filename");
    this->m_logPath = root.get<std::string>("log_path");
    this->m_logLevel = root.get<std::string>("log_level");
    boost::property_tree::ptree rota = root.get_child("log_rota");
    this->m_logRotaType = rota.get<std::string>("type");
    this->m_logRotaSize = rota.get<unsigned int>("size") * 1024 * 1024;
    boost::property_tree::ptree rotaTimePointObj = rota.get_child("time_point");
    this->m_logRotaTimePoint.hour = rotaTimePointObj.get<unsigned char >("hour");
    this->m_logRotaTimePoint.minute = rotaTimePointObj.get<unsigned char >("minute");
    this->m_logRotaTimePoint.second = rotaTimePointObj.get<unsigned char >("second");
    this->m_is2Console = root.get<bool>("is_console");
    this->m_isSynchronize = root.get<bool>("is_synchronize");

    jsonStrm.close();

    return 0;
}
