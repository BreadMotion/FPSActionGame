#include "BaseGameMode.h"
#include "BaseGameState.h"
#include "FPSSystem/BaseSystem.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

/**
 * @brief デフォルトコンストラクタ
 * @details
 * - デフォルトで使用する GameState クラスを設定します。
 */
ABaseGameMode::ABaseGameMode()
{
	// BaseGameState を使用（継承先で差し替え可能）
	GameStateClass = ABaseGameState::StaticClass();
	UE_LOG(LogTemp, Log, TEXT("[BaseGameMode] Constructed (%s)"), *GetName());
}

/**
 * @brief ゲーム開始時の処理
 * @details
 * - 親クラスの StartPlay() を呼び出した後に、
 * - 現在の GameState をキャッシュします。
 */
void ABaseGameMode::StartPlay()
{
	Super::StartPlay();

	m_cachedGameState = Cast<ABaseGameState>(GameState);
	if (m_cachedGameState)
		UE_LOG(LogTemp, Log, TEXT("[BaseGameMode] Cached GameState: %s"), *m_cachedGameState->GetName());

	UWorld* world = GetWorld();
	UGameInstance* gi = world->GetGameInstance();
	if (world && gi)
	{
		const TArray<UGameInstanceSubsystem*> subsystems = gi->GetSubsystemArrayCopy<UGameInstanceSubsystem>();
		for (UGameInstanceSubsystem* subsystem : subsystems)
		{
			if (UBaseSystem* baseSystem = Cast<UBaseSystem>(subsystem))
			{
				baseSystem->PrintDebugMessage(TEXT("Registered in BaseGameManager"));
			}
		}

		UE_LOG(LogTemp, Warning, TEXT("[BaseGameMode] Success to GameInstance setup."));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("[BaseGameMode] Failed to GameInstance setup."));
}

/**
 * @brief プレイヤーがログインした際の処理
 * @param _newPlayer 新しくログインしたプレイヤーのコントローラー
 * @details
 * - 通常はプレイヤーの初期化処理や UI 呼び出しなどを行います。
 * - 現状はログを出力するのみです。
 */
void ABaseGameMode::PostLogin(APlayerController* _newPlayer)
{
	Super::PostLogin(_newPlayer);

	if (!_newPlayer) return;
	UE_LOG(LogTemp, Log, TEXT("[BaseGameMode] Player joined: %s"), *_newPlayer->GetName());

	// GameManager への通知などが必要ならここに追加予定
}

/**
 * @brief プレイヤーがログアウトした際の処理
 * @param _exiting ログアウトするプレイヤーのコントローラー
 * @details
 * - 通常はプレイヤーのクリーンアップ処理を実施します。
 * - 現状はログを出力するのみです。
 */
void ABaseGameMode::Logout(AController* _exiting)
{
	Super::Logout(_exiting);

	if (!_exiting) return;
	UE_LOG(LogTemp, Log, TEXT("[BaseGameMode] Player exited: %s"), *_exiting->GetName());

	// 必要に応じて GameManager にも通知可能
}
