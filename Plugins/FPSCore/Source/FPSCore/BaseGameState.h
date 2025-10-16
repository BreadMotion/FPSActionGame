#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BaseGameState.generated.h"

/**
 * @class ABaseGameState
 * @brief ゲームの進行状態を管理するゲームステートの基底クラス
 * @details
 * - スコアやゲームフェーズなどの進行状態を管理します。
 * - 全クライアントに同期され、ゲームの状態共有に使われます。
 * - `ABaseGameMode` と連携し、ゲーム進行を制御します。
 *
 * @see ABaseGameMode
 * @see UBaseGameManager
 */
UCLASS(Blueprintable)
class FPSCORE_API ABaseGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	/** @brief コンストラクタ */
	ABaseGameState();

	/** @brief ゲームのスコア */
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "GameState")
	int32 m_score;

	/** @brief ゲームの進行フェーズ。"Init"、"InGame"、"Result" など */
	UPROPERTY(ReplicatedUsing = OnRep_GamePhase, BlueprintReadOnly, Category = "GameState")
	FString m_currentPhase;

	/**
	 * @brief ゲームフェーズを変更する関数
	 * @param _newPhase 新しいゲームフェーズ
	 */
	UFUNCTION(BlueprintCallable, Category = "GameState")
	void SetGamePhase(const FString& _newPhase);

protected:
	/** @brief ゲームフェーズ変更時に呼ばれる通知関数（レプリケーション通知用） */
	UFUNCTION()
	void OnRep_GamePhase();

	/** @brief レプリケーション対象プロパティの登録 */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& _outLifetimeProps) const override;
};
