#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BaseSystem.generated.h"

/**
 * ゲーム全体で利用される基本サブシステム。
 * 他のSubsystemの親クラスとしても利用できます。
 */
UCLASS(Blueprintable)
class FPSACTIONGAME_API UBaseSystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    // 初期化
    virtual void Initialize(FSubsystemCollectionBase& _collection) override;

    // 終了処理
    virtual void Deinitialize() override;

protected:
    // 永続データ例：ゲームの開始時間
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "System")
    FDateTime m_gameStartTime;

    // 現在のプレイ時間を取得
    UFUNCTION(BlueprintCallable, Category = "System")
    float GetPlayTimeSeconds() const;

public:
    // セーブデータ保存例
    UFUNCTION(BlueprintCallable, Category = "System|Save")
    virtual void SaveData();

    // セーブデータ読み込み例
    UFUNCTION(BlueprintCallable, Category = "System|Save")
    virtual void LoadData();

    // 任意のログ出力
    UFUNCTION(BlueprintCallable, Category = "System|Debug")
    void PrintDebugMessage(const FString& _message) const;
};
