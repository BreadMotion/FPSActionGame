#include "BaseGameManager.h"
#include "Kismet/GameplayStatics.h"

void UBaseGameManager::LoadLevelByName(const FString& _levelName)
{
    if (UWorld* world = GetWorld())
        UGameplayStatics::OpenLevel(world, FName(*_levelName));
}

void UBaseGameManager::QuitGame()
{
    if (UWorld* world = GetWorld())
    {
        APlayerController* pc = UGameplayStatics::GetPlayerController(world, 0);
        UKismetSystemLibrary::QuitGame(world, pc, EQuitPreference::Quit, false);
    }
}
