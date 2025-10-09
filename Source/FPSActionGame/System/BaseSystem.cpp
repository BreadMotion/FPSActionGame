#include "BaseSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

/**
 * @brief サブシステム初期化処理
 * @details
 *  - ゲーム開始時刻を記録し、ログ出力を行います
 */
void UBaseSystem::Initialize(FSubsystemCollectionBase& _collection)
{
    Super::Initialize(_collection);
    m_gameStartTime = FDateTime::UtcNow();
    UE_LOG(LogTemp, Log, TEXT("UBaseSystem initialized at %s"), *m_gameStartTime.ToString());
}

/**
 * @brief サブシステム終了処理
 * @details
 *  - 終了ログを出力します。必要に応じてセーブ処理などを追加可能です
 */
void UBaseSystem::Deinitialize()
{
    UE_LOG(LogTemp, Log, TEXT("UBaseSystem  deinitialized."));
    Super::Deinitialize();
}

/**
 * @brief 現在のプレイ時間を取得します
 * @details
 *  - キャッシュしているゲーム開始時刻からの経過時間を秒単位で返します
 * @return 経過時間　(秒)
 */
float UBaseSystem::GetPlayTimeSeconds() const
{
    return (FDateTime::UtcNow() - m_gameStartTime).GetTotalSeconds();
}

/**
 * @brief セーブ処理
 * @details
 *  - SaveGameクラスを継承したオブジェクトを作り、セーブ処理を行います
 */
void UBaseSystem::SaveData()
{
    UE_LOG(LogTemp, Log, TEXT("UBaseSystem : SaveData() called. Implement your save logic here."));
}

/**
 * @brief ロード処理
 * @details
 *  - SaveGameオブジェクトをロードしてデータを復元します
 */
void UBaseSystem::LoadData()
{
    UE_LOG(LogTemp, Log, TEXT("UBaseSystem : LoadData() called. Implement your load logic here."));
}

/**
 * @brief デバッグ用ログ出力
 * @details
 *  - 指定したログを出力します。
 */
void UBaseSystem::PrintDebugMessage(const FString& _message) const
{
    if (GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("[Subsystem] %s"), *_message));
    UE_LOG(LogTemp, Log, TEXT("[Subsystem] %s"), *_message);
}
