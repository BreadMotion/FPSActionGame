#include "BaseGameManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "FPSSystem/BaseSystem.h"

void UBaseGameManager::InitGameManager()
{
	m_currentLevel = TEXT("None");
	UE_LOG(LogTemp, Log, TEXT("UBaseGameManager initialized."));
}

void UBaseGameManager::StartGameManager()
{
	if (UWorld* World = GetWorld())
	{
		m_currentLevel = UGameplayStatics::GetCurrentLevelName(World, true);
		UE_LOG(LogTemp, Log, TEXT("UBaseGameManager started at level: %s"), *m_currentLevel);
	}
}

void UBaseGameManager::BroadcastLevelChanged(const FString& _oldLevel, const FString& _newLevel)
{
	if (UGameInstance* GI = GetGameInstance())
	{
		const TArray<UGameInstanceSubsystem*> Subsystems = GI->GetSubsystemArrayCopy<UGameInstanceSubsystem>();
		for (UGameInstanceSubsystem* Subsystem : Subsystems)
		{
			if (UBaseSystem* System = Cast<UBaseSystem>(Subsystem))
			{
				System->OnLevelChanged(_oldLevel, _newLevel);
			}
		}
	}
}

void UBaseGameManager::BroadcastGameStateChanged(const FString& _stateName)
{
	if (UGameInstance* GI = GetGameInstance())
	{
		const TArray<UGameInstanceSubsystem*> Subsystems = GI->GetSubsystemArrayCopy<UGameInstanceSubsystem>();
		for (UGameInstanceSubsystem* Subsystem : Subsystems)
		{
			if (UBaseSystem* System = Cast<UBaseSystem>(Subsystem))
			{
				System->OnGameStateChanged(_stateName);
			}
		}
	}
}
