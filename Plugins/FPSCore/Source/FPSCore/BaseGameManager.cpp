#include "BaseGameManager.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "FPSSystem/BaseSystem.h"

/**
 * @brief Subsystem 初期化時の処理。
 * @details
 * - 全 UBaseSystem を列挙し登録。
 * - 現在のレベル名を取得して記録します。
 */
void UBaseGameManager::Initialize(FSubsystemCollectionBase& _collection)
{
	Super::Initialize(_collection);
	UE_LOG(LogTemp, Log, TEXT("[BaseGameManager] Initialize() called"));
	InitializeAllSystems();

	// 最初のレベルを記録
	if (UWorld* world = GetWorld())
	{
		m_currentLevel = world->GetMapName();
		UE_LOG(LogTemp, Log, TEXT("[BaseGameManager] Current level: %s"), *m_currentLevel);
	}
}

/**
 * @brief すべてのシステムを初期化する。
 * @details
 * GameInstance 内の Subsystem を走査し、UBaseSystem を継承しているものを登録します。
 */
void UBaseGameManager::InitializeAllSystems()
{
	if (UGameInstance* gi = GetGameInstance())
	{
		const TArray<UGameInstanceSubsystem*> subsystems = gi->GetSubsystemArrayCopy<UGameInstanceSubsystem>();
		for (UGameInstanceSubsystem* subsystem : subsystems)
		{
			if (UBaseSystem* baseSystem = Cast<UBaseSystem>(subsystem))
			{
				if (baseSystem != this) // 自身を除外
				{
					m_registeredSystems.Add(baseSystem);
					baseSystem->PrintDebugMessage(TEXT("Registered in BaseGameManager"));
				}
			}
		}
	}

	UE_LOG(LogTemp, Log, TEXT("[BaseGameManager] %d systems registered."), m_registeredSystems.Num());
}

/**
 * @brief レベル変更時の処理。
 * @param OldLevel 変更前のレベル名。
 * @param NewLevel 変更後のレベル名。
 * @details
 * レベル名を更新し、全システムに OnLevelChanged イベントを通知します。
 */
void UBaseGameManager::HandleLevelChanged(const FString& _oldLevel, const FString& _newLevel)
{
	m_currentLevel = _newLevel;
	UE_LOG(LogTemp, Log, TEXT("[BaseGameManager] Level changed: %s -> %s"), *_oldLevel, *_newLevel);
	
	for (UBaseSystem* system : m_registeredSystems)
		if (system)
			system->OnLevelChanged(_oldLevel, _newLevel);
}

/**
 * @brief 登録されたすべてのシステムを終了処理する。
 * @details
 * 各 UBaseSystem に "Shutdown" ステートを通知してクリーンアップします。
 */
void UBaseGameManager::ShutdownAllSystems()
{
	for (UBaseSystem* system : m_registeredSystems)
		if (system)
			system->OnGameStateChanged(TEXT("Shutdown"));
	m_registeredSystems.Empty();
}

/**
 * @brief Subsystem 終了時の処理。
 * @details
 * 終了前に全システムのシャットダウンを行い、クリーンな状態に戻します。
 */
void UBaseGameManager::Deinitialize()
{
	UE_LOG(LogTemp, Log, TEXT("[BaseGameManager] Deinitialize() called"));
	
	ShutdownAllSystems();
	Super::Deinitialize();
}
