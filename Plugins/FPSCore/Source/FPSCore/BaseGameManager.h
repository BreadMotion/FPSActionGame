#pragma once
#include "CoreMinimal.h"
#include "FPSSystem/BaseSystem.h"
#include "BaseGameManager.generated.h"

/**
 * @class UBaseGameManager
 * @brief ゲーム全体のシステム統括クラス。
 * @details
 * - UBaseSystem を継承し、Subsystem 群の初期化・終了・レベル変更を統合管理します。
 * - ゲーム開始時にすべての UBaseSystem を自動検出して登録。
 * - レベル遷移時に全システムへ通知をブロードキャストします。
 * - ゲーム終了時に各システムの終了処理を一括実行します。
 */
UCLASS()
class FPSCORE_API UBaseGameManager : public UBaseSystem
{
	GENERATED_BODY()

public:
	/**
	 * @brief Subsystem 初期化時に呼ばれる。
	 * @details
	 * UGameInstance にロードされたタイミングで自動的に呼び出されます。
	 * すべての UBaseSystem の初期化を行い、現在のレベルを記録します。
	 * @param Collection サブシステム登録情報。
	 */
	virtual void Initialize(FSubsystemCollectionBase& _collection) override;

	/**
	 * @brief Subsystem 終了時に呼ばれる。
	 * @details
	 * 登録されたすべてのシステムの終了処理を呼び出し、リストをクリアします。
	 */
	virtual void Deinitialize() override;

	/**
	 * @brief レベル遷移時の処理。
	 * @details
	 * レベル名を更新し、全登録システムに OnLevelChanged を通知します。
	 * @param _oldLevel 遷移前のレベル名。
	 * @param _newLevel 遷移後のレベル名。
	 */
	void HandleLevelChanged(const FString& _oldLevel, const FString& _newLevel);

	/**
	 * @brief 現在のレベル名を取得する。
	 * @return 現在ロード中のレベル名。
	 */
	UFUNCTION(BlueprintPure, Category = "BaseGameManager")
	FString GetCurrentLevel() const { return m_currentLevel; }

	/**
	 * @brief 特定のシステムを型指定で取得する。
	 * @tparam T 取得するシステムの型。
	 * @return 該当するシステムインスタンス。存在しない場合は nullptr。
	 */
	template <typename T>
	T* GetSystem() const
	{
		for (UBaseSystem* Sys : m_registeredSystems)
		{
			if (T* Casted = Cast<T>(Sys))
			{
				return Casted;
			}
		}
		return nullptr;
	}

private:
	/** @brief 現在のレベル名を記録 */
	UPROPERTY()
	FString m_currentLevel;

	/** @brief 登録されているシステムのリスト */
	UPROPERTY()
	TArray<TObjectPtr<UBaseSystem>> m_registeredSystems;

	/**
	 * @brief すべてのシステムを初期化する。
	 * @details
	 * GameInstance 内の Subsystem を列挙し、UBaseSystem を継承するものを登録。
	 */
	void InitializeAllSystems();

	/**
	 * @brief すべてのシステムを終了処理する。
	 * @details
	 * 各 UBaseSystem に OnGameStateChanged("Shutdown") を送信して破棄します。
	 */
	void ShutdownAllSystems();
};
