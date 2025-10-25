#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "WeaponTable.generated.h"

/**
 * @brief シートから自動生成されたDataTable行構造体
 * @details CSV: https://docs.google.com/spreadsheets/d/1YHssd98A2mBzEWdTSMbR_8xpO6EAnEMXHFCLLPs93_k/export?format=csv
 */
USTRUCT(BlueprintType)
struct FPSACTIONGAME_API FWeaponTable : public FTableRowBase
{
    GENERATED_BODY()

    /** DataTable行名 */
    // 名前
    UPROPERTY(EditAnywhere, BlueprintReadOnly) FName Name;

    // 武器種類
    UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 Type;

    // インポートするか
    UPROPERTY(EditAnywhere, BlueprintReadOnly) bool Ignore;

    // 攻撃
    UPROPERTY(EditAnywhere, BlueprintReadOnly) float Damage;

    // 速さ
    UPROPERTY(EditAnywhere, BlueprintReadOnly) float speed;

};
