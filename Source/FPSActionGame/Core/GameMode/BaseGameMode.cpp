#include "GameMode/BaseGameMode.h"
#include "GameState/BaseGameState.h"
#include "Core/BaseGameManager.h"
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

    CachedGameState = GetGameState<ABaseGameState>();

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
void ABaseGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);
    UE_LOG(LogTemp, Log, TEXT("Player joined: %s"), *NewPlayer->GetName());
}

/**
 * @brief プレイヤー退出時の処理。
 * @param Exiting 退出するプレイヤーのコントローラ。
 */
void ABaseGameMode::Logout(AController* Exiting)
{
    Super::Logout(Exiting);
    UE_LOG(LogTemp, Log, TEXT("Player left: %s"), *Exiting->GetName());
}
