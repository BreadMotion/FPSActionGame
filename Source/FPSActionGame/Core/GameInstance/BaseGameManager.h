#pragma once
#include "CoreMinimal.h"
#include "System/BaseSystem.h"
#include "BaseGameManager.generated.h"

/**
 * @class UBaseGameManager
 * @brief ゲーム全体を管理するサブシステム
 * @details
 *  - レベル遷移、セーブ/ロード、設定値の永続化などを担当します
 *  - UBaseSystem を継承しており、ゲーム全体に1インスタンスのみ存在します
 *  - Blueprint からも呼び出し可能です
 */
UCLASS(Blueprintable)
class FPSACTIONGAME_API UBaseGameManager : public UBaseSystem
{
    GENERATED_BODY()

public:
    /** @brief 初期化処理 */
    virtual void Initialize(FSubsystemCollectionBase& _collection) override;

    /** @brief 終了処理 */
    virtual void Deinitialize() override;

    /**
     * @brief レベルをロードします
     * @param LevelName ロードするレベル名
     * @note この関数は非同期ではなく、即時ロードを行います
     */
    UFUNCTION(BlueprintCallable, Category = "Game")
    void LoadLevel(const FString& _levelName);

    /**
     * @brief ゲームを終了します
     * @param bForceQuit 強制終了する場合は true
     */
    UFUNCTION(BlueprintCallable, Category = "Game")
    void QuitGame(bool _bForceQuit = false);

    /**
     * @brief 現在のプレイ時間（秒）を取得します
     * @return 経過時間（秒）
     */
    UFUNCTION(BlueprintPure, Category = "Game")
    float GetElapsedPlayTime() const;

private:
    /** @brief ゲーム開始時刻。 */
    FDateTime m_GameStartTime;
};