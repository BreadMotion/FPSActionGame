#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"

/**
 * @brief シートから自動生成されたDataTable行構造体
 * @details CSV: https://docs.google.com/spreadsheets/d/1YHssd98A2mBzEWdTSMbR_8xpO6EAnEMXHFCLLPs93_k/edit?usp=drive_link?output=csv
 */
USTRUCT(BlueprintType)
struct FPSACTIONGAME_API FWeaponTable : public FTableRowBase
{
    GENERATED_BODY()

    /** DataTable行名（CSVの1列目） */
    UPROPERTY(EditAnywhere, BlueprintReadOnly) FName Name;

};
