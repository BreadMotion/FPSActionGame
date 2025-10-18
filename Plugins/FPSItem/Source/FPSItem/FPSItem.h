#pragma once
#include "Modules/ModuleManager.h"

class FFPSItem : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
