#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BaseSystem.generated.h"

/**
 * @class UBaseSystem
 * @brief ゲーム全体で利用される基本サブシステムの基底クラス。
 * @details
 * - すべてのゲーム内サブシステム（例：セーブ、ネットワーク、解析など）の共通処理を提供します。
 * - `UGameInstanceSubsystem` を継承しており、ゲーム全体に1インスタンスのみ存在します。
 * - 他のSubsystemクラス（例：`USaveSystem`）の親クラスとして利用できます。
 */
UCLASS(Blueprintable)
class FPSACTIONGAME_API UBaseSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	/**
	 * @class UBaseSystem
	 * @brief ゲーム全体で利用される基本サブシステムの基底クラス。
	 * @details
	 * - すべてのゲーム内サブシステム（例：セーブ、ネットワーク、解析など）の共通処理を提供します。
	 * - `UGameInstanceSubsystem` を継承しており、ゲーム全体に1インスタンスのみ存在します。
	 * - 他のSubsystemクラス（例：`USaveSystem`）の親クラスとして利用できます。
	 */
	virtual void Initialize(FSubsystemCollectionBase& _collection) override;

	/**
	 * @brief サブシステム終了処理。
	 * @details
	 * - ゲーム終了時またはインスタンス破棄時に呼び出されます。
	 * - 使用中のリソース開放やセーブ処理などを行います。
	 *
	 * @note `UGameInstanceSubsystem::Deinitialize()` のオーバーライドです。
	 */
	virtual void Deinitialize() override;

	/**
	 * @brief レベル遷移時に呼ばれるイベント。
	 * @param _oldLevelName 遷移前のレベル名。
	 * @param _newLevelName 遷移後のレベル名。
	 * @details
	 * - `UBaseGameManager` から呼び出され、レベル変更を通知します。
	 * - 派生クラスでオーバーライドして、レベルごとの初期化・終了処理を実装できます。
	 */
	virtual void OnLevelChanged(const FString& _oldLevelName, const FString& _newLevelName);

	/**
	 * @brief ゲームの再生状態変更時に呼ばれるイベント。
	 * @param _stateName 状態名（例："Pause"、"Resume"、"GameOver"など）。
	 * @details
	 * - `UBaseGameManager::BroadcastGameStateChanged()` によって通知されます。
	 * - 状態に応じたリソース制御やログ送信などを行う場合に利用します。
	 */
	virtual void OnGameStateChanged(const FString& _stateName);

protected:
	/**
	 * @brief ゲーム開始時刻。
	 * @details
	 * - ゲーム起動時に `Initialize()` 内で設定されます。
	 * - プレイ時間の計測などに利用されます。
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "System")
	FDateTime m_gameStartTime;

	/**
	 * @brief 現在のプレイ時間を取得します。
	 * @return 経過時間（秒）。
	 * @details
	 * - `m_gameStartTime` からの経過時間を秒単位で返します。
	 * - Blueprintからも呼び出し可能です。
	 */
	UFUNCTION(BlueprintCallable, Category = "System")
	float GetPlayTimeSeconds() const;

public:
	/**
	 * @brief セーブデータを保存します。
	 * @details
	 * - セーブシステムや永続データの保存処理を実装します。
	 * - Blueprintから呼び出すことも可能です。
	 *
	 * @note 派生クラスで具体的なセーブ処理を実装してください。
	 */
	UFUNCTION(BlueprintCallable, Category = "System|Save")
	virtual void SaveData();

	/**
	 * @brief セーブデータを読み込みます。
	 * @details
	 * - セーブシステムや永続データのロード処理を実装します。
	 * - Blueprintから呼び出すことも可能です。
	 *
	 * @note 派生クラスで具体的なロード処理を実装してください。
	 */
	UFUNCTION(BlueprintCallable, Category = "System|Save")
	virtual void LoadData();

	/**
	 * @brief デバッグ用メッセージを出力します。
	 * @param _message 出力するメッセージ文字列。
	 * @details
	 * - 画面上またはログにデバッグメッセージを表示します。
	 * - システム状態の確認やテスト時の補助に利用します。
	 */
	UFUNCTION(BlueprintCallable, Category = "System|Debug")
	void PrintDebugMessage(const FString& _message) const;
};
