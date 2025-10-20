#pragma once
#include "Modules/ModuleManager.h"

class FFPSInterface : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
