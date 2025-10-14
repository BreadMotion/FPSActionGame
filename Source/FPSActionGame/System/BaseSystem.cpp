#include "BaseSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

/**
 * @brief サブシステムの初期化処理。
 * @param _collection 初期化対象のSubsystemコレクション。
 * @details
 * - ゲーム開始時刻（UTC）を記録し、ログ出力を行います。
 * - ゲーム全体で一度だけ呼ばれる初期化処理です。
 *
 * @note `UGameInstanceSubsystem::Initialize()` のオーバーライドです。
 */
void UBaseSystem::Initialize(FSubsystemCollectionBase& _collection)
{
    Super::Initialize(_collection);
    m_gameStartTime = FDateTime::UtcNow();
    UE_LOG(LogTemp, Log, TEXT("UBaseSystem initialized at %s"), *m_gameStartTime.ToString());
}

/**
 * @brief サブシステム終了処理。
 * @details
 * - システム終了時またはゲーム終了時に呼ばれます。
 * - 終了ログを出力し、必要に応じてセーブやリソース開放を行うことができます。
 *
 * @note `UGameInstanceSubsystem::Deinitialize()` のオーバーライドです。
 */
void UBaseSystem::Deinitialize()
{
    UE_LOG(LogTemp, Log, TEXT("UBaseSystem deinitialized."));
    Super::Deinitialize();
}

/**
 * @brief レベル遷移イベント。
 * @param OldLevelName 遷移前のレベル名。
 * @param NewLevelName 遷移後のレベル名。
 * @details
 * - レベルが変更された際に `UBaseGameManager` から呼び出されます。
 * - 派生クラスでオーバーライドして、レベルごとの初期化・終了処理を実装できます。
 *
 * @virtual
 */
void UBaseSystem::OnLevelChanged(const FString& OldLevelName, const FString& NewLevelName)
{
    // 派生クラスで実装
}

/**
 * @brief ゲームの再生状態通知イベント。
 * @param StateName 状態名（例："Pause"、"Resume"、"GameOver"など）。
 * @details
 * - ゲーム状態が変更された際に `UBaseGameManager` から呼び出されます。
 * - 状態に応じた挙動変更（例：一時停止、リソース調整など）を派生クラスで実装します。
 *
 * @virtual
 */
void UBaseSystem::OnGameStateChanged(const FString& StateName)
{
    // デフォルト空実装
}

/**
 * @brief 現在のプレイ時間を取得します。
 * @return ゲーム開始からの経過時間（秒単位）。
 * @details
 * - `m_gameStartTime` から現在までの経過時間を計算して返します。
 * - Blueprintからも呼び出し可能です。
 *
 * @note `FDateTime::UtcNow()` を使用しており、システム時間ベースです。
 */
float UBaseSystem::GetPlayTimeSeconds() const
{
    return (FDateTime::UtcNow() - m_gameStartTime).GetTotalSeconds();
}

/**
 * @brief セーブデータ保存処理。
 * @details
 * - 派生クラスでセーブ処理を実装してください。
 * - ここではデフォルトとしてログ出力のみ行います。
 *
 * @virtual
 */
void UBaseSystem::SaveData()
{
    UE_LOG(LogTemp, Log, TEXT("UBaseSystem::SaveData() called. Implement your save logic here."));
}

/**
 * @brief セーブデータ読み込み処理。
 * @details
 * - 派生クラスでロード処理を実装してください。
 * - ここではデフォルトとしてログ出力のみ行います。
 *
 * @virtual
 */
void UBaseSystem::LoadData()
{
    UE_LOG(LogTemp, Log, TEXT("UBaseSystem::LoadData() called. Implement your load logic here."));
}

/**
 * @brief デバッグ用メッセージ出力。
 * @param _message 出力する文字列。
 * @details
 * - 画面上およびログにデバッグメッセージを出力します。
 * - 画面出力は2秒間表示されます。
 *
 * @note `GEngine->AddOnScreenDebugMessage()` を使用しています。
 * @see UE_LOG
 */
void UBaseSystem::PrintDebugMessage(const FString& _message) const
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green,
            FString::Printf(TEXT("[Subsystem] %s"), *_message));
    }

    UE_LOG(LogTemp, Log, TEXT("[Subsystem] %s"), *_message);
}
