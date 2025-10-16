#pragma once
#include "CoreMinimal.h"
#include "FPSSystem/BaseSystem.h"
#include "BaseGameManager.generated.h"

/**
 * @class UBaseGameManager
 * @brief ゲーム全体の状態を管理するマネージャーSubsystem
 * @details
 * - UBaseSystemを拡張して、全Subsystemに対してブロードキャスト処理を行う。
 * - ゲーム全体の進行・レベル変更・状態変更を管理する。
 */
UCLASS(Blueprintable)
class FPSCORE_API UBaseGameManager : public UBaseSystem
{
	GENERATED_BODY()

public:
	/** ゲーム全体の初期化（Subsystem起動後に呼び出し） */
	UFUNCTION(BlueprintCallable, Category = "GameManager")
	void InitGameManager();

	/** ゲーム開始時処理 */
	UFUNCTION(BlueprintCallable, Category = "GameManager")
	void StartGameManager();

	/** レベル変更時にSubsystemへ通知 */
	UFUNCTION(BlueprintCallable, Category = "GameManager")
	void BroadcastLevelChanged(const FString& _oldLevel, const FString& _newLevel);

	/** ゲームステート変更時にSubsystemへ通知 */
	UFUNCTION(BlueprintCallable, Category = "GameManager")
	void BroadcastGameStateChanged(const FString& _stateName);

private:
	/** 現在のレベル名 */
	FString m_currentLevel;
};
