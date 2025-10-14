#include "BaseGameManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "System/ProgressionSystem/ProgressionSystem.h"

/**
 * @brief ゲーム全体の初期化処理を行います。
 * @details
 * - ゲームインスタンスが生成されたタイミングで呼び出されます。
 * - サブシステム群の初期化はこの段階で Unreal によって自動的に行われます。
 * - 本関数では初期レベル名などの基本的なゲーム情報をセットアップします。
 *
 * @note `UGameInstance::Init()` のオーバーライドです。
 * @see OnStart()
 */
void UBaseGameManager::Init()
{
    Super::Init();
    m_currentLevel = TEXT("None");
}

/**
 * @brief ゲーム開始時の処理を行います。
 * @details
 * - 実行開始時に呼び出され、現在のレベル名を記録します。
 * - レベル遷移前後で状態を管理したい場合に利用できます。
 *
 * @note `UGameInstance::OnStart()` のオーバーライドです。
 * @see BroadcastLevelChanged()
 */
void UBaseGameManager::OnStart()
{
    Super::OnStart();
    m_currentLevel = UGameplayStatics::GetCurrentLevelName(this, true);
}

/**
 * @brief レベル遷移イベントを全てのサブシステムに通知します。
 * @param _oldLevelName 遷移前のレベル名。
 * @param _newLevelName 遷移後のレベル名。
 * @details
 * - `UBaseSystem` を継承した全てのサブシステムに対して `OnLevelChanged()` を呼び出します。
 * - 各サブシステムでレベル変更時の処理（例：データリロードやリセット）を実装できます。
 *
 * @see UBaseSystem::OnLevelChanged()
 * @see BroadcastGameStateChanged()
 */
void UBaseGameManager::BroadcastLevelChanged(const FString& _oldLevelName, const FString& _newLevelName)
{
    TArray<UGameInstanceSubsystem*> Subsystems = GetSubsystemArray<UGameInstanceSubsystem>();
    for (UGameInstanceSubsystem* Subsystem : Subsystems)
    {
        if (UBaseSystem* System = Cast<UBaseSystem>(Subsystem))
        {
            System->OnLevelChanged(_oldLevelName, _newLevelName);
        }
    }
}

/**
 * @brief ゲーム全体の状態変更を全てのサブシステムに通知します。
 * @param _stateName 変更後の状態名（例："Pause", "Resume", "GameOver" など）。
 * @details
 * - 各 `UBaseSystem` に対して `OnGameStateChanged()` を呼び出します。
 * - 各システムが独自の内部状態を更新したり、一時停止・再開処理を実装できます。
 *
 * @see UBaseSystem::OnGameStateChanged()
 * @see BroadcastLevelChanged()
 */
void UBaseGameManager::BroadcastGameStateChanged(const FString& _stateName)
{
    TArray<UGameInstanceSubsystem*> Subsystems = GetSubsystemArray<UGameInstanceSubsystem>();
    for (UGameInstanceSubsystem* Subsystem : Subsystems)
    {
        if (UBaseSystem* System = Cast<UBaseSystem>(Subsystem))
        {
            System->OnGameStateChanged(_stateName);
        }
    }
}
