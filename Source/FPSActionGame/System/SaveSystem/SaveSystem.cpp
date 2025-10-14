#include "SaveSystem.h"
#include "Engine/Engine.h"

void USaveSystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    m_saveManager = MakeUnique<FSaveManager>();
    m_saveManager->Initialize();
}

void USaveSystem::Deinitialize()
{
    if (m_saveManager.IsValid())
    {
        m_saveManager->Shutdown();
        m_saveManager.Reset();
    }

    Super::Deinitialize();
}

void USaveSystem::SaveAll()
{
    if (m_saveManager.IsValid())
    {
        m_saveManager->SaveAll();
    }
}

void USaveSystem::LoadAll()
{
    if (m_saveManager.IsValid())
    {
        m_saveManager->LoadAll();
    }
}
