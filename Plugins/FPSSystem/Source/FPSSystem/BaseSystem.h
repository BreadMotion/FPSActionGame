#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BaseSystem.generated.h"

/**
 * @class UBaseSystem
 * @brief ゲーム全体のシステムを管理する基底クラス
 * @details
 * - ゲーム全体の管理（セーブデータなど）を行う
 * - `UGameInstanceSubsystem` を継承しているのでゲームインスタンスに依存する
 * - 他Subsystem（例: USaveSystem）と連携可能
 */
UCLASS(Blueprintable)
class FPSSYSTEM_API UBaseSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	/**
	 * @class UBaseSystem
	 * @brief ゲーム全体のシステムを管理する基底クラス
	 * @details
	 * - ゲーム全体の管理（セーブデータなど）を行う
	 * - `UGameInstanceSubsystem` を継承しているのでゲームインスタンスに依存する
	 * - 他Subsystem（例: USaveSystem）と連携可能
	 */
	virtual void Initialize(FSubsystemCollectionBase& _collection) override;

	/**
	 * @brief 終了処理
	 * @details
	 * - ゲームの終了時に呼ばれる
	 * - 基底クラスの `UGameInstanceSubsystem::Deinitialize()` をオーバーライド
	 */
	virtual void Deinitialize() override;

	/**
	 * @brief レベル変更時に呼ばれる関数
	 * @param _oldLevelName 変更前のレベル名
	 * @param _newLevelName 変更後のレベル名
	 * @details
	 * - `UBaseGameManager` から呼ばれ、レベル変更に対応する
	 * - 各Subsystemがレベル変更に伴う処理をここで行う
	 */
	virtual void OnLevelChanged(const FString& _oldLevelName, const FString& _newLevelName);

	/**
	 * @brief ゲーム状態変更時に呼ばれる関数
	 * @param _stateName 状態名（例: "Pause", "Resume", "GameOver"）
	 * @details
	 * - `UBaseGameManager::BroadcastGameStateChanged()` から通知される
	 * - 状態に応じた処理を行う
	 */
	virtual void OnGameStateChanged(const FString& _stateName);

protected:
	/**
	 * @brief ゲーム開始時間
	 * @details
	 * - `Initialize()` 時に設定される
	 * - プレイ時間計測に使用
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "System")
	FDateTime m_gameStartTime;

	/**
	 * @brief プレイ時間（秒）を取得する
	 * @return プレイ時間（秒）
	 * @details
	 * - `m_gameStartTime` からの経過秒数を返す
	 * - Blueprintからも呼び出せる
	 */
	UFUNCTION(BlueprintCallable, Category = "System")
	float GetPlayTimeSeconds() const;

public:
	/**
	 * @brief セーブ処理
	 * @details
	 * - ゲームデータの保存処理を行う
	 * - Blueprintからも呼び出せる
	 * @note 具体的な保存処理は派生クラスで実装
	 */
	UFUNCTION(BlueprintCallable, Category = "System|Save")
	virtual void SaveData();

	/**
	 * @brief ロード処理
	 * @details
	 * - ゲームデータの読み込み処理を行う
	 * - Blueprintからも呼び出せる
	 * @note 具体的な読み込み処理は派生クラスで実装
	 */
	UFUNCTION(BlueprintCallable, Category = "System|Save")
	virtual void LoadData();

	/**
	 * @brief デバッグメッセージ出力
	 * @param _message 出力したいメッセージ
	 * @details
	 * - デバッグ用のログや画面表示を行う
	 * - 補助的に使用
	 */
	UFUNCTION(BlueprintCallable, Category = "System|Debug")
	void PrintDebugMessage(const FString& _message) const;
};
