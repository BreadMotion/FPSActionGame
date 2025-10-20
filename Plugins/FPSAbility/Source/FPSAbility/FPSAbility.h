#pragma once
#include "Modules/ModuleManager.h"

class FFPSAbility : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
