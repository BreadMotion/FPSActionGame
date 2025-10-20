#pragma once
#include "CoreMinimal.h"
#include "FPSSystem/BaseSystem.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SaveManager.h"
#include "SaveSystem.generated.h"

/**
 * @class USaveSystem
 * @brief セーブ管理を行うサブシステムクラス
 * @details UGameInstanceSubsystemとして動作するセーブ管理サブシステム
 * - GameInstance起動時に初期化
 * - SaveManagerを通してローカル/リモートの保存を抽象化
 */
UCLASS()
class FPSACTIONGAME_API USaveSystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& _collection) override;
    virtual void Deinitialize() override;

    // セーブデータ保存
    UFUNCTION(BlueprintCallable, Category = "Save")
    void SaveAll();

    // セーブデータ読み込み
    UFUNCTION(BlueprintCallable, Category = "Save")
    void LoadAll();

private:
    TUniquePtr<FSaveManager> m_saveManager;
};
