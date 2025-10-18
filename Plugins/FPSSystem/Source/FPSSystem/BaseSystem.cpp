#include "BaseSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

/**
 * @brief ベースシステム初期化処理
 * @param _collection 利用可能なSubsystemのコレクション
 * @details
 * - ゲーム開始時にUTC時間を取得し、開始時間として記録する
 * - ゲーム全体の管理に使用する
 *
 * @note `UGameInstanceSubsystem::Initialize()` のオーバーライド
 */
void UBaseSystem::Initialize(FSubsystemCollectionBase& _collection)
{
	Super::Initialize(_collection);
	m_gameStartTime = FDateTime::UtcNow();
	UE_LOG(LogTemp, Log, TEXT("UBaseSystem initialized at %s"), *m_gameStartTime.ToString());
}

/**
 * @brief ベースシステム終了処理
 * @details
 * - システム終了時に呼ばれる
 * - 必要に応じて後処理を行う
 *
 * @note `UGameInstanceSubsystem::Deinitialize()` のオーバーライド
 */
void UBaseSystem::Deinitialize()
{
	UE_LOG(LogTemp, Log, TEXT("UBaseSystem deinitialized."));
	Super::Deinitialize();
}

/**
 * @brief レベル変更時の通知
 * @param _oldLevelName 変更前のレベル名
 * @param _newLevelName 変更後のレベル名
 * @details
 * - レベル切り替えの際に `UBaseGameManager` から呼ばれる
 * - レベル依存の初期化や終了処理を行うためにオーバーライド可能
 *
 * @virtual
 */
void UBaseSystem::OnLevelChanged(const FString& _oldLevelName, const FString& _newLevelName)
{
	UE_LOG(LogTemp, Log, TEXT("[BaseSystem] Level Changed: %s -> %s"), *_oldLevelName, *_newLevelName);
}

/**
 * @brief ゲーム状態変更時の通知
 * @param _stateName 状態名（例："Pause", "Resume", "GameOver"）
 * @details
 * - ゲーム状態の変化に伴う処理を行う
 * - `UBaseGameManager` から呼び出される
 *
 * @virtual
 */
void UBaseSystem::OnGameStateChanged(const FString& _stateName)
{
	UE_LOG(LogTemp, Log, TEXT("[BaseSystem] GameState Changed: %s"), *_stateName);
}

/**
 * @brief プレイ時間（秒）を取得する
 * @return プレイ時間（秒）
 * @details
 * - ゲーム開始時間からの経過秒数を返す
 * - Blueprintからも呼び出せる
 *
 * @note `FDateTime::UtcNow()` を使い正確な時間計測を行う
 */
float UBaseSystem::GetPlayTimeSeconds() const
{
	return (FDateTime::UtcNow() - m_gameStartTime).GetTotalSeconds();
}

/**
 * @brief セーブ処理
 * @details
 * - ゲームデータの保存処理の雛形
 * - 派生クラスで具体的な処理を実装する
 *
 * @virtual
 */
void UBaseSystem::SaveData()
{
	UE_LOG(LogTemp, Log, TEXT("UBaseSystem::SaveData() called. Implement your save logic here."));
}

/**
 * @brief ロード処理
 * @details
 * - ゲームデータの読み込み処理の雛形
 * - 派生クラスで具体的な処理を実装する
 *
 * @virtual
 */
void UBaseSystem::LoadData()
{
	UE_LOG(LogTemp, Log, TEXT("UBaseSystem::LoadData() called. Implement your load logic here."));
}

/**
 * @brief デバッグメッセージ出力
 * @param _message 出力したいメッセージ
 * @details
 * - 画面とログの両方にメッセージを表示する
 * - 開発時のデバッグ支援に利用可能
 *
 * @note `GEngine->AddOnScreenDebugMessage()` を使用
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
