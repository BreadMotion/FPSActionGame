#pragma once
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveDataStructures.generated.h"

/**
 * シリアライズ対象データ構造
 */
UCLASS()
class FPSACTIONGAME_API USaveGameData : public USaveGame
{
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, Category = "Player")
    FString m_playerName;

    UPROPERTY(VisibleAnywhere, Category = "Player")
    int32 m_playerLevel;
};
