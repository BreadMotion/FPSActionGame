#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BaseGameManager.generated.h"

/**
 * 
 */
UCLASS()
class FPSACTIONGAME_API UBaseGameManager : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Game")
    void LoadLevelByName(const FString& _levelName);

    UFUNCTION(BlueprintCallable, Category = "Game")
    void QuitGame();
};