#include "BaseGameManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"

/**
 * @brief サブシステム初期化処理
 * @details
 *  - ゲーム開始時刻を記録し、ログ出力を行います
 */
void UBaseGameManager::Initialize(FSubsystemCollectionBase& _collection)
{
    Super::Initialize(_collection);
    m_gameStartTime = FDateTime::UtcNow();
    UE_LOG(LogTemp, Log, TEXT("BaseGameManager initialized at %s"), *m_gameStartTime.ToString());
}

/**
 * @brief サブシステム終了処理
 * @details
 *  - 終了ログを出力します。必要に応じてセーブ処理などを追加可能です
 */
void UBaseGameManager::Deinitialize()
{
    UE_LOG(LogTemp, Log, TEXT("BaseGameManager deinitialized."));
    Super::Deinitialize();
}

/**
 * @brief 指定されたレベルをロードします
 * @param LevelName ロードするレベル名
 */
void UBaseGameManager::LoadLevel(const FString& _levelName)
{
    if (UWorld* world = GetWorld())
    {
        UE_LOG(LogTemp, Log, TEXT("Loading level: %s"), *_levelName);
        UGameplayStatics::OpenLevel(world, FName(*_levelName));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("BaseGameManager: Cannot load level, World is null."));
    }
}

/**
 * @brief ゲームを終了します
 * @param _bForceQuit 強制終了を行うかどうか
 */
void UBaseGameManager::QuitGame(bool _bForceQuit)
{
    if (UWorld* world = GetWorld())
    {
        APlayerController* PC = UGameplayStatics::GetPlayerController(world, 0);
        UKismetSystemLibrary::QuitGame(world, PC, EQuitPreference::Quit, _bForceQuit);
    }
}

/**
 * @brief 現在のプレイ時間（秒）を取得します
 * @return 経過時間（秒）
 */
float UBaseGameManager::GetElapsedPlayTime() const
{
    return (FDateTime::UtcNow() - m_gameStartTime).GetTotalSeconds();
}
