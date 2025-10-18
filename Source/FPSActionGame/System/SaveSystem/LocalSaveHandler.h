#pragma once
#include "CoreMinimal.h"
#include "SaveDataStructures.h"

/**
 * ローカルセーブデータを扱うハンドラー
 * - SaveGameObjectを使用して保存
 */
class FLocalSaveHandler
{
public:
    void SaveData() { UE_LOG(LogTemp, Log, TEXT("FLocalSaveHandler::SaveData called (stub)")); }
    void LoadData() { UE_LOG(LogTemp, Log, TEXT("FLocalSaveHandler::LoadData called (stub)")); }

private:
    FString GetSaveSlotName() const;
};
