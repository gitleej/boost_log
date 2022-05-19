//
// Created by AILEE on 2022/5/18.
//

#ifndef BOOST_LOG_TEST_BOOSTLOGCONFIG_H
#define BOOST_LOG_TEST_BOOSTLOGCONFIG_H

#include "AbstractLogConfig.h"

class BoostLogConfig : public AbstractLogConfig{
public:
    ~BoostLogConfig() override;

    int LoadConfig() override;

    int LoadConfig(char *configFilePath) override;
};


#endif //BOOST_LOG_TEST_BOOSTLOGCONFIG_H
