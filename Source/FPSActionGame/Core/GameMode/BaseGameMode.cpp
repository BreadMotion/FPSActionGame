#include "GameMode/BaseGameMode.h"
#include "GameState/BaseGameState.h"
#include "GameInstance/BaseGameManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

/**
 * @brief コンストラクタ。
 * @details
 * - `GameStateClass` に `ABaseGameState` を設定します。
 */
ABaseGameMode::ABaseGameMode()
{
    GameStateClass = ABaseGameState::StaticClass();
}

/**
 * @brief ゲーム開始時処理。
 * @details
 * - `ABaseGameState` をキャッシュし、初期フェーズを設定します。
 * - `UBaseGameManager` へゲーム開始イベントを通知します。
 */
void ABaseGameMode::StartPlay()
{
    Super::StartPlay();

    m_cachedGameState = GetGameState<ABaseGameState>();

    if (UBaseGameManager* GameManager = Cast<UBaseGameManager>(GetGameInstance()))
    {
        GameManager->BroadcastGameStateChanged(TEXT("StartPlay"));
    }

    UE_LOG(LogTemp, Log, TEXT("GameMode: StartPlay called."));
}

/**
 * @brief プレイヤー参加時の処理。
 * @param NewPlayer 参加したプレイヤーのコントローラ。
 */
void ABaseGameMode::PostLogin(APlayerController* _newPlayer)
{
    Super::PostLogin(_newPlayer);
    UE_LOG(LogTemp, Log, TEXT("Player joined: %s"), *_newPlayer->GetName());
}

/**
 * @brief プレイヤー退出時の処理。
 * @param Exiting 退出するプレイヤーのコントローラ。
 */
void ABaseGameMode::Logout(AController* _exiting)
{
    Super::Logout(_exiting);
    UE_LOG(LogTemp, Log, TEXT("Player left: %s"), *_exiting->GetName());
}
