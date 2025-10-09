#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BaseSystem.generated.h"

/**
 * @class UBaseSystem
 * @brief ゲーム全体で利用される基本サブシステム
 * @details 
 *  - 他のSubsystemの親クラスとしても利用できます
 */
UCLASS(Blueprintable)
class FPSACTIONGAME_API UBaseSystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    /** @brief 初期化 */
    virtual void Initialize(FSubsystemCollectionBase& _collection) override;

    /** @brienf 終了処理 */
    virtual void Deinitialize() override;

protected:
    /** @brief ゲームの開始時間*/
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "System")
    FDateTime m_gameStartTime;

    /** @brief 現在のプレイ時間を取得 */
    UFUNCTION(BlueprintCallable, Category = "System")
    float GetPlayTimeSeconds() const;

public:
    /** @brienf セーブデータ保存 */
    UFUNCTION(BlueprintCallable, Category = "System|Save")
    virtual void SaveData();

    /** @brienfセーブデータ読み込み */
    UFUNCTION(BlueprintCallable, Category = "System|Save")
    virtual void LoadData();
    
    /** @brienf デバッグ用ログ出力
    * @param _message : 出力メッセージ */
    UFUNCTION(BlueprintCallable, Category = "System|Debug")
    void PrintDebugMessage(const FString& _message) const;
};
