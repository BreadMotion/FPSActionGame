#include "GameSystem.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "FPSSystem/BaseSystem.h"

/**
 * @brief Subsystem の初期化処理
 * @details
 * - すべての UBaseSystem を検出して登録します。
 * - 現在のレベル名を取得して保持します。
 */
void UGameSystem::Initialize(FSubsystemCollectionBase& _collection)
{
	Super::Initialize(_collection);
	UE_LOG(LogTemp, Log, TEXT("[BaseGameManager] Initialize() called"));
	InitializeAllSystems();

	// 現在のレベル名を登録
	if (UWorld* world = GetWorld())
	{
		m_currentLevel = world->GetMapName();
		UE_LOG(LogTemp, Log, TEXT("[BaseGameManager] Current level: %s"), *m_currentLevel);
	}
}

/**
 * @brief すべてのシステムを初期化する
 * @details
 * GameInstance に登録されている Subsystem のうち、
 * UBaseSystem を継承しているものを検出して登録します。
 */
void UGameSystem::InitializeAllSystems()
{
	if (UGameInstance* gi = GetGameInstance())
	{
		const TArray<UGameInstanceSubsystem*> subsystems = gi->GetSubsystemArrayCopy<UGameInstanceSubsystem>();
		for (UGameInstanceSubsystem* subsystem : subsystems)
		{
			if (UBaseSystem* baseSystem = Cast<UBaseSystem>(subsystem))
			{
				if (baseSystem != this) // 自身は除外
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
 * @brief レベル変更時の処理
 * @param _oldLevel 変更前のレベル名
 * @param _newLevel 変更後のレベル名
 * @details
 * レベル名を更新し、全てのシステムに OnLevelChanged イベントを通知します。
 */
void UGameSystem::HandleLevelChanged(const FString& _oldLevel, const FString& _newLevel)
{
	m_currentLevel = _newLevel;
	UE_LOG(LogTemp, Log, TEXT("[BaseGameManager] Level changed: %s -> %s"), *_oldLevel, *_newLevel);
	
	for (UBaseSystem* system : m_registeredSystems)
		if (system)
			system->OnLevelChanged(_oldLevel, _newLevel);
}

/**
 * @brief 登録されたすべてのシステムをシャットダウンする
 * @details
 * 各 UBaseSystem に "Shutdown" ステートを通知し、リストをクリアします。
 */
void UGameSystem::ShutdownAllSystems()
{
	for (UBaseSystem* system : m_registeredSystems)
		if (system)
			system->OnGameStateChanged(TEXT("Shutdown"));
	m_registeredSystems.Empty();
}

/**
 * @brief Subsystem の終了処理
 * @details
 * 終了時にすべてのシステムをシャットダウンし、クリーンアップします。
 */
void UGameSystem::Deinitialize()
{
	UE_LOG(LogTemp, Log, TEXT("[BaseGameManager] Deinitialize() called"));
	
	ShutdownAllSystems();
	Super::Deinitialize();
}
