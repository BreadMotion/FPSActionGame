#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "WeaponTable.generated.h"

/**
 * @brief シートから自動生成されたDataTable行構造体
 * @details CSV: https://docs.google.com/spreadsheets/d/1YHssd98A2mBzEWdTSMbR_8xpO6EAnEMXHFCLLPs93_k/edit?usp=sharing
 */
USTRUCT(BlueprintType)
struct FPSACTIONGAME_API FWeaponTable : public FTableRowBase
{
    GENERATED_BODY()

    /** DataTable行名 */
    // 名前
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName Name = NAME_None;

    // 武器種類
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 Type = 0;

    // インポートするか
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool Ignore = false;

    // 攻撃
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float Damage = 0.0f;

    // 速さ
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float speed = 0.0f;

};
