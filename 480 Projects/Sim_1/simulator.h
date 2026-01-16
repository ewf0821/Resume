#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "datatypes.h"
#include "configops.h"
#include "metadataops.h"
#include "OS_SimDriver.h"

void runSim(ConfigDataType *configPtr, OpCodeType *MetaDataMstrPrt);

#endif