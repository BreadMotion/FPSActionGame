#pragma once
#include "Modules/ModuleManager.h"

class FFPSUtility : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
