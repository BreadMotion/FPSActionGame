#include "SaveManager.h"

void FSaveManager::Initialize()
{
    m_localHandler = MakeUnique<FLocalSaveHandler>();
    m_remoteHandler = MakeUnique<FRemoteSaveHandler>();

    // ¡‚Íƒ[ƒJƒ‹‚Ì‚Ý—˜—p
    m_bUseRemote = false;
}

void FSaveManager::Shutdown()
{
    m_localHandler.Reset();
    m_remoteHandler.Reset();
}

void FSaveManager::SaveAll()
{
    if (m_bUseRemote)
    {
        m_remoteHandler->SaveData();
    }
    else
    {
        m_localHandler->SaveData();
    }
}

void FSaveManager::LoadAll()
{
    if (m_bUseRemote)
    {
        m_remoteHandler->LoadData();
    }
    else
    {
        m_localHandler->LoadData();
    }
}
