//
// Created by AILEE on 2022/5/18.
//

#ifndef MVPR_LOG_BOOSTLOGCONFIG_H
#define MVPR_LOG_BOOSTLOGCONFIG_H

#include "AbstractLogConfig.h"

class BoostLogConfig : public AbstractLogConfig{
public:
    ~BoostLogConfig() override;

    int LoadConfig() override;

    int LoadConfig(const char *configFilePath) override;
};


#endif //MVPR_LOG_BOOSTLOGCONFIG_H
