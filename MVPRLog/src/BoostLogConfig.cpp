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

int BoostLogConfig::LoadConfig(char *configFilePath) {
    std::ifstream jsonStrm(configFilePath, std::ios_base::in);

    boost::property_tree::ptree root;
    boost::property_tree::read_json(jsonStrm, root);

    /**
     * "log_filename": "MVPR_%Y%m%d%H%M%S_%N.log",
     * "log_path": "./logs/",
     * "log_level": "default",
     * "log_rota_type": "default",
     * "is_console": true,
     * "is_synchronize": true
     */
    this->m_logFilename = root.get<std::string>("log_filename");
    this->m_logPath = root.get<std::string>("log_path");
    this->m_logLevel = root.get<std::string>("log_level");
    this->m_logRotaType = root.get<std::string>("log_rota_type");
    this->m_is2Console = root.get<bool>("is_console");
    this->m_isSynchronize = root.get<bool>("is_synchronize");

    jsonStrm.close();

    return 0;
}
